# Building Paperboat for Android, iOS and the web

All three platforms build the same CMake project the desktop build does. What
differs is how the game's files get onto the device, so start with how that
works — the rest is mechanical.

## The two archives

Paperboat needs two `.o2r` archives at runtime:

| Archive | What it is | Where it comes from |
| --- | --- | --- |
| `paperboat.o2r` | The engine's own assets: shaders, fonts, button art. Everything under `port/`. | Built from source by the `GeneratePortO2R` CMake target (or by Gradle on Android). Ships with the app. |
| `pm64.o2r` | The game's assets, extracted from a Paper Mario ROM by Torch. | Generated on the user's own machine or device. **Never ships with the app.** |

Torch needs `config.yml` and `assets/` (the extraction recipes) on disk to
produce `pm64.o2r`, so those travel with the app too.

`config.yml` is also what recognises a ROM: its top-level keys are the SHA-1
hashes Torch has recipes for. `GameExtractor::DetectVersion()` hashes a file and
looks it up there, and every ROM prompt in the port — the desktop scan, the
Android launcher, the web picker — goes through it. There is no second list of
hashes anywhere; adding a ROM version to `config.yml` is enough.

## Android

Requires Android Studio (or the command-line SDK) with:

* NDK 30.0.15729638 — set in `android/app/build.gradle.kts`
* CMake 3.30.3 or newer, installed through the SDK manager. The NDK's bundled
  3.22.1 is too old for libultraship.
* JDK 17 or newer. The wrapper is on Gradle 9.4, so anything up to JDK 26 works;
  Gradle picks up `JAVA_HOME`, and Android Studio's bundled JBR is a safe choice:

  ```bash
  export JAVA_HOME="/Applications/Android Studio.app/Contents/jbr/Contents/Home"
  ```

```bash
cd android
./gradlew assembleDebug          # app/build/outputs/apk/debug/
./gradlew installDebug           # straight onto a connected device
```

Gradle drives CMake itself; there is no separate CMake step. It also builds
`paperboat.o2r` from `port/` and bundles it with `config.yml` and `assets/` into
a single `gamedata.zip` inside the APK — so a clean checkout builds without a
desktop build having run first.

The build is **arm64-v8a only**. Add `"armeabi-v7a"` to `abiFilters` if you need
a 32-bit device; it roughly doubles an already long native build.

### On the device

`LauncherActivity` runs first. It unpacks `gamedata.zip` into the app's external
files directory, asks for a ROM through the document picker, checks it against
`config.yml`, and runs Torch over it. That last step takes a minute or more.
Everything then lives in one directory the user can reach with a file manager:

```
Android/data/dev.net64.paperboat/files/
  baserom.us.z64   config.yml   assets/   paperboat.o2r   pm64.o2r
  mods/            saves/       gamecontrollerdb.txt
```

The launcher runs in its own process (`android:process=":launcher"`) and calls
`Runtime.exit()` once the archive is written. Torch's `Companion` holds the ROM
and every decoded asset and is never freed, so ending the process is what hands
that memory back before the game starts.

In the game, the engine draws its own on-screen controls (see
[Touch controls](#touch-controls)); the only Android view over the SDL surface is
a Mods button, and it appears only while the engine's menu is open. Mods and
Saves both have their own screens from there.

### Release signing

Put a `key.properties` beside `android/settings.gradle.kts` (it is gitignored):

```properties
storeFile=paperboat.jks
storePassword=…
keyAlias=…
keyPassword=…
```

CI can use `KEYSTORE_FILE` / `KEYSTORE_PASSWORD` / `KEY_ALIAS` / `KEY_PASSWORD`
instead. With neither, the release build falls back to the debug key so a fork
still gets an installable APK.

## iOS

Requires Xcode and an iOS SDK. The build uses the Xcode generator because the
app is a bundle.

```bash
cmake -S . -B build-ios -G Xcode \
  -DCMAKE_TOOLCHAIN_FILE=cmake/ios.paperboat.toolchain.cmake -DPLATFORM=OS64
cmake --build build-ios --config Release
```

To sideload without a paid developer account, add `-DIOS_SIGNING=OFF` for an
unsigned bundle. With signing on, set `IOS_DEVELOPMENT_TEAM` in the environment
to pin a team; otherwise Xcode picks one from the signing identity.

The bundle identifier is `dev.net64.paperboat`, and the deployment target is
**iOS 16.3**. That floor is not cosmetic: the engine formats floats through
`std::format`, whose `std::to_chars` path libc++ marks unavailable on anything
older. That is why the toolchain file above is `ios.paperboat.toolchain.cmake`
rather than `ios.toolchain.cmake` — it sets the target before the upstream
toolchain bakes it into the compiler's triple, which CMakeLists.txt is too late
to do. Override it with `-DDEPLOYMENT_TARGET=…` only if you have dealt with
that; the configure refuses anything below 16.3.

`config.yml`, `assets/` and `paperboat.o2r` are copied into the `.app` — that is
where `Ship::Context::GetAppBundlePath()` points. Everything the user owns lives
in the app's Documents folder instead, which `UIFileSharingEnabled` and
`LSSupportsOpeningDocumentsInPlace` expose in the Files app. That is the only
way things get in and out:

* put `baserom.us.z64` there and launch; the game extracts it on first run
* mods go in `Documents/mods/`, saves come out of `Documents/saves/`

## Web

Requires the [Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html).

```bash
source /path/to/emsdk/emsdk_env.sh
emcmake cmake -S . -B build-web -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build-web
```

The output is `build-web/paperboat.html` plus its `.js`/`.wasm`/`.data` and
`coi-serviceworker.js`. Serve the directory over HTTP — opening the file
directly will not work:

```bash
python3 -m http.server -d build-web 8080
```

The game uses WASM threads, which need `SharedArrayBuffer`, which needs COOP and
COEP headers. `coi-serviceworker.js` installs them client-side so any static host
works; a host that sends the headers itself is faster, since it skips the extra
reload.

On first run the page offers to generate `pm64.o2r` from a ROM in the browser, or
to load one generated earlier. Both go through a real file input inside a click
handler — Safari ignores a file dialog opened from anywhere else. Nothing is
uploaded; the ROM is read into the page's virtual filesystem and thrown away.

Everything the game writes lives under `/storage`, an IndexedDB mount, synced
every five seconds and again on exit. Clearing site data deletes the generated
archive and every save with it.

`-DPAPERBOAT_WEB_PRELOAD_ROM=/path/to/pm64.o2r` embeds an already-generated
archive at build time and skips the in-browser extraction. It is a development
shortcut — never ship a build made with it.

### Asyncify

The engine's frame loop blocks, so the web build runs under Asyncify. Torch is
excluded from instrumentation in `src/port/web/asyncify-remove.txt`: Asyncify
turns every instrumented function into thousands of wasm locals, and Safari keeps
those on the worker's native stack, which the extraction overflows. If you add a
new top-level namespace to Torch, add it to that file.

## Touch controls

The on-screen pad is the engine's own — `src/port/ui/TouchControls.cpp`, drawn
inside the render surface, so it works identically on Android, iOS and a touch
browser. It is on by default on Android and iOS and off elsewhere; Settings →
Controller has the toggle, scale, opacity, and an **Edit Touch Layout** button
that lets every control be dragged to a new position.

On desktop the mouse acts as a single finger, which is how the layout can be
tried out without a device.

## CI

`.github/workflows/build.yml` builds all six platforms on every push and on
`workflow_dispatch`, and uploads each one as an artifact:

| Job | Runner | Artifact |
| --- | --- | --- |
| Linux | `ubuntu-latest` | binary + `paperboat.o2r` + `config.yml` + `assets/` |
| macOS | `macos-14` (arm64) | same |
| Windows | `windows-2022` | same, built through the `windows-release` preset (Ninja + clang-cl) |
| Android | `ubuntu-latest` | `Paperboat.apk` |
| iOS | `macos-15` | `Paperboat-unsigned.ipa` + sideloading notes |
| Web | `ubuntu-latest` | the static site, and a Pages deploy on `develop` |

No job builds `paperboat.o2r` for the others — every build makes its own from
`port/`, and the APK packs its own. Nothing in CI touches a ROM.

Each job ends by checking that what it produced is actually runnable, because
none of these failures show up at link time: the desktop jobs run
`.github/scripts/check-desktop-build.sh` (binary, archive, `config.yml`, a
non-empty `assets/`), the Android job checks the APK really carries every asset
`GameAssets.kt` opens by name plus both `.so` files, and the iOS job checks the
`.app` carries the recipes it needs to extract a ROM on device.

Two deliberate omissions:

* **No Vulkan SDK** is installed. libultraship's `find_package(Vulkan QUIET)`
  falls back to OpenGL, Metal or DX11, so CI validates the build without paying
  for the SDK download every run. Add it per-job if you want the Vulkan backend
  in the artifacts.
* **No formatting gate.** `.clang-format` says 4-space, and a good deal of
  `src/port/` is 2-space, so a `--check` job would fail on the first run
  against code nobody has touched. Worth adding once the tree is uniform.

### Secrets

Everything works without any secret; the Android APK just falls back to the
debug key, which is still installable. To sign releases with your own key, set
`KEYSTORE_BASE64` (the keystore, base64-encoded), `KEYSTORE_PASSWORD`,
`KEY_ALIAS` and `KEY_PASSWORD`.

### GitHub Pages

The deploy job only runs for pushes to `develop` on `HarbourMasters/PaperBoat`.
It needs Pages turned on for the repository with **Source: GitHub Actions**
(Settings → Pages); until then the job fails while the build itself is fine.

## What doesn't build on these platforms

Scripting (`ENABLE_SCRIPTING`) and the native mod loader are forced off: none of
the three can `dlopen` a native mod, and TCC has no backend for any of them.
Archive-based mods (`.o2r`, `.zip`, folders) work everywhere.
