/**
 * JNI surface for the Android app — the only three places the Kotlin side
 * reaches into native code:
 *
 *  - whether the engine's menu is up, which decides when the Mods button shows,
 *  - whether a file is a ROM the bundled recipes recognise, and
 *  - game asset generation, which runs Torch against that ROM.
 *
 * On-screen controls are not here: the engine draws and handles its own (see
 * src/port/ui/TouchControls.cpp).
 *
 * The two extraction entry points are deliberately independent of libultraship:
 * they are called from the launcher activity, before SDL exists, so they cannot
 * use Ship::Context to discover paths. The launcher passes them in explicitly.
 */
#ifdef __ANDROID__

#include <jni.h>
#include <android/log.h>

#include <atomic>
#include <exception>
#include <filesystem>
#include <string>

#include "extractor/GameExtractor.h"
#include "ship/Context.h"
#include "ship/window/Window.h"
#include "ship/window/gui/Gui.h"
#include <libultraship/bridge/windowbridge.h>

namespace {

constexpr const char* kLogTag = "Paperboat";
constexpr const char* kGameArchive = "pm64.o2r";

std::string ToStdString(JNIEnv* env, jstring value) {
    if (value == nullptr) {
        return {};
    }
    const char* chars = env->GetStringUTFChars(value, nullptr);
    std::string result = chars != nullptr ? chars : "";
    if (chars != nullptr) {
        env->ReleaseStringUTFChars(value, chars);
    }
    return result;
}

} // namespace

extern "C" {

/**
 * Whether libultraship's menu is currently up.
 *
 * The Mods button needs this because the menu is not only opened by the engine's
 * own on-screen toggle — a keyboard, a gamepad, or the menu closing itself all
 * change it behind Kotlin's back. Reading the engine's state instead of
 * mirroring it is what keeps the two from drifting apart.
 *
 * Called from the UI thread while the game thread renders. It reads a bool the
 * game thread may be writing, which is worth accepting here: the value only
 * decides whether one button is shown, and a torn read self-corrects on the
 * next poll.
 */
JNIEXPORT jboolean JNICALL Java_dev_net64_paperboat_MainActivity_isMenuOpen(JNIEnv*, jobject) {
    auto window = WindowGetWindowComponent();
    if (window == nullptr) {
        return JNI_FALSE;
    }

    auto gui = window->GetGui();
    if (gui == nullptr) {
        return JNI_FALSE;
    }

    return gui->GetMenuOrMenubarVisible() ? JNI_TRUE : JNI_FALSE;
}

/**
 * The name config.yml gives the ROM at romPath, or null when it is not one the
 * recipes in sourceDir can extract.
 *
 * Answering from the same config.yml the extraction reads is what keeps the
 * launcher from carrying its own copy of the supported hashes.
 */
JNIEXPORT jstring JNICALL Java_dev_net64_paperboat_GameAssets_nativeDetectRom(JNIEnv* env, jobject, jstring jRomPath,
                                                                             jstring jSourceDir) {
    const std::string romPath = ToStdString(env, jRomPath);
    const std::string sourceDir = ToStdString(env, jSourceDir);

    const auto version = GameExtractor::DetectVersion(romPath, sourceDir);
    if (!version.has_value()) {
        __android_log_print(ANDROID_LOG_WARN, kLogTag, "Unrecognised ROM at %s", romPath.c_str());
        return nullptr;
    }

    __android_log_print(ANDROID_LOG_INFO, kLogTag, "Recognised %s as %s", romPath.c_str(), version->c_str());
    return env->NewStringUTF(version->c_str());
}

/**
 * Runs Torch over the ROM at romPath and writes pm64.o2r into destDir.
 *
 * sourceDir is the directory holding config.yml and assets/ymls (unpacked from
 * the APK by the launcher). Returns null on success, or a message describing
 * what went wrong.
 */
JNIEXPORT jstring JNICALL Java_dev_net64_paperboat_GameAssets_nativeGenerateGameArchive(JNIEnv* env, jobject,
                                                                                       jstring jRomPath,
                                                                                       jstring jSourceDir,
                                                                                       jstring jDestDir) {
    const std::string romPath = ToStdString(env, jRomPath);
    const std::string sourceDir = ToStdString(env, jSourceDir);
    const std::string destDir = ToStdString(env, jDestDir);

    const auto fail = [env](const std::string& message) {
        __android_log_print(ANDROID_LOG_ERROR, kLogTag, "Asset generation failed: %s", message.c_str());
        return env->NewStringUTF(message.c_str());
    };

    GameExtractor extractor;
    if (!extractor.RunStandalone(romPath, sourceDir)) {
        return fail("Could not read a supported Paper Mario ROM at " + romPath + ".");
    }

    __android_log_print(ANDROID_LOG_INFO, kLogTag, "Extracting %s into %s", romPath.c_str(), destDir.c_str());

    std::string extractError;
    std::atomic<size_t> assetCount{ 0 };
    std::atomic<size_t> totalAssets{ 0 };
    try {
        if (!extractor.GenerateOTRTo(assetCount, totalAssets, sourceDir, destDir)) {
            extractError = GameExtractor::sLastError.empty() ? "Torch could not extract the ROM."
                                                             : "Torch could not extract the ROM: " +
                                                                   GameExtractor::sLastError;
        }
    } catch (const std::exception& error) {
        extractError = std::string("Torch could not extract the ROM: ") + error.what();
    } catch (...) { extractError = "Torch could not extract the ROM."; }

    if (!extractError.empty()) {
        return fail(extractError);
    }

    // Init() logs and returns rather than throwing for a few failure modes
    // (missing config, unrecognised ROM), so confirm the archive really landed.
    std::error_code error;
    const std::filesystem::path archive = std::filesystem::path(destDir) / kGameArchive;
    if (!std::filesystem::exists(archive, error) || std::filesystem::file_size(archive, error) == 0) {
        return fail(std::string("Torch finished without producing ") + kGameArchive +
                    ". Check that the ROM is Paper Mario (N64, US).");
    }

    __android_log_print(ANDROID_LOG_INFO, kLogTag, "Wrote %s", archive.c_str());
    return nullptr;
}

} // extern "C"

#endif // __ANDROID__
