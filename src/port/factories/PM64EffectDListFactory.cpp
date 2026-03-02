// PM64 Effect Display List Factory
//
// Overrides the standard DListFactory binary exporter to fix a width encoding bug
// in torch's G_SETTIMG → G_SETTIMG_OTR_HASH conversion.
//
// The standard DListFactory uses gsDPSetTextureOTRImage(fmt, siz, C0(0,10), ptr)
// which double-subtracts 1 from the width (the original DL already stores width-1,
// and the macro subtracts 1 again). This causes texture_to_load.width to be off by 1,
// which breaks effects that use G_LOADTILE (e.g. sparkles with its 176x22 texture strip).
//
// This factory preserves the original w0 bits exactly:
//   newW0 = (G_SETTIMG_OTR_HASH << 24) | (w0 & 0x00FFFFFF)

#include "PM64EffectDListFactory.h"
#include "Companion.h"
#include "utils/Decompressor.h"
#include "spdlog/spdlog.h"
#include "n64/gbi-otr.h"
#include "strhash64/StrHash64.h"

// F3DEX2 opcodes
#define F3DEX2_G_VTX      0x01
#define F3DEX2_G_DL       0xDE
#define F3DEX2_G_MTX      0xDA
#define F3DEX2_G_ENDDL    0xDF
#define F3DEX2_G_SETTIMG  0xFD
#define F3DEX2_G_MOVEMEM  0xDC

#define C0(pos, width) ((w0 >> (pos)) & ((1U << width) - 1))

// Override DListFactory::parse to skip auto-discovery of sub-DL/VTX/light assets.
// All effect assets are already defined in the YAML files, so auto-discovery via
// Companion::Instance->AddAsset() is unnecessary and harmful: it re-registers
// sub-DLs as "GFX" type (standard DListFactory), overwriting the YAML-defined
// "PM64:EFFECT_DL" entries and causing them to be exported by the standard
// DListBinaryExporter instead of PM64EffectDListBinaryExporter.
std::optional<std::shared_ptr<IParsedData>> PM64EffectDListFactory::parse(std::vector<uint8_t>& raw_buffer, YAML::Node& node) {
    auto [_, segment] = Decompressor::AutoDecode(node, raw_buffer);
    LUS::BinaryReader reader(segment.data, segment.size);
    reader.SetEndianness(Torch::Endianness::Big);

    std::vector<uint32_t> gfxs;
    bool processing = true;

    while (processing) {
        auto w0 = reader.ReadUInt32();
        auto w1 = reader.ReadUInt32();
        uint8_t opcode = w0 >> 24;

        if (opcode == F3DEX2_G_ENDDL) {
            processing = false;
        }

        if (opcode == F3DEX2_G_DL) {
            // If this is a branch (G_DL_NO_PUSH), stop processing like the base class does
            if ((w0 >> 16) & 0x01) {
                processing = false;
            }
            // Intentionally skip Companion::Instance->AddAsset() — assets defined in YAML
        }

        gfxs.push_back(w0);
        gfxs.push_back(w1);
    }

    return std::make_shared<DListData>(gfxs);
}

ExportResult PM64EffectDListBinaryExporter::Export(std::ostream& write, std::shared_ptr<IParsedData> raw, std::string& entryName, YAML::Node& node, std::string* replacement) {
    auto cmds = std::static_pointer_cast<DListData>(raw)->mGfxs;
    auto writer = LUS::BinaryWriter();

    WriteHeader(writer, Torch::ResourceType::DisplayList, 0);

    // GBI version byte (F3DEX2)
    writer.Write(static_cast<int8_t>(GBIVersion::f3dex2));

    // Pad to 8-byte alignment
    while (writer.GetBaseAddress() % 8 != 0)
        writer.Write(static_cast<int8_t>(0xFF));

    // G_MARKER with resource hash
    auto bhash = CRC64((*replacement).c_str());
    writer.Write(static_cast<uint32_t>(G_MARKER << 24));
    writer.Write(static_cast<uint32_t>(0xBEEFBEEF));
    writer.Write(static_cast<uint32_t>(bhash >> 32));
    writer.Write(static_cast<uint32_t>(bhash & 0xFFFFFFFF));

    for (size_t i = 0; i < cmds.size(); i += 2) {
        auto w0 = cmds[i];
        auto w1 = cmds[i + 1];
        uint8_t opcode = w0 >> 24;

        if (opcode == F3DEX2_G_VTX) {
            auto ptr = w1;
            auto dec = Companion::Instance->GetSafeStringByAddr(ptr, "VTX");

            if (dec.has_value()) {
                uint64_t hash = CRC64(dec.value().c_str());
                if (hash == 0) {
                    throw std::runtime_error("Vtx hash is 0 for " + dec.value());
                }
                // Construct G_VTX_OTR_HASH: preserve n/v0 bits, zero the vtx offset
                uint32_t newW0 = (G_VTX_OTR_HASH << 24) | (w0 & 0x00FFFFFF);
                writer.Write(newW0);
                writer.Write(static_cast<uint32_t>(0));
                writer.Write(static_cast<uint32_t>(hash >> 32));
                writer.Write(static_cast<uint32_t>(hash & 0xFFFFFFFF));
            } else {
                SPDLOG_WARN("Could not find vtx at 0x{:X}", ptr);
                writer.Write(w0);
                writer.Write(w1);
            }
            continue;
        }

        if (opcode == F3DEX2_G_DL) {
            auto ptr = w1;
            // Use GetStringByAddr (no type check) since sub-DLs are registered as
            // "PM64:EFFECT_DL" in YAML, not "GFX" as the standard factory expects.
            auto dec = Companion::Instance->GetStringByAddr(ptr);
            auto branch = (w0 >> 16) & 0x01;  // G_DL_NO_PUSH

            // Construct G_DL_OTR_HASH
            uint32_t newW0 = (G_DL_OTR_HASH << 24) | (branch << 16);
            writer.Write(newW0);
            writer.Write(static_cast<uint32_t>(0));

            if (dec.has_value()) {
                uint64_t hash = CRC64(dec.value().c_str());
                writer.Write(static_cast<uint32_t>(hash >> 32));
                writer.Write(static_cast<uint32_t>(hash & 0xFFFFFFFF));
            } else {
                SPDLOG_WARN("Could not find display list at 0x{:X}", ptr);
                writer.Write(w0);
                writer.Write(w1);
            }

            if (branch) {
                // Append G_ENDDL after a branch
                writer.Write(static_cast<uint32_t>(F3DEX2_G_ENDDL << 24));
                writer.Write(static_cast<uint32_t>(0));
            }
            continue;
        }

        if (opcode == F3DEX2_G_MOVEMEM) {
            auto ptr = w1;
            auto res = Companion::Instance->GetStringByAddr(ptr);
            bool hasOffset = false;

            if (!res.has_value()) {
                res = Companion::Instance->GetStringByAddr(ptr - 0x8);
                hasOffset = res.has_value();
                if (!hasOffset) {
                    SPDLOG_WARN("Could not find light {:X}", ptr);
                }
            }

            uint8_t index = C0(0, 8);
            uint8_t offset = C0(8, 8) * 8;

            uint32_t newW0 = (G_MOVEMEM_OTR_HASH << 24) | (w0 & 0x00FFFFFF);
            uint32_t newW1 = _SHIFTL(index, 24, 8) | _SHIFTL(offset, 16, 8) | _SHIFTL((uint8_t)(hasOffset ? 1 : 0), 8, 8);

            writer.Write(newW0);
            writer.Write(newW1);

            if (res.has_value()) {
                uint64_t hash = CRC64(res.value().c_str());
                writer.Write(static_cast<uint32_t>(hash >> 32));
                writer.Write(static_cast<uint32_t>(hash & 0xFFFFFFFF));
            } else {
                SPDLOG_WARN("Could not find light at 0x{:X}", ptr);
                writer.Write(w0);
                writer.Write(w1);
            }
            continue;
        }

        if (opcode == F3DEX2_G_SETTIMG) {
            auto ptr = w1;
            auto dec = Companion::Instance->GetSafeStringByAddr(ptr, "TEXTURE");

            // FIX: Preserve original w0 bits (fmt/siz/width) exactly.
            uint32_t newW0 = (G_SETTIMG_OTR_HASH << 24) | (w0 & 0x00FFFFFF);
            writer.Write(newW0);
            writer.Write(ptr);

            if (dec.has_value()) {
                uint64_t hash = CRC64(dec.value().c_str());
                if (hash == 0) {
                    throw std::runtime_error("Texture hash is 0 for " + dec.value());
                }
                writer.Write(static_cast<uint32_t>(hash >> 32));
                writer.Write(static_cast<uint32_t>(hash & 0xFFFFFFFF));
            } else {
                SPDLOG_WARN("Could not find texture at 0x{:X}", ptr);
                writer.Write(w0);
                writer.Write(w1);
            }
            continue;
        }

        if (opcode == F3DEX2_G_MTX) {
            auto ptr = w1;
            auto dec = Companion::Instance->GetSafeStringByAddr(ptr, "MTX");

            uint32_t newW0 = (G_MTX_OTR << 24) | (w0 & 0x00FFFFFF);
            writer.Write(newW0);
            writer.Write(static_cast<uint32_t>(0));

            if (dec.has_value()) {
                uint64_t hash = CRC64(dec.value().c_str());
                if (hash == 0) {
                    throw std::runtime_error("Matrix hash is 0 for " + dec.value());
                }
                writer.Write(static_cast<uint32_t>(hash >> 32));
                writer.Write(static_cast<uint32_t>(hash & 0xFFFFFFFF));
            } else {
                SPDLOG_WARN("Could not find matrix at 0x{:X}", ptr);
                writer.Write(w0);
                writer.Write(w1);
            }
            continue;
        }

        // All other opcodes: pass through unchanged
        writer.Write(w0);
        writer.Write(w1);
    }

    writer.Finish(write);
    return std::nullopt;
}
