#include "audio.h"
#include "audio/core.h"

void au_load_BK_headers(AuGlobals* globals, ALHeap* heap) {
    SBNFileEntry fileEntry;
    InitBankEntry* buffer = au_read_rom(globals->bkFileListOffset);
    s32 i;

    for (i = 0; i < INIT_BANK_BUFFER_SIZE; i++) {
        // Data is now native-endian after torch extraction (PM64:AUDIO factory)
        u16 fileIndex = buffer[i].fileIndex;
        if (fileIndex == 0xFFFF) {
            break;
        }

        AuResult res = au_fetch_SBN_file(fileIndex, AU_FMT_BK, &fileEntry);
        if (res == AU_RESULT_OK) {
            au_load_BK_to_bank(fileEntry.offset, nullptr, buffer[i].bankIndex, buffer[i].bankSet);
        }
    }
}
