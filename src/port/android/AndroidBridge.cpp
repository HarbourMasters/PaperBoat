/**
 * JNI surface for the Android app: menu state, ROM recognition, and extraction.
 *
 * On-screen controls are not here — the engine draws its own, in
 * src/port/ui/TouchControls.cpp.
 *
 * The two extraction entry points take their paths as arguments rather than
 * asking Ship::Context: the launcher calls them before SDL exists.
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
 * Whether libultraship's menu is up. A keyboard, a gamepad or the menu itself
 * can change this behind Kotlin's back, so ask the engine rather than mirror it.
 *
 * Races with the game thread by design: it decides whether one button shows,
 * and a torn read self-corrects on the next poll.
 */
JNIEXPORT jboolean JNICALL Java_dev_net64_paperboat_MainActivity_isMenuOpen(JNIEnv*, jobject) {
    auto context = Ship::Context::GetRawInstance();
    if (context == nullptr) {
        return JNI_FALSE;
    }

    auto window = context->GetWindow();
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
 * The name config.yml gives the ROM at romPath, or null if it has no recipe.
 * Reading the same config.yml the extraction does keeps the launcher from
 * carrying its own copy of the supported hashes.
 */
JNIEXPORT jstring JNICALL
Java_dev_net64_paperboat_GameAssets_nativeDetectRom(JNIEnv* env, jobject, jstring jRomPath, jstring jSourceDir) {
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
 * sourceDir holds config.yml and assets/, unpacked from the APK by the
 * launcher. Returns null on success, or a message describing the failure.
 */
JNIEXPORT jstring JNICALL Java_dev_net64_paperboat_GameAssets_nativeGenerateGameArchive(
    JNIEnv* env, jobject, jstring jRomPath, jstring jSourceDir, jstring jDestDir
) {
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
    std::atomic<size_t> assetCount { 0 };
    std::atomic<size_t> totalAssets { 0 };
    try {
        if (!extractor.GenerateOTRTo(assetCount, totalAssets, sourceDir, destDir)) {
            extractError = GameExtractor::sLastError.empty()
                ? "Torch could not extract the ROM."
                : "Torch could not extract the ROM: " + GameExtractor::sLastError;
        }
    } catch (const std::exception& error) {
        extractError = std::string("Torch could not extract the ROM: ") + error.what();
    } catch (...) {
        extractError = "Torch could not extract the ROM.";
    }

    if (!extractError.empty()) {
        return fail(extractError);
    }

    // Init() logs and returns rather than throwing for some failures, so
    // confirm the archive really landed.
    std::error_code error;
    const std::filesystem::path archive = std::filesystem::path(destDir) / kGameArchive;
    if (!std::filesystem::exists(archive, error) || std::filesystem::file_size(archive, error) == 0) {
        return fail(
            std::string("Torch finished without producing ") + kGameArchive
            + ". Check that the ROM is Paper Mario (N64, US)."
        );
    }

    __android_log_print(ANDROID_LOG_INFO, kLogTag, "Wrote %s", archive.c_str());
    return nullptr;
}

} // extern "C"

#endif // __ANDROID__
