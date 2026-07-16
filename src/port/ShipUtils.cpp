#include "ShipUtils.h"
#include <libultraship/libultraship.h>

constexpr f32 fourByThree = 4.0f / 3.0f;

extern "C" bool Ship_IsCStringEmpty(const char *str) {
  return str == NULL || str[0] == '\0';
}

char seedString[MAX_SEED_STRING_SIZE];
u32 finalSeed = 0;

extern uint32_t Ship_Hash(std::string str) {
  // FNV-1a
  const size_t len = str.size();
  uint32_t hval = 0x811c9dc5;
  for (size_t pos = 0; pos < len; pos++) {
    hval ^= (uint32_t)str[pos];
    hval *= 0x01000193;
  }
  return hval;
}

// Build vertex coordinates for a quad command
// In order of top left, top right, bottom left, then bottom right
// Supports flipping the texture horizontally
extern "C" void Ship_CreateQuadVertexGroup(Vtx *vtxList, s32 xStart, s32 yStart,
                                           s32 width, s32 height, u8 flippedH) {
  vtxList[0].v.ob[0] = xStart;
  vtxList[0].v.ob[1] = yStart;
  vtxList[0].v.tc[0] = (flippedH ? width : 0) << 5;
  vtxList[0].v.tc[1] = 0 << 5;

  vtxList[1].v.ob[0] = xStart + width;
  vtxList[1].v.ob[1] = yStart;
  vtxList[1].v.tc[0] = (flippedH ? width * 2 : width) << 5;
  vtxList[1].v.tc[1] = 0 << 5;

  vtxList[2].v.ob[0] = xStart;
  vtxList[2].v.ob[1] = yStart + height;
  vtxList[2].v.tc[0] = (flippedH ? width : 0) << 5;
  vtxList[2].v.tc[1] = height << 5;

  vtxList[3].v.ob[0] = xStart + width;
  vtxList[3].v.ob[1] = yStart + height;
  vtxList[3].v.tc[0] = (flippedH ? width * 2 : width) << 5;
  vtxList[3].v.tc[1] = height << 5;
}

void EncodeFilename(const std::string& input, char outFilename[8]) {
    for (int i = 0; i < 8; ++i) {
        if (i < input.length()) {
            char c = input[i];

            if (c >= 'A' && c <= 'Z') {
                outFilename[i] = c - 32;  // Uppercase shift
            }
            else if (c >= 'a' && c <= 'z') {
                outFilename[i] = c - 64;  // Lowercase shift
            }
            else {
                outFilename[i] = c;
            }
        }
        else {
            outFilename[i] = static_cast<char>(247); // '÷' pad character
        }
    }
}

std::string DecodeFilename(const char filename[8]) {
    std::string decoded = "";

    for (int i = 0; i < 8; ++i) {
        unsigned char c = static_cast<unsigned char>(filename[i]);

        // Stop decoding at pad character or null terminator
        if (c == 247 || c == '\0') {
            break;
        }

        // 1. Decode Uppercase: Encoded range is 33 to 58 ('!' to 'Z' minus offset)
        // 'A' (65) - 32 = 33 ('!')
        // 'Z' (90) - 32 = 58 (':')
        if (c >= 33 && c <= 58) {
            decoded += static_cast<char>(c + 32);
        }
        // 2. Decode Lowercase: Encoded range is 33 to 58 for lowercase ('a' to 'z')
        // 'a' (97) - 64 = 33 ('!')
        // 'z' (122) - 64 = 58 (':')
        // Note: Because the encoded ranges overlap, we need to know how your game 
        // distinguishes them, or use your original hardcoded overrides:
        else if (c == '!') {
            decoded += 'a'; // Decodes to lowercase 'a'
        }
        else if (c == ',') {
            decoded += 'l'; // Decodes to lowercase 'l'
        }
        else {
            // Fallback for other characters
            decoded += static_cast<char>(c);
        }
    }

    return decoded;
}

void LoadGuiTextures() {
  // @port: Load gui textures here
}
