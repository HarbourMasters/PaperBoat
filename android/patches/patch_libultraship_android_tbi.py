#!/usr/bin/env python3
"""Patch libultraship Fast3D for Android arm64 tagged heap pointers."""

from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TARGET = ROOT / "external" / "libultraship" / "src" / "fast" / "interpreter.cpp"
text = TARGET.read_text(encoding="utf-8")

if "CanonicalizeAndroidPointer" in text:
    print("libultraship Android pointer-tag patch already applied")
    raise SystemExit(0)


def replace_exact(old: str, new: str, expected: int = 1, label: str = "replacement") -> None:
    global text
    count = text.count(old)
    if count != expected:
        raise RuntimeError(f"{label}: expected {expected} match(es), found {count}")
    text = text.replace(old, new)


# Keep the helpers near the top of the Fast namespace so every RDP/RSP/S2DEX
# handler below can use them.
needle = """namespace Fast {

static UcodeHandlers ucode_handler_index = ucode_f3dex2;
"""
helper = """namespace Fast {

// Android arm64 may store an allocation tag in the top byte of a heap pointer.
// AArch64 dereferences it through Top Byte Ignore, but numeric range checks and
// pointer-keyed resource lookups need the canonical address.
static inline uintptr_t CanonicalizeAndroidPointer(uintptr_t addr) {
#if defined(__ANDROID__) && UINTPTR_MAX > 0xFFFFFFFFu
    return addr & 0x00FFFFFFFFFFFFFFull;
#else
    return addr;
#endif
}

static inline const char* CanonicalizeAndroidString(const char* ptr) {
    return reinterpret_cast<const char*>(CanonicalizeAndroidPointer(reinterpret_cast<uintptr_t>(ptr)));
}

static UcodeHandlers ucode_handler_index = ucode_f3dex2;
"""
replace_exact(needle, helper, label="insert canonical pointer helpers")

# Standard RDP texture image path.
replace_exact(
    "uintptr_t i = (uintptr_t)gfx->SegAddr(cmd->words.w1);",
    "uintptr_t i = CanonicalizeAndroidPointer((uintptr_t)gfx->SegAddr(cmd->words.w1));",
    label="canonicalize G_SETTIMG address",
)

# OTR filepath opcodes are range-checked before their handlers run. Without
# canonicalization Android tagged pointers are rejected before resource loading.
replace_exact(
    "uintptr_t w1 = (uintptr_t)cmd->words.w1;",
    "uintptr_t w1 = CanonicalizeAndroidPointer((uintptr_t)cmd->words.w1);",
    label="canonicalize OTR filepath guard",
)

# Do the special const-from-mutable spelling first. Otherwise the generic
# `char* fileName` substring also matches this line.
replace_exact(
    "const char* fileName = (char*)cmd->words.w1;",
    "const char* fileName = CanonicalizeAndroidString((const char*)cmd->words.w1);",
    label="canonicalize texture filepath handler",
)
replace_exact(
    "const char* fileName = (const char*)cmd->words.w1;",
    "const char* fileName = CanonicalizeAndroidString((const char*)cmd->words.w1);",
    expected=2,
    label="canonicalize const filepath handlers",
)
replace_exact(
    "char* fileName = (char*)cmd->words.w1;",
    "char* fileName = const_cast<char*>(CanonicalizeAndroidString((const char*)cmd->words.w1));",
    expected=2,
    label="canonicalize mutable filepath handlers",
)
replace_exact(
    "gfx_push_current_dir((char*)(*cmd0)->words.w1);",
    "gfx_push_current_dir(const_cast<char*>(CanonicalizeAndroidString((const char*)(*cmd0)->words.w1)));",
    label="canonicalize pushcd filepath",
)
replace_exact(
    "const char* path = (const char*)gfx->SegAddr(cmd->words.w1);",
    "const char* path = CanonicalizeAndroidString((const char*)gfx->SegAddr(cmd->words.w1));",
    label="canonicalize shader filepath",
)

# S2DEX backgrounds can carry resource-backed image pointers too.
replace_exact(
    "uintptr_t data = (uintptr_t)bg->b.imagePtr;",
    "uintptr_t data = CanonicalizeAndroidPointer((uintptr_t)bg->b.imagePtr);",
    expected=2,
    label="canonicalize S2DEX image pointers",
)

# Upstream already masks the pointer for one numeric comparison. Canonicalize it
# once instead, then use the same address for both validation and signature read.
replace_exact(
    """int32_t gfx_check_image_signature(const char* imgData) {
    uintptr_t i = (uintptr_t)(imgData);
""",
    """int32_t gfx_check_image_signature(const char* imgData) {
    uintptr_t i = CanonicalizeAndroidPointer((uintptr_t)(imgData));
    const char* canonicalImgData = reinterpret_cast<const char*>(i);
""",
    label="canonicalize signature pointer",
)
replace_exact(
    "if ((i & 0x00FFFFFFFFFFFFFFull) > 0x0000FFFFFFFFFFFFull) {",
    "if (i > 0x0000FFFFFFFFFFFFull) {",
    label="use canonical range check",
)
replace_exact(
    "return Ship::Context::GetRawInstance()->GetResourceManager()->OtrSignatureCheck(imgData);",
    "return Ship::Context::GetRawInstance()->GetResourceManager()->OtrSignatureCheck(canonicalImgData);",
    label="signature dereference canonical pointer",
)

TARGET.write_text(text, encoding="utf-8")
print(f"Patched {TARGET.relative_to(ROOT)} for Android arm64 tagged pointers")
