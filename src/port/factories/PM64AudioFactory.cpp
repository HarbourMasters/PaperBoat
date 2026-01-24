#include "PM64AudioFactory.h"
#include "Companion.h"
#include "spdlog/spdlog.h"
#include <ship/utils/binarytools/endianness.h>
#include <set>

// SBN file format constants
#define SBN_SIGNATURE 0x53424E20  // 'SBN '
#define INIT_SIGNATURE 0x494E4954 // 'INIT'
#define BGM_SIGNATURE 0x42474D20  // 'BGM '
#define SEF_SIGNATURE 0x53454620  // 'SEF '
#define PER_SIGNATURE 0x50455220  // 'PER '
#define PRG_SIGNATURE 0x50524720  // 'PRG '
#define BK_SIGNATURE 0x424B      // 'BK'
#define MSEQ_SIGNATURE 0x4D534551 // 'MSEQ'

// Audio file format types (upper byte of SBNFileEntry.data)
// NOTE: PER and PRG share format 0x40 with MSEQ; distinguished by file signature
#define AU_FMT_BGM  0x10
#define AU_FMT_SEF  0x20
#define AU_FMT_BK   0x30
#define AU_FMT_MSEQ 0x40

// Structure sizes
#define SBN_HEADER_SIZE     0x40
#define SBN_FILE_ENTRY_SIZE 8
#define INIT_HEADER_SIZE    0x20
#define INIT_SONG_ENTRY_SIZE 8
#define INIT_BANK_ENTRY_SIZE 4
#define BGM_HEADER_SIZE     0x24
#define BK_HEADER_SIZE      0x40
#define SEF_HEADER_SIZE     0x22
#define MSEQ_HEADER_SIZE    0x18
#define PER_HEADER_SIZE     0x10

// SEF section entry counts (from game code)
#define SEF_SECTION_0_3_ENTRIES 0xC0  // 192 entries for sections 0-3
#define SEF_SECTION_4_7_ENTRIES 0x40  // 64 entries for sections 4-7
#define SEF_EXTRA_ENTRIES       0x140 // 320 entries for extra section

// BGMDrumInfo size
#define BGM_DRUM_INFO_SIZE 0x0C
// BGMInstrumentInfo size
#define BGM_INSTRUMENT_INFO_SIZE 0x08
// PEREntry size (12 drums)
#define PER_ENTRY_SIZE (12 * BGM_DRUM_INFO_SIZE) // 0x90

// Helper to check bounds
#define CHECK_BOUNDS(offset, size, totalSize) ((offset) + (size) <= (totalSize))

static void ByteSwapAudioData(uint8_t* data, size_t size) {
    if (size < SBN_HEADER_SIZE) {
        SPDLOG_WARN("Audio data too small for SBN header: {}", size);
        return;
    }

    // === SBN Header ===
    // Offsets: 0x00 signature (s32), 0x04 size (s32), 0x10 fileListOffset (s32),
    //          0x14 numEntries (s32), 0x18 fullFileSize (s32), 0x1C versionOffset (s32),
    //          0x24 INIToffset (s32)
    uint32_t* header32 = reinterpret_cast<uint32_t*>(data);

    // Byte-swap the header fields we need
    uint32_t signature = BSWAP32(header32[0]);
    header32[0] = signature;
    header32[1] = BSWAP32(header32[1]); // size

    uint32_t fileListOffset = BSWAP32(header32[4]); // 0x10
    uint32_t numEntries = BSWAP32(header32[5]);      // 0x14
    uint32_t fullFileSize = BSWAP32(header32[6]);    // 0x18
    uint32_t versionOffset = BSWAP32(header32[7]);   // 0x1C
    uint32_t initOffset = BSWAP32(header32[9]);      // 0x24

    header32[4] = fileListOffset;
    header32[5] = numEntries;
    header32[6] = fullFileSize;
    header32[7] = versionOffset;
    header32[9] = initOffset;

    SPDLOG_DEBUG("SBN: signature=0x{:08X}, fileListOffset=0x{:X}, numEntries={}, initOffset=0x{:X}",
                 signature, fileListOffset, numEntries, initOffset);

    if (signature != SBN_SIGNATURE) {
        SPDLOG_ERROR("Invalid SBN signature: 0x{:08X}", signature);
        return;
    }

    // === SBN File Entry Array ===
    // Each entry: s32 offset, u32 data
    if (CHECK_BOUNDS(fileListOffset, numEntries * SBN_FILE_ENTRY_SIZE, size)) {
        uint32_t* entries = reinterpret_cast<uint32_t*>(data + fileListOffset);
        for (uint32_t i = 0; i < numEntries; i++) {
            uint32_t offset = BSWAP32(entries[i * 2]);
            uint32_t entryData = BSWAP32(entries[i * 2 + 1]);
            entries[i * 2] = offset;
            entries[i * 2 + 1] = entryData;

            // Stop if we hit an invalid entry
            if ((offset & 0xFFFFFF) == 0) {
                break;
            }

            // Get the file type and offset within SBN
            uint8_t fileType = (entryData >> 24) & 0xFF;
            uint32_t fileOffset = offset & 0xFFFFFF;
            uint32_t fileSize = entryData & 0xFFFFFF;

            // Byte-swap the embedded file based on type
            if (fileOffset > 0 && CHECK_BOUNDS(fileOffset, 8, size)) {
                uint8_t* fileData = data + fileOffset;

                switch (fileType) {
                    case AU_FMT_BGM: {
                        // BGM Header: s32 signature, s32 size, s32 name, pad[4], BGMFileInfo
                        if (CHECK_BOUNDS(fileOffset, BGM_HEADER_SIZE, size)) {
                            uint32_t* bgm32 = reinterpret_cast<uint32_t*>(fileData);
                            bgm32[0] = BSWAP32(bgm32[0]); // signature
                            uint32_t bgmFileSize = BSWAP32(bgm32[1]);
                            bgm32[1] = bgmFileSize; // size
                            bgm32[2] = BSWAP32(bgm32[2]); // name
                            // pad at 0x0C

                            // BGMFileInfo at offset 0x10:
                            // u8 timingPreset, pad[3], u16 compositions[4], u16 drums, u16 drumCount, u16 instruments, u16 instrumentCount
                            uint16_t* bgm16 = reinterpret_cast<uint16_t*>(fileData + 0x14);
                            bgm16[0] = BSWAP16(bgm16[0]); // compositions[0]
                            bgm16[1] = BSWAP16(bgm16[1]); // compositions[1]
                            bgm16[2] = BSWAP16(bgm16[2]); // compositions[2]
                            bgm16[3] = BSWAP16(bgm16[3]); // compositions[3]
                            bgm16[4] = BSWAP16(bgm16[4]); // drums
                            bgm16[5] = BSWAP16(bgm16[5]); // drumCount
                            bgm16[6] = BSWAP16(bgm16[6]); // instruments
                            bgm16[7] = BSWAP16(bgm16[7]); // instrumentCount

                            // Swap composition data (SegData/u32 command arrays) and phrase track entries
                            // The BGM player reads these as u32 via SegData* pointers
                            std::set<uint32_t> swappedPhrases;
                            for (int comp = 0; comp < 4; comp++) {
                                uint16_t compOff = bgm16[comp]; // already swapped
                                if (compOff == 0) continue;

                                uint32_t compAbsOff = fileOffset + compOff * 4;
                                uint32_t* cmdPtr = reinterpret_cast<uint32_t*>(data + compAbsOff);

                                // Walk composition commands until BGM_COMP_END (0x00000000)
                                while (compAbsOff + 4 <= size) {
                                    uint32_t raw = *cmdPtr;
                                    if (raw == 0) break; // BGM_COMP_END is 0 in both endiannesses
                                    uint32_t swapped = BSWAP32(raw);
                                    *cmdPtr = swapped;

                                    // Check for PLAY_PHRASE command (top nibble = 1)
                                    if (((swapped >> 28) & 0xF) == 1) {
                                        // Phrase offset is relative to compStartPos, in u32 units
                                        uint16_t phraseRelOff = swapped & 0xFFFF;
                                        uint32_t phraseAbsOff = fileOffset + compOff * 4 + phraseRelOff * 4;
                                        if (swappedPhrases.find(phraseAbsOff) == swappedPhrases.end()
                                            && CHECK_BOUNDS(phraseAbsOff, 16 * 4, size)) {
                                            swappedPhrases.insert(phraseAbsOff);
                                            // Swap 16 u32 track info entries
                                            uint32_t* phrasePtr = reinterpret_cast<uint32_t*>(data + phraseAbsOff);
                                            for (int t = 0; t < 16; t++) {
                                                phrasePtr[t] = BSWAP32(phrasePtr[t]);
                                            }
                                        }
                                    }
                                    cmdPtr++;
                                    compAbsOff += 4;
                                }
                            }

                            // Swap BGMDrumInfo entries (u16 bankPatch at +0, u16 keyBase at +2)
                            uint16_t drumsOff = bgm16[4];
                            uint16_t drumCount = bgm16[5];
                            if (drumsOff != 0 && drumCount > 0) {
                                uint32_t drumsAbsOff = fileOffset + drumsOff * 4;
                                for (uint16_t d = 0; d < drumCount; d++) {
                                    uint32_t drumEntryOff = drumsAbsOff + d * BGM_DRUM_INFO_SIZE;
                                    if (CHECK_BOUNDS(drumEntryOff, BGM_DRUM_INFO_SIZE, size)) {
                                        uint16_t* drum16 = reinterpret_cast<uint16_t*>(data + drumEntryOff);
                                        drum16[0] = BSWAP16(drum16[0]); // bankPatch
                                        drum16[1] = BSWAP16(drum16[1]); // keyBase
                                    }
                                }
                            }

                            // Swap BGMInstrumentInfo entries (u16 bankPatch at +0)
                            uint16_t instrOff = bgm16[6];
                            uint16_t instrCount = bgm16[7];
                            if (instrOff != 0 && instrCount > 0) {
                                uint32_t instrAbsOff = fileOffset + instrOff * 4;
                                for (uint16_t ins = 0; ins < instrCount; ins++) {
                                    uint32_t instrEntryOff = instrAbsOff + ins * BGM_INSTRUMENT_INFO_SIZE;
                                    if (CHECK_BOUNDS(instrEntryOff, BGM_INSTRUMENT_INFO_SIZE, size)) {
                                        uint16_t* instr16 = reinterpret_cast<uint16_t*>(data + instrEntryOff);
                                        instr16[0] = BSWAP16(instr16[0]); // bankPatch
                                    }
                                }
                            }
                        }
                        break;
                    }

                    case AU_FMT_BK: {
                        // BK Header: u16 signature, pad[2], s32 size, s32 name, u16 format, u8 swizzled, pad[3],
                        //            u16 instruments[16], u16 instrumentsLength, u16 loopStatesStart, u16 loopStatesLength,
                        //            u16 predictorsStart, u16 predictorsLength, u16 envelopesStart, u16 envelopesLength
                        if (CHECK_BOUNDS(fileOffset, BK_HEADER_SIZE, size)) {
                            uint16_t* bk16 = reinterpret_cast<uint16_t*>(fileData);
                            bk16[0] = BSWAP16(bk16[0]); // signature
                            // pad at 0x02

                            uint32_t* bk32 = reinterpret_cast<uint32_t*>(fileData + 0x04);
                            uint32_t bkSize = BSWAP32(bk32[0]); // size
                            bk32[0] = bkSize;
                            bk32[1] = BSWAP32(bk32[1]); // name

                            bk16 = reinterpret_cast<uint16_t*>(fileData + 0x0C);
                            bk16[0] = BSWAP16(bk16[0]); // format
                            // swizzled (u8) and pad at 0x0E-0x11

                            // instruments[16] at 0x12 - swap and save offsets for instrument data swapping
                            uint16_t instrumentOffsets[16];
                            bk16 = reinterpret_cast<uint16_t*>(fileData + 0x12);
                            for (int j = 0; j < 16; j++) {
                                instrumentOffsets[j] = BSWAP16(bk16[j]);
                                bk16[j] = instrumentOffsets[j];
                            }

                            // More u16 fields at 0x32
                            bk16 = reinterpret_cast<uint16_t*>(fileData + 0x32);
                            bk16[0] = BSWAP16(bk16[0]); // instrumentsLength
                            bk16[1] = BSWAP16(bk16[1]); // loopStatesStart
                            bk16[2] = BSWAP16(bk16[2]); // loopStatesLength
                            bk16[3] = BSWAP16(bk16[3]); // predictorsStart
                            bk16[4] = BSWAP16(bk16[4]); // predictorsLength
                            bk16[5] = BSWAP16(bk16[5]); // envelopesStart
                            bk16[6] = BSWAP16(bk16[6]); // envelopesLength

                            // Save region offsets/lengths for data swapping below
                            uint16_t loopStatesStart = bk16[1];
                            uint16_t loopStatesLength = bk16[2];
                            uint16_t predictorsStart = bk16[3];
                            uint16_t predictorsLength = bk16[4];

                            // Now swap each Instrument structure within the BK file
                            // Instrument structure (0x30 bytes):
                            // 0x00: u32 wavData (offset)
                            // 0x04: u32 wavDataLength
                            // 0x08: u32 loopState (offset)
                            // 0x0C: s32 loopStart
                            // 0x10: s32 loopEnd
                            // 0x14: s32 loopCount
                            // 0x18: u32 predictor (offset)
                            // 0x1C: u16 codebookSize
                            // 0x1E: u16 keyBase
                            // 0x20: s32 sampleRate
                            // 0x24-0x2B: u8 fields (no swap needed)
                            // 0x2C: u32 envelopes (offset)

                            // Track which envelope presets we've already swapped (multiple instruments may share one)
                            std::set<uint32_t> swappedEnvelopes;

                            for (int j = 0; j < 16; j++) {
                                uint16_t instOffset = instrumentOffsets[j];
                                if (instOffset != 0 && CHECK_BOUNDS(fileOffset + instOffset, 0x30, size)) {
                                    uint8_t* instData = fileData + instOffset;
                                    uint32_t* inst32 = reinterpret_cast<uint32_t*>(instData);

                                    inst32[0] = BSWAP32(inst32[0]); // wavData
                                    inst32[1] = BSWAP32(inst32[1]); // wavDataLength
                                    inst32[2] = BSWAP32(inst32[2]); // loopState
                                    inst32[3] = BSWAP32(inst32[3]); // loopStart
                                    inst32[4] = BSWAP32(inst32[4]); // loopEnd
                                    inst32[5] = BSWAP32(inst32[5]); // loopCount
                                    inst32[6] = BSWAP32(inst32[6]); // predictor

                                    uint16_t* inst16 = reinterpret_cast<uint16_t*>(instData + 0x1C);
                                    inst16[0] = BSWAP16(inst16[0]); // codebookSize
                                    inst16[1] = BSWAP16(inst16[1]); // keyBase

                                    inst32 = reinterpret_cast<uint32_t*>(instData + 0x20);
                                    inst32[0] = BSWAP32(inst32[0]); // sampleRate
                                    // 0x24-0x2B are u8 fields, no swap needed

                                    inst32 = reinterpret_cast<uint32_t*>(instData + 0x2C);
                                    uint32_t envOffset = BSWAP32(inst32[0]);
                                    inst32[0] = envOffset; // envelopes

                                    // Swap EnvelopePreset data if not already done
                                    // EnvelopePreset: u8 count, pad[3], EnvelopeOffset offsets[count]
                                    // EnvelopeOffset: u16 offsetPress, u16 offsetRelease
                                    if (envOffset != 0 && swappedEnvelopes.find(envOffset) == swappedEnvelopes.end()) {
                                        uint32_t envAbsOff = fileOffset + envOffset;
                                        if (CHECK_BOUNDS(envAbsOff, 4, size)) {
                                            uint8_t envCount = data[envAbsOff]; // u8, no swap
                                            // Swap each EnvelopeOffset entry (4 bytes each)
                                            for (uint8_t e = 0; e < envCount; e++) {
                                                uint32_t entryOff = envAbsOff + 4 + e * 4;
                                                if (CHECK_BOUNDS(entryOff, 4, size)) {
                                                    uint16_t* envEntry = reinterpret_cast<uint16_t*>(data + entryOff);
                                                    envEntry[0] = BSWAP16(envEntry[0]); // offsetPress
                                                    envEntry[1] = BSWAP16(envEntry[1]); // offsetRelease
                                                }
                                            }
                                            swappedEnvelopes.insert(envOffset);
                                        }
                                    }
                                }
                            }

                            // Swap predictor codebook data (s16 array)
                            if (predictorsStart > 0 && predictorsLength > 0) {
                                uint32_t predAbsOff = fileOffset + predictorsStart;
                                if (CHECK_BOUNDS(predAbsOff, predictorsLength, size)) {
                                    uint16_t* predData = reinterpret_cast<uint16_t*>(data + predAbsOff);
                                    uint32_t numShorts = predictorsLength / 2;
                                    for (uint32_t p = 0; p < numShorts; p++) {
                                        predData[p] = BSWAP16(predData[p]);
                                    }
                                    SPDLOG_DEBUG("BK: swapped {} predictor shorts at offset 0x{:X}", numShorts, predictorsStart);
                                }
                            }

                            // Swap loop state data (s16 array)
                            if (loopStatesStart > 0 && loopStatesLength > 0) {
                                uint32_t loopAbsOff = fileOffset + loopStatesStart;
                                if (CHECK_BOUNDS(loopAbsOff, loopStatesLength, size)) {
                                    uint16_t* loopData = reinterpret_cast<uint16_t*>(data + loopAbsOff);
                                    uint32_t numShorts = loopStatesLength / 2;
                                    for (uint32_t l = 0; l < numShorts; l++) {
                                        loopData[l] = BSWAP16(loopData[l]);
                                    }
                                    SPDLOG_DEBUG("BK: swapped {} loop state shorts at offset 0x{:X}", numShorts, loopStatesStart);
                                }
                            }
                        }
                        break;
                    }

                    case AU_FMT_SEF: {
                        // SEF Header: s32 signature, s32 size, s32 name, pad[2], u8 hasExtraSection, pad[1],
                        //             u16 sections[8], u16 section2000
                        if (CHECK_BOUNDS(fileOffset, SEF_HEADER_SIZE, size)) {
                            uint32_t* sef32 = reinterpret_cast<uint32_t*>(fileData);
                            sef32[0] = BSWAP32(sef32[0]); // signature
                            uint32_t sefSize = BSWAP32(sef32[1]); // size
                            sef32[1] = sefSize;
                            sef32[2] = BSWAP32(sef32[2]); // name
                            // pad and u8 at 0x0C-0x0F

                            // Swap header section offsets and save them
                            uint16_t* sef16 = reinterpret_cast<uint16_t*>(fileData + 0x10);
                            uint16_t sectionOffsets[9]; // sections[8] + section2000
                            for (int j = 0; j < 9; j++) {
                                sectionOffsets[j] = BSWAP16(sef16[j]);
                                sef16[j] = sectionOffsets[j];
                            }

                            // SEF section layout:
                            // - Sections 0-3: lookup tables of (u16 offset, u16 info) pairs + polyphonic sub-tables
                            //   Game code dereferences offset via AU_FILE_RELATIVE -> must be swapped
                            // - Sections 4-7 and extra: raw command bytes passed directly as (u8*)cmdList
                            //   Game code reads byte-by-byte -> must NOT be swapped

                            // Track swapped sub-table offsets to avoid double-swapping
                            std::set<uint16_t> swappedSubTables;

                            // Swap sections 0-3 lookup tables
                            for (int j = 0; j < 4; j++) {
                                if (sectionOffsets[j] == 0) continue;
                                uint32_t secAbsOff = fileOffset + sectionOffsets[j];
                                uint32_t entryCount = SEF_SECTION_0_3_ENTRIES;
                                if (!CHECK_BOUNDS(secAbsOff, entryCount * 4, size)) continue;

                                uint16_t* entries = reinterpret_cast<uint16_t*>(data + secAbsOff);
                                for (uint32_t k = 0; k < entryCount; k++) {
                                    uint16_t cmdOffset = BSWAP16(entries[k * 2]);
                                    uint16_t cmdInfo = BSWAP16(entries[k * 2 + 1]);
                                    entries[k * 2] = cmdOffset;
                                    entries[k * 2 + 1] = cmdInfo;

                                    if (cmdOffset == 0) continue;

                                    // Check for polyphonic entries (bits 5-6 of info)
                                    uint8_t polyphonyMode = (cmdInfo & 0x60) >> 5;
                                    if (polyphonyMode != 0 && swappedSubTables.find(cmdOffset) == swappedSubTables.end()) {
                                        // Follow offset to polyphonic sub-table and swap it
                                        uint32_t trackCount = 2 << (polyphonyMode - 1); // 2, 4, or 8
                                        uint32_t subTableAbsOff = fileOffset + cmdOffset;
                                        if (CHECK_BOUNDS(subTableAbsOff, trackCount * 4, size)) {
                                            uint16_t* subEntries = reinterpret_cast<uint16_t*>(data + subTableAbsOff);
                                            for (uint32_t t = 0; t < trackCount; t++) {
                                                subEntries[t * 2] = BSWAP16(subEntries[t * 2]);     // offset
                                                subEntries[t * 2 + 1] = BSWAP16(subEntries[t * 2 + 1]); // info
                                            }
                                        }
                                        swappedSubTables.insert(cmdOffset);
                                    }
                                }
                            }

                            // Sections 4-7: raw command bytes, no swap needed
                            // Extra section (section2000): raw command bytes, no swap needed

                            SPDLOG_DEBUG("SEF: swapped {} section 0-3 lookup tables, {} polyphonic sub-tables",
                                         4, swappedSubTables.size());
                        }
                        break;
                    }

                    case AU_FMT_MSEQ: {
                        // Format 0x40 is shared by MSEQ, PER, and PRG files.
                        // Distinguish by reading the big-endian signature before swapping.
                        uint32_t fileSig = BSWAP32(*reinterpret_cast<uint32_t*>(fileData));

                        if (fileSig == PER_SIGNATURE) {
                            // PER file: s32 signature, s32 size, pad[8], then PEREntry data
                            // PEREntry = 12 × BGMDrumInfo (0x0C bytes each) = 0x90 bytes
                            // BGMDrumInfo: u16 bankPatch, u16 keyBase, u8 volume, s8 pan, u8 reverb, ...
                            if (CHECK_BOUNDS(fileOffset, PER_HEADER_SIZE, size)) {
                                uint32_t* per32 = reinterpret_cast<uint32_t*>(fileData);
                                per32[0] = BSWAP32(per32[0]); // signature
                                uint32_t perSize = BSWAP32(per32[1]);
                                per32[1] = perSize; // size

                                // Swap internal BGMDrumInfo entries
                                uint32_t dataStart = PER_HEADER_SIZE;
                                uint32_t dataLen = perSize - dataStart;
                                uint32_t numDrums = dataLen / BGM_DRUM_INFO_SIZE;
                                for (uint32_t d = 0; d < numDrums; d++) {
                                    uint32_t drumOff = fileOffset + dataStart + d * BGM_DRUM_INFO_SIZE;
                                    if (CHECK_BOUNDS(drumOff, BGM_DRUM_INFO_SIZE, size)) {
                                        uint16_t* drum16 = reinterpret_cast<uint16_t*>(data + drumOff);
                                        drum16[0] = BSWAP16(drum16[0]); // bankPatch
                                        drum16[1] = BSWAP16(drum16[1]); // keyBase
                                        // remaining fields are u8, no swap
                                    }
                                }
                                SPDLOG_DEBUG("PER: swapped {} drum entries", numDrums);
                            }
                        } else if (fileSig == PRG_SIGNATURE) {
                            // PRG file: s32 signature, s32 size, pad[8], then BGMInstrumentInfo data
                            // BGMInstrumentInfo: u16 bankPatch, u8 volume, s8 pan, u8 reverb, s8 coarseTune, s8 fineTune, pad
                            if (CHECK_BOUNDS(fileOffset, PER_HEADER_SIZE, size)) {
                                uint32_t* prg32 = reinterpret_cast<uint32_t*>(fileData);
                                prg32[0] = BSWAP32(prg32[0]); // signature
                                uint32_t prgSize = BSWAP32(prg32[1]);
                                prg32[1] = prgSize; // size

                                // Swap internal BGMInstrumentInfo entries
                                uint32_t dataStart = PER_HEADER_SIZE;
                                uint32_t dataLen = prgSize - dataStart;
                                uint32_t numInst = dataLen / BGM_INSTRUMENT_INFO_SIZE;
                                for (uint32_t p = 0; p < numInst; p++) {
                                    uint32_t instOff = fileOffset + dataStart + p * BGM_INSTRUMENT_INFO_SIZE;
                                    if (CHECK_BOUNDS(instOff, BGM_INSTRUMENT_INFO_SIZE, size)) {
                                        uint16_t* inst16 = reinterpret_cast<uint16_t*>(data + instOff);
                                        inst16[0] = BSWAP16(inst16[0]); // bankPatch
                                        // remaining fields are u8/s8, no swap
                                    }
                                }
                                SPDLOG_DEBUG("PRG: swapped {} instrument entries", numInst);
                            }
                        } else {
                            // MSEQ file
                            // MSEQ Header: s32 signature, s32 size, s32 name, u8 firstVoiceIdx, u8 trackSettingsCount,
                            //              u16 trackSettingsOffset, u16 dataStart, pad[6]
                            if (CHECK_BOUNDS(fileOffset, MSEQ_HEADER_SIZE, size)) {
                                uint32_t* mseq32 = reinterpret_cast<uint32_t*>(fileData);
                                mseq32[0] = BSWAP32(mseq32[0]); // signature
                                mseq32[1] = BSWAP32(mseq32[1]); // size
                                mseq32[2] = BSWAP32(mseq32[2]); // name
                                // u8 fields at 0x0C-0x0D

                                uint16_t* mseq16 = reinterpret_cast<uint16_t*>(fileData + 0x0E);
                                uint16_t trackSettingsOffset = BSWAP16(mseq16[0]);
                                mseq16[0] = trackSettingsOffset; // trackSettingsOffset
                                mseq16[1] = BSWAP16(mseq16[1]); // dataStart

                                // Swap MSEQTrackData entries
                                // Each entry: u8 trackIndex, u8 type, s16 time, s16 delta, s16 goal (8 bytes)
                                uint8_t trackSettingsCount = fileData[0x0D];
                                if (trackSettingsCount > 0 && trackSettingsOffset > 0) {
                                    for (uint8_t t = 0; t < trackSettingsCount; t++) {
                                        uint32_t entryOff = fileOffset + trackSettingsOffset + t * 8;
                                        if (CHECK_BOUNDS(entryOff, 8, size)) {
                                            uint16_t* td16 = reinterpret_cast<uint16_t*>(data + entryOff + 2);
                                            td16[0] = BSWAP16(td16[0]); // time
                                            td16[1] = BSWAP16(td16[1]); // delta
                                            td16[2] = BSWAP16(td16[2]); // goal
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    }

                    default:
                        // Unknown file type, skip
                        break;
                }
            }
        }
    }

    // === INIT Section ===
    if (initOffset > 0 && CHECK_BOUNDS(initOffset, INIT_HEADER_SIZE, size)) {
        uint8_t* initData = data + initOffset;

        // INIT Header: s32 signature, s32 size, u16 bankListOffset, u16 bankListSize,
        //              u16 songListOffset, u16 songListSize, u16 mseqListOffset, u16 mseqListSize, pad[12]
        uint32_t* init32 = reinterpret_cast<uint32_t*>(initData);
        init32[0] = BSWAP32(init32[0]); // signature
        init32[1] = BSWAP32(init32[1]); // size

        uint16_t* init16 = reinterpret_cast<uint16_t*>(initData + 0x08);
        uint16_t bankListOffset = BSWAP16(init16[0]);
        uint16_t bankListSize = BSWAP16(init16[1]);
        uint16_t songListOffset = BSWAP16(init16[2]);
        uint16_t songListSize = BSWAP16(init16[3]);
        uint16_t mseqListOffset = BSWAP16(init16[4]);
        uint16_t mseqListSize = BSWAP16(init16[5]);

        init16[0] = bankListOffset;
        init16[1] = bankListSize;
        init16[2] = songListOffset;
        init16[3] = songListSize;
        init16[4] = mseqListOffset;
        init16[5] = mseqListSize;

        SPDLOG_DEBUG("INIT: songListOffset=0x{:X}, songListSize={}, bankListOffset=0x{:X}, mseqListOffset=0x{:X}",
                     songListOffset, songListSize, bankListOffset, mseqListOffset);

        // === Song List (InitSongEntry array) ===
        // Each entry: u16 bgmFileIndex, u16 bkFileIndex[3]
        uint32_t songListAbsOffset = initOffset + songListOffset;
        uint32_t numSongs = songListSize / INIT_SONG_ENTRY_SIZE;
        if (songListOffset > 0 && CHECK_BOUNDS(songListAbsOffset, songListSize, size)) {
            uint16_t* songList = reinterpret_cast<uint16_t*>(data + songListAbsOffset);
            for (uint32_t i = 0; i < numSongs * 4; i++) { // 4 u16s per entry
                songList[i] = BSWAP16(songList[i]);
            }
        }

        // === Bank List (InitBankEntry array) ===
        // Each entry: u16 fileIndex, u8 bankIndex, u8 bankSet
        uint32_t bankListAbsOffset = initOffset + bankListOffset;
        uint32_t numBanks = bankListSize / INIT_BANK_ENTRY_SIZE;
        if (bankListOffset > 0 && CHECK_BOUNDS(bankListAbsOffset, bankListSize, size)) {
            // Only need to swap the u16 fileIndex, the u8 fields don't need swapping
            for (uint32_t i = 0; i < numBanks; i++) {
                uint16_t* bankEntry = reinterpret_cast<uint16_t*>(data + bankListAbsOffset + i * INIT_BANK_ENTRY_SIZE);
                bankEntry[0] = BSWAP16(bankEntry[0]); // fileIndex
            }
        }

        // === MSEQ/Extra File List (u16 array) ===
        // This is a simple array of u16 file indices
        uint32_t mseqListAbsOffset = initOffset + mseqListOffset;
        uint32_t numMseqEntries = mseqListSize / 2;
        if (mseqListOffset > 0 && CHECK_BOUNDS(mseqListAbsOffset, mseqListSize, size)) {
            uint16_t* mseqList = reinterpret_cast<uint16_t*>(data + mseqListAbsOffset);
            for (uint32_t i = 0; i < numMseqEntries; i++) {
                mseqList[i] = BSWAP16(mseqList[i]);
            }
        }
    }

    SPDLOG_DEBUG("PM64:AUDIO byte-swap complete, {} bytes processed", size);
}

std::optional<std::shared_ptr<IParsedData>> PM64AudioFactory::parse(std::vector<uint8_t>& buffer, YAML::Node& node) {
    auto offset = GetSafeNode<uint32_t>(node, "offset");
    auto size = GetSafeNode<size_t>(node, "size");

    if (offset + size > buffer.size()) {
        SPDLOG_ERROR("PM64:AUDIO offset 0x{:X} + size 0x{:X} exceeds buffer size 0x{:X}", offset, size, buffer.size());
        return std::nullopt;
    }

    // Copy the audio data
    std::vector<uint8_t> audioData(buffer.begin() + offset, buffer.begin() + offset + size);

    // Byte-swap for little-endian
    ByteSwapAudioData(audioData.data(), audioData.size());

    SPDLOG_INFO("PM64:AUDIO parsed at 0x{:X}, size: {} bytes", offset, audioData.size());

    return std::make_shared<RawBuffer>(audioData);
}

ExportResult PM64AudioBinaryExporter::Export(std::ostream& write, std::shared_ptr<IParsedData> raw, std::string& entryName, YAML::Node& node, std::string* replacement) {
    auto writer = LUS::BinaryWriter();
    auto data = std::static_pointer_cast<RawBuffer>(raw)->mBuffer;

    // Write as Blob type - game will load as raw binary
    WriteHeader(writer, Torch::ResourceType::Blob, 0);
    writer.Write(static_cast<uint32_t>(data.size()));
    writer.Write(reinterpret_cast<char*>(data.data()), data.size());
    writer.Finish(write);

    return std::nullopt;
}

ExportResult PM64AudioHeaderExporter::Export(std::ostream& write, std::shared_ptr<IParsedData> raw, std::string& entryName, YAML::Node& node, std::string* replacement) {
    const auto symbol = GetSafeNode(node, "symbol", entryName);

    if (Companion::Instance->IsOTRMode()) {
        write << "static const ALIGN_ASSET(2) char " << symbol << "[] = \"__OTR__" << (*replacement) << "\";\n\n";
        return std::nullopt;
    }

    write << "extern u8 " << symbol << "[];\n";
    return std::nullopt;
}
