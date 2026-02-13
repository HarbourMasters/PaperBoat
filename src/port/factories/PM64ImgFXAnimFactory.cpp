#include "PM64ImgFXAnimFactory.h"
#include "Companion.h"
#include "spdlog/spdlog.h"
#include <ship/utils/binarytools/endianness.h>

// ImgFX animation blob layout (produced by this factory):
//
// [0x00] u32 n64KeyframesOffset  (original segment-relative, for vertex fixup)
// [0x04] u32 n64GfxOffset        (original segment-relative, unused on port)
// [0x08] u16 vtxCount
// [0x0A] u16 gfxCount
// [0x0C] u16 keyframesCount
// [0x0E] u16 flags
// [0x10] Keyframe data (keyframesCount * vtxCount * 12 bytes, positions byte-swapped)
// [0x10 + keyframeDataSize] GFX data (gfxCount * 8 bytes, N64 Gfx commands word-swapped)

std::optional<std::shared_ptr<IParsedData>> PM64ImgFXAnimFactory::parse(std::vector<uint8_t>& buffer, YAML::Node& node) {
    auto segmentBase = GetSafeNode<uint32_t>(node, "offset");
    auto headerOffset = GetSafeNode<uint32_t>(node, "header_offset");

    uint32_t headerRomAddr = segmentBase + headerOffset;

    if (headerRomAddr + 16 > buffer.size()) {
        SPDLOG_ERROR("PM64:IMGFX_ANIM: Header at 0x{:X} exceeds buffer size 0x{:X}",
                     headerRomAddr, buffer.size());
        return std::nullopt;
    }

    // Read 16-byte N64 header (big-endian)
    uint8_t* hdr = buffer.data() + headerRomAddr;
    uint32_t n64KeyframesOffset = BSWAP32(*(uint32_t*)(hdr + 0x00));
    uint32_t n64GfxOffset       = BSWAP32(*(uint32_t*)(hdr + 0x04));
    uint16_t vtxCount           = BSWAP16(*(uint16_t*)(hdr + 0x08));
    uint16_t gfxCount           = BSWAP16(*(uint16_t*)(hdr + 0x0A));
    uint16_t keyframesCount     = BSWAP16(*(uint16_t*)(hdr + 0x0C));
    uint16_t flags              = BSWAP16(*(uint16_t*)(hdr + 0x0E));

    uint32_t keyframeDataSize = keyframesCount * vtxCount * 12;  // sizeof(ImgFXVtx) = 0x0C
    uint32_t gfxDataSize = gfxCount * 8;  // sizeof(N64 Gfx) = 8

    uint32_t keyframesRomAddr = segmentBase + n64KeyframesOffset;
    uint32_t gfxRomAddr = segmentBase + n64GfxOffset;

    if (keyframesRomAddr + keyframeDataSize > buffer.size()) {
        SPDLOG_ERROR("PM64:IMGFX_ANIM: Keyframe data at 0x{:X} (size 0x{:X}) exceeds buffer",
                     keyframesRomAddr, keyframeDataSize);
        return std::nullopt;
    }
    if (gfxRomAddr + gfxDataSize > buffer.size()) {
        SPDLOG_ERROR("PM64:IMGFX_ANIM: GFX data at 0x{:X} (size 0x{:X}) exceeds buffer",
                     gfxRomAddr, gfxDataSize);
        return std::nullopt;
    }

    // Build output blob: header (16) + keyframes + gfx
    uint32_t blobSize = 16 + keyframeDataSize + gfxDataSize;
    std::vector<uint8_t> blob(blobSize);

    // Write header (already byte-swapped to native LE)
    *(uint32_t*)(blob.data() + 0x00) = n64KeyframesOffset;
    *(uint32_t*)(blob.data() + 0x04) = n64GfxOffset;
    *(uint16_t*)(blob.data() + 0x08) = vtxCount;
    *(uint16_t*)(blob.data() + 0x0A) = gfxCount;
    *(uint16_t*)(blob.data() + 0x0C) = keyframesCount;
    *(uint16_t*)(blob.data() + 0x0E) = flags;

    // Copy and byte-swap keyframe data
    // ImgFXVtx: s16 ob[3] (bytes 0-5, need swap), u8 tc[2] (bytes 6-7, no swap),
    //           s8 cn[3] (bytes 8-10, no swap), pad (byte 11, no swap)
    uint8_t* kfSrc = buffer.data() + keyframesRomAddr;
    uint8_t* kfDst = blob.data() + 16;
    memcpy(kfDst, kfSrc, keyframeDataSize);
    for (uint32_t i = 0; i + 12 <= keyframeDataSize; i += 12) {
        uint16_t* v = reinterpret_cast<uint16_t*>(kfDst + i);
        v[0] = BSWAP16(v[0]);  // ob[0]
        v[1] = BSWAP16(v[1]);  // ob[1]
        v[2] = BSWAP16(v[2]);  // ob[2]
        // bytes 6-11: u8/s8 fields, no swap needed
    }

    // Copy and byte-swap GFX data (N64 Gfx: two u32 words each)
    uint8_t* gfxSrc = buffer.data() + gfxRomAddr;
    uint8_t* gfxDst = blob.data() + 16 + keyframeDataSize;
    memcpy(gfxDst, gfxSrc, gfxDataSize);
    for (uint32_t i = 0; i + 8 <= gfxDataSize; i += 8) {
        uint32_t* words = reinterpret_cast<uint32_t*>(gfxDst + i);
        words[0] = BSWAP32(words[0]);
        words[1] = BSWAP32(words[1]);
    }

    SPDLOG_INFO("PM64:IMGFX_ANIM: headerOffset=0x{:X}, vtxCount={}, gfxCount={}, keyframesCount={}, flags=0x{:X}, blobSize=0x{:X}",
                headerOffset, vtxCount, gfxCount, keyframesCount, flags, blobSize);

    return std::make_shared<RawBuffer>(blob);
}

ExportResult PM64ImgFXAnimBinaryExporter::Export(std::ostream& write, std::shared_ptr<IParsedData> raw, std::string& entryName, YAML::Node& node, std::string* replacement) {
    auto writer = LUS::BinaryWriter();
    auto data = std::static_pointer_cast<RawBuffer>(raw)->mBuffer;

    WriteHeader(writer, Torch::ResourceType::Blob, 0);
    writer.Write(static_cast<uint32_t>(data.size()));
    writer.Write(reinterpret_cast<char*>(data.data()), data.size());
    writer.Finish(write);

    return std::nullopt;
}

ExportResult PM64ImgFXAnimHeaderExporter::Export(std::ostream& write, std::shared_ptr<IParsedData> raw, std::string& entryName, YAML::Node& node, std::string* replacement) {
    return std::nullopt;
}
