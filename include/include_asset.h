#ifndef _H_INCLUDE_ASSET
#define _H_INCLUDE_ASSET

#define ASTRINGIFY_(x) #x
#define ASTRINGIFY(x) ASTRINGIFY_(x)

// ELF platforms (Linux) support .type directive
// Mach-O platforms (macOS) do not support it
// macOS also requires underscore prefix for C symbols in assembly
#ifdef __APPLE__
#  define TYPE_DIRECTIVE(SYMBOLNAME)
#  define ASM_SYMBOL_PREFIX "_"
#else
#  define TYPE_DIRECTIVE(SYMBOLNAME) ".type " #SYMBOLNAME", @object\n"
#  define ASM_SYMBOL_PREFIX ""
#endif

#if defined(MODERN_COMPILER) && !defined(__APPLE__)
#  define PUSHSECTION(SECTION) ".pushsection " SECTION "\n"
#  define POPSECTION ".popsection\n"
#else
#  define PUSHSECTION(SECTION) SECTION "\n"
#  define POPSECTION
#endif

#define _INCLUDE_IMG(FILENAME, SYMBOLNAME) \
    extern unsigned char SYMBOLNAME[]; \
    __asm__( \
        ".globl " ASM_SYMBOL_PREFIX #SYMBOLNAME"\n" \
        PUSHSECTION(".data") \
        ".p2align 3\n" \
        TYPE_DIRECTIVE(SYMBOLNAME) \
        ASM_SYMBOL_PREFIX #SYMBOLNAME":\n" \
        ".incbin \"ver/"ASTRINGIFY(VERSION)"/build/" FILENAME ".bin\"\n" \
        POPSECTION \
    )

// two macros are needed for N() usage
#define INCLUDE_IMG(FILENAME, SYMBOLNAME) \
    _INCLUDE_IMG(FILENAME, SYMBOLNAME)

#define INCLUDE_PAL(FILENAME, SYMBOLNAME) \
    extern unsigned short SYMBOLNAME[]; \
    __asm__( \
        ".globl " ASM_SYMBOL_PREFIX #SYMBOLNAME"\n" \
        PUSHSECTION(".data") \
        ".p2align 3\n" \
        TYPE_DIRECTIVE(SYMBOLNAME) \
        ASM_SYMBOL_PREFIX #SYMBOLNAME":\n" \
        ".incbin \"ver/"ASTRINGIFY(VERSION)"/build/" FILENAME ".bin\"\n" \
        POPSECTION \
    )

#define INCLUDE_RAW(FILENAME, SYMBOLNAME) \
    extern unsigned char SYMBOLNAME[]; \
    __asm__( \
        ".globl " ASM_SYMBOL_PREFIX #SYMBOLNAME"\n" \
        PUSHSECTION(".data") \
        ".p2align 3\n" \
        TYPE_DIRECTIVE(SYMBOLNAME) \
        ASM_SYMBOL_PREFIX #SYMBOLNAME":\n" \
        ".incbin \"ver/"ASTRINGIFY(VERSION)"/build/assets/"ASTRINGIFY(VERSION)"/" FILENAME "\"\n" \
        POPSECTION \
    )


#endif // _H_INCLUDE_ASSET
