#pragma once

#include <filesystem>
#include <functional>
#include <optional>

#include "ship/window/gui/FileBrowserWindow.h"

#ifndef PAPERBOAT_NATIVE_FILE_DIALOG
#if defined(__SWITCH__) || defined(__WIIU__) || defined(__IOS__) || defined(__ANDROID__) ||                             \
    (defined(__linux__) && (defined(__aarch64__) || defined(__arm__)))
#define PAPERBOAT_NATIVE_FILE_DIALOG 0
#else
#define PAPERBOAT_NATIVE_FILE_DIALOG 1
#endif
#endif

namespace Paperboat {
void PickFile(Ship::FileBrowserRequest request, std::function<void(std::optional<std::filesystem::path>)> onResult);
} // namespace Paperboat
