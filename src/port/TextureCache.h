#ifndef PORT_TEXTURE_CACHE_H
#define PORT_TEXTURE_CACHE_H

#include <cstdint>

void TextureCache_Configure();
uint64_t TextureCache_CeilingBytes();
uint64_t TextureCache_AutoBytes();

#endif // PORT_TEXTURE_CACHE_H
