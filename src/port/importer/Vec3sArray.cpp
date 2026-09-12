#include "Vec3sArray.h"

namespace PM64 {
Vec3sData* Vec3sArray::GetPointer() {
    return mData.data();
}

size_t Vec3sArray::GetPointerSize() {
    return mData.size() * sizeof(Vec3sData);
}
} // namespace PM64
