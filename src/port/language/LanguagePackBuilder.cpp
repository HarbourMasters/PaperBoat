#include "LanguagePackBuilder.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <zlib.h>

#include "TinySHA1.hpp"

namespace fs = std::filesystem;

namespace Paperboat {
namespace {

    using Bytes = std::vector<uint8_t>;

    // --- PAL ROM layout -------------------------------------------------------

    constexpr size_t kRomFull = 0x4000000;
    constexpr size_t kRomTrimmed = 0x3000000; // the last 16 MB of the full image mirror 0x2000000-0x3000000
    constexpr const char* kShaFull = "2111d39265a317414d359e35a7d971c4dfa5f9e1";
    constexpr const char* kShaTrimmed = "1273275142b79f7443f55bd35679a19670adfe3a";

    constexpr int kLangDe = 1;
    constexpr int kLangFr = 2;
    constexpr int kLangEs = 3;
    constexpr const char* kLangCodes[] = { "en", "de", "fr", "es" };

    // ROM range of each language's message block (msg_pal_* in the decomp splat).
    struct MsgRange {
        uint32_t start;
        uint32_t end;
    };
    constexpr MsgRange kMsgRanges[] = {
        { 0x2030000, 0x2132440 }, { 0x21B0000, 0x22D2220 }, { 0x2330000, 0x242C180 }, { 0x24B0000, 0x25B11C0 }
    };
    constexpr int kSectionCount = 47;

    constexpr uint32_t kFontStart = 0x110CB0;
    constexpr int kGlyphBytes = 128;
    constexpr int kGlyphCount = 0x5100 / kGlyphBytes;
    constexpr uint32_t kFontBlobSize = 0x5300;

    constexpr size_t kMsgHeader = 64; // BLBO header shared by every message resource
    constexpr size_t kTexHeader = 80; // XETO header in front of a texture's pixels

    struct PalMessage {
        const char* name;
        uint8_t section;
        uint16_t index;
    };
    struct PalImage {
        uint8_t lang;
        const char* path;
        uint32_t offset;
        uint32_t size;
    };
#include "PalLangTables.inc"

    // --- helpers --------------------------------------------------------------

    uint32_t ReadBE32(const Bytes& b, size_t pos) {
        return (uint32_t(b[pos]) << 24) | (uint32_t(b[pos + 1]) << 16) | (uint32_t(b[pos + 2]) << 8) | b[pos + 3];
    }
    uint32_t ReadLE32(const uint8_t* p) {
        return p[0] | (p[1] << 8) | (p[2] << 16) | (uint32_t(p[3]) << 24);
    }
    uint16_t ReadLE16(const uint8_t* p) {
        return uint16_t(p[0] | (p[1] << 8));
    }
    void PutLE32(Bytes& out, uint32_t v) {
        for (int i = 0; i < 4; i++) {
            out.push_back(uint8_t(v >> (8 * i)));
        }
    }
    void PutLE16(Bytes& out, uint16_t v) {
        out.push_back(uint8_t(v));
        out.push_back(uint8_t(v >> 8));
    }

    bool ReadFile(const fs::path& path, Bytes& out) {
        std::ifstream f(path, std::ios::binary | std::ios::ate);
        if (!f) {
            return false;
        }
        const auto size = f.tellg();
        out.resize(size_t(size));
        f.seekg(0);
        f.read(reinterpret_cast<char*>(out.data()), size);
        return bool(f);
    }

    std::string Sha1Hex(const uint8_t* data, size_t size) {
        sha1::SHA1 sha;
        sha.processBytes(data, size);
        uint32_t digest[5];
        sha.getDigest(digest);
        char buf[41];
        snprintf(buf, sizeof(buf), "%08x%08x%08x%08x%08x", digest[0], digest[1], digest[2], digest[3], digest[4]);
        return buf;
    }

    // --- minimal zip reader (the archive is a plain, non-zip64 zip) -------------

    class ZipReader {
    public:
        bool Open(const fs::path& path, std::string& error) {
            if (!ReadFile(path, mData)) {
                error = "Cannot read " + path.string();
                return false;
            }
            if (mData.size() < 22) {
                error = "Not a zip archive";
                return false;
            }
            // The end record sits in the last 64 KB (it may be followed by a comment).
            size_t eocd = std::string::npos;
            const size_t lowest = mData.size() > 22 + 0xFFFF ? mData.size() - 22 - 0xFFFF : 0;
            for (size_t i = mData.size() - 22 + 1; i-- > lowest;) {
                if (ReadLE32(&mData[i]) == 0x06054B50) {
                    eocd = i;
                    break;
                }
            }
            if (eocd == std::string::npos) {
                error = "Zip end record not found";
                return false;
            }
            const uint32_t count = ReadLE16(&mData[eocd + 10]);
            size_t pos = ReadLE32(&mData[eocd + 16]);
            if (count == 0xFFFF || pos >= mData.size()) {
                error = "Unsupported zip layout";
                return false;
            }
            for (uint32_t i = 0; i < count; i++) {
                if (pos + 46 > mData.size() || ReadLE32(&mData[pos]) != 0x02014B50) {
                    error = "Corrupt zip directory";
                    return false;
                }
                Entry e;
                e.method = ReadLE16(&mData[pos + 10]);
                e.compSize = ReadLE32(&mData[pos + 20]);
                e.size = ReadLE32(&mData[pos + 24]);
                const uint16_t nameLen = ReadLE16(&mData[pos + 28]);
                const uint16_t extraLen = ReadLE16(&mData[pos + 30]);
                const uint16_t commentLen = ReadLE16(&mData[pos + 32]);
                e.localOffset = ReadLE32(&mData[pos + 42]);
                mEntries.emplace(std::string(reinterpret_cast<const char*>(&mData[pos + 46]), nameLen), e);
                pos += 46 + nameLen + extraLen + commentLen;
            }
            return true;
        }

        bool Has(const std::string& name) const {
            return mEntries.count(name) != 0;
        }

        bool Read(const std::string& name, Bytes& out) const {
            auto it = mEntries.find(name);
            if (it == mEntries.end()) {
                return false;
            }
            const Entry& e = it->second;
            const size_t lh = e.localOffset;
            if (lh + 30 > mData.size() || ReadLE32(&mData[lh]) != 0x04034B50) {
                return false;
            }
            const size_t dataPos = lh + 30 + ReadLE16(&mData[lh + 26]) + ReadLE16(&mData[lh + 28]);
            if (dataPos + e.compSize > mData.size()) {
                return false;
            }
            out.resize(e.size);
            if (e.method == 0) {
                std::memcpy(out.data(), &mData[dataPos], e.size);
                return true;
            }
            if (e.method != 8) {
                return false;
            }
            z_stream zs {};
            if (inflateInit2(&zs, -15) != Z_OK) {
                return false;
            }
            zs.next_in = const_cast<Bytef*>(&mData[dataPos]);
            zs.avail_in = e.compSize;
            zs.next_out = out.data();
            zs.avail_out = e.size;
            const int rc = inflate(&zs, Z_FINISH);
            inflateEnd(&zs);
            return rc == Z_STREAM_END;
        }

    private:
        struct Entry {
            uint16_t method;
            uint32_t compSize;
            uint32_t size;
            uint32_t localOffset;
        };
        Bytes mData;
        std::unordered_map<std::string, Entry> mEntries;
    };

    // --- minimal zip writer ------------------------------------------------------

    class ZipWriter {
    public:
        bool Add(const std::string& name, const Bytes& data) {
            Bytes comp;
            z_stream zs {};
            if (deflateInit2(&zs, 9, Z_DEFLATED, -15, 8, Z_DEFAULT_STRATEGY) != Z_OK) {
                return false;
            }
            comp.resize(deflateBound(&zs, uLong(data.size())));
            zs.next_in = const_cast<Bytef*>(data.data());
            zs.avail_in = uInt(data.size());
            zs.next_out = comp.data();
            zs.avail_out = uInt(comp.size());
            const int rc = deflate(&zs, Z_FINISH);
            comp.resize(zs.total_out);
            deflateEnd(&zs);
            if (rc != Z_STREAM_END) {
                return false;
            }
            const uint32_t crc = uint32_t(crc32(0L, data.data(), uInt(data.size())));
            const uint32_t offset = uint32_t(mOut.size());

            PutLE32(mOut, 0x04034B50);
            PutLE16(mOut, 20);   // version needed
            PutLE16(mOut, 0);    // flags
            PutLE16(mOut, 8);    // deflate
            PutLE16(mOut, 0);    // time
            PutLE16(mOut, 0x21); // date (1980-01-01)
            PutLE32(mOut, crc);
            PutLE32(mOut, uint32_t(comp.size()));
            PutLE32(mOut, uint32_t(data.size()));
            PutLE16(mOut, uint16_t(name.size()));
            PutLE16(mOut, 0);
            mOut.insert(mOut.end(), name.begin(), name.end());
            mOut.insert(mOut.end(), comp.begin(), comp.end());

            PutLE32(mDir, 0x02014B50);
            PutLE16(mDir, 20); // made by
            PutLE16(mDir, 20); // needed
            PutLE16(mDir, 0);
            PutLE16(mDir, 8);
            PutLE16(mDir, 0);
            PutLE16(mDir, 0x21);
            PutLE32(mDir, crc);
            PutLE32(mDir, uint32_t(comp.size()));
            PutLE32(mDir, uint32_t(data.size()));
            PutLE16(mDir, uint16_t(name.size()));
            PutLE16(mDir, 0); // extra
            PutLE16(mDir, 0); // comment
            PutLE16(mDir, 0); // disk
            PutLE16(mDir, 0); // internal attrs
            PutLE32(mDir, 0); // external attrs
            PutLE32(mDir, offset);
            mDir.insert(mDir.end(), name.begin(), name.end());
            mCount++;
            return mCount < 0xFFFF;
        }

        bool Save(const fs::path& path) {
            const uint32_t dirOffset = uint32_t(mOut.size());
            mOut.insert(mOut.end(), mDir.begin(), mDir.end());
            PutLE32(mOut, 0x06054B50);
            PutLE16(mOut, 0);
            PutLE16(mOut, 0);
            PutLE16(mOut, uint16_t(mCount));
            PutLE16(mOut, uint16_t(mCount));
            PutLE32(mOut, uint32_t(mDir.size()));
            PutLE32(mOut, dirOffset);
            PutLE16(mOut, 0);
            std::ofstream f(path, std::ios::binary | std::ios::trunc);
            f.write(reinterpret_cast<const char*>(mOut.data()), std::streamsize(mOut.size()));
            return bool(f);
        }

    private:
        Bytes mOut;
        Bytes mDir;
        uint32_t mCount = 0;
    };

    // --- pack building ---------------------------------------------------------------

    LanguagePackResult Fail(std::string message) {
        return { false, std::move(message) };
    }

    // section -> message offsets, relative to the language's message block.
    bool ReadMessageOffsets(const Bytes& block, std::vector<std::vector<uint32_t>>& offsets) {
        std::vector<uint32_t> sections;
        for (size_t pos = 0; pos + 4 <= block.size() && pos < 4 * (kSectionCount + 1); pos += 4) {
            const uint32_t off = ReadBE32(block, pos);
            if (off == 0) {
                break;
            }
            sections.push_back(off);
        }
        if (sections.size() != kSectionCount) {
            return false;
        }
        for (uint32_t sectionOffset : sections) {
            std::vector<uint32_t> entries;
            size_t pos = sectionOffset;
            while (pos + 4 <= block.size()) {
                const uint32_t off = ReadBE32(block, pos);
                if (off == sectionOffset) {
                    break;
                }
                entries.push_back(off);
                pos += 4;
            }
            offsets.push_back(std::move(entries));
        }
        return true;
    }

    LanguagePackResult BuildPack(const Bytes& rom, const ZipReader& us, int lang, const fs::path& outFile) {
        const MsgRange range = kMsgRanges[lang];
        const Bytes block(rom.begin() + range.start, rom.begin() + range.end);
        std::vector<std::vector<uint32_t>> offsets;
        if (!ReadMessageOffsets(block, offsets)) {
            return Fail(std::string("Unexpected message layout for ") + kLangCodes[lang]);
        }

        Bytes none;
        if (!us.Read("messages/MSG_NONE", none) || none.size() < kMsgHeader + 4) {
            return Fail("pm64.o2r has no message template");
        }
        const Bytes header(none.begin(), none.begin() + kMsgHeader);

        ZipWriter zip;
        for (const PalMessage& m : kPalMessages) {
            if (m.section >= offsets.size() || m.index >= offsets[m.section].size()) {
                return Fail(std::string("Missing message ") + m.name);
            }
            const uint32_t off = offsets[m.section][m.index];
            const uint32_t next =
                m.index + 1 < offsets[m.section].size() ? offsets[m.section][m.index + 1] : uint32_t(block.size());
            const auto end = std::find(block.begin() + off, block.end(), uint8_t(0xFD));
            if (end == block.end() || size_t(end - block.begin()) >= next) {
                return Fail(std::string("Bad message bounds for ") + m.name);
            }
            Bytes entry = header;
            PutLE32(entry, uint32_t(end - (block.begin() + off) + 1));
            entry.insert(entry.end(), block.begin() + off, end + 1);
            if (!zip.Add(std::string("messages/MSG_") + m.name, entry)) {
                return Fail("Cannot write the language pack");
            }
        }

        // PAL's standard glyph sheet: same layout as US plus the accented letters.
        for (int i = 0; i < kGlyphCount; i++) {
            const std::string path = "charset/charset_standard_" + std::to_string(i);
            Bytes original;
            if (!us.Read(path, original) || original.size() != kTexHeader + kGlyphBytes) {
                return Fail("Unexpected glyph resource " + path);
            }
            const uint32_t src = kFontStart + uint32_t(i) * kGlyphBytes;
            std::copy(rom.begin() + src, rom.begin() + src + kGlyphBytes, original.begin() + kTexHeader);
            if (!zip.Add(path, original)) {
                return Fail("Cannot write the language pack");
            }
        }
        Bytes font;
        if (us.Read("charset/charset_standard", font) && font.size() >= kMsgHeader + 4
            && ReadLE32(&font[kMsgHeader]) == kFontBlobSize && font.size() >= kMsgHeader + 4 + kFontBlobSize)
        {
            std::copy(
                rom.begin() + kFontStart, rom.begin() + kFontStart + kFontBlobSize, font.begin() + kMsgHeader + 4
            );
            zip.Add("charset/charset_standard", font);
        }

        // Localized images: replace the pixels, keep the US resource header.
        for (const PalImage& img : kPalImages) {
            if (img.lang != lang) {
                continue;
            }
            Bytes original;
            if (!us.Read(img.path, original) || original.size() != kTexHeader + img.size) {
                return Fail(std::string("Unexpected image resource ") + img.path);
            }
            std::copy(rom.begin() + img.offset, rom.begin() + img.offset + img.size, original.begin() + kTexHeader);
            if (!zip.Add(img.path, original)) {
                return Fail("Cannot write the language pack");
            }
        }

        if (!zip.Save(outFile)) {
            return Fail("Cannot write " + outFile.string());
        }
        return { true, {} };
    }

} // namespace

LanguagePackResult ValidatePalRom(const fs::path& path) {
    std::error_code ec;
    const auto size = fs::file_size(path, ec);
    if (ec || (size != kRomFull && size != kRomTrimmed)) {
        return Fail("This is not a European (PAL) Paper Mario ROM: unexpected size.");
    }
    Bytes rom;
    if (!ReadFile(path, rom)) {
        return Fail("Cannot read the ROM file.");
    }
    if (rom.size() < 4 || ReadBE32(rom, 0) != 0x80371240) {
        return Fail("The ROM must be in big-endian (.z64) byte order.");
    }
    const std::string sha = Sha1Hex(rom.data(), rom.size());
    if (sha != (size == kRomFull ? kShaFull : kShaTrimmed)) {
        return Fail("This ROM does not match the European (NUS-NMQP-EUR) release.");
    }
    return { true, {} };
}

LanguagePackResult BuildLanguagePacks(
    const fs::path& palRom, const fs::path& usArchive, const fs::path& outDir, LanguagePackProgress* progress
) {
    struct Running {
        LanguagePackProgress* p;
        explicit Running(LanguagePackProgress* p_)
            : p(p_) {
            if (p) {
                p->running = true;
                p->percent = 0;
            }
        }
        ~Running() {
            if (p) {
                p->running = false;
            }
        }
    } running(progress);

    const LanguagePackResult valid = ValidatePalRom(palRom);
    if (!valid.ok) {
        return valid;
    }
    Bytes rom;
    if (!ReadFile(palRom, rom)) {
        return Fail("Cannot read the ROM file.");
    }
    if (progress) {
        progress->percent = 10;
    }

    ZipReader us;
    std::string error;
    if (!us.Open(usArchive, error)) {
        return Fail(error);
    }
    if (progress) {
        progress->percent = 25;
    }

    std::error_code ec;
    fs::create_directories(outDir, ec);
    std::vector<std::pair<fs::path, fs::path>> written; // temp -> final
    for (int lang : { kLangDe, kLangFr, kLangEs }) {
        const fs::path finalPath = outDir / (std::string("lang_") + kLangCodes[lang] + ".o2r");
        const fs::path tmpPath = finalPath.string() + ".tmp";
        const LanguagePackResult r = BuildPack(rom, us, lang, tmpPath);
        if (!r.ok) {
            for (auto& w : written) {
                fs::remove(w.first, ec);
            }
            fs::remove(tmpPath, ec);
            return r;
        }
        written.emplace_back(tmpPath, finalPath);
        if (progress) {
            progress->percent = 25 + 25 * int(written.size());
        }
    }
    // Only replace existing packs once all of them built.
    for (auto& w : written) {
        fs::rename(w.first, w.second, ec);
        if (ec) {
            return Fail("Cannot write " + w.second.string());
        }
    }
    if (progress) {
        progress->percent = 100;
    }
    return { true, "Language packs created. Restart to use them." };
}

int RunBuildLanguagePacksCli(int argc, char** argv) {
    // argv[1] is the flag itself.
    const fs::path rom = argc > 2 ? argv[2] : "";
    const fs::path archive = argc > 3 ? fs::path(argv[3]) : fs::path("pm64.o2r");
    const fs::path outDir = argc > 4 ? fs::path(argv[4]) : fs::path("langpacks");
    const LanguagePackResult r = BuildLanguagePacks(rom, archive, outDir);
    std::fprintf(r.ok ? stdout : stderr, "%s\n", r.message.c_str());
    return r.ok ? 0 : 1;
}

} // namespace Paperboat
