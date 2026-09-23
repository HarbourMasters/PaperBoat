#ifndef SAVE_CONVERTER_H
#define SAVE_CONVERTER_H

#include <functional>
#include <string>

namespace SaveConverter {
constexpr int kSlotAll = 0;
constexpr int kSlotCount = 4;
struct Result {
    bool ok = false;
    int slotsImported = 0;
    std::string message;
};
Result ImportFromFlash(const std::string& srcPath, int srcSlot = kSlotAll, int destSlot = 1);
void PickAndImport(int srcSlot, int destSlot, std::function<void(Result)> onComplete);
} // namespace SaveConverter
#endif // SAVE_CONVERTER_H
