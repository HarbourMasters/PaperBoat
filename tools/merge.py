import os
import re
import sys
import argparse
import hashlib
import struct
from enum import Enum
from io import BytesIO
from typing import Optional, Dict

try:
    from PIL import Image
except ImportError:
    Image = None

class TextureType(Enum):
    Error = 0
    RGBA32bpp = 1
    RGBA16bpp = 2
    Palette4bpp = 3
    Palette8bpp = 4
    Grayscale4bpp = 5
    Grayscale8bpp = 6
    GrayscaleAlpha4bpp = 7
    GrayscaleAlpha8bpp = 8
    GrayscaleAlpha16bpp = 9


TexturePixelMultipliers: Dict[TextureType, float] = {
    TextureType.Error: 0.0,
    TextureType.RGBA32bpp: 4.0,
    TextureType.RGBA16bpp: 2.0,
    TextureType.Palette4bpp: 0.5,
    TextureType.Palette8bpp: 1.0,
    TextureType.Grayscale4bpp: 0.5,
    TextureType.Grayscale8bpp: 1.0,
    TextureType.GrayscaleAlpha4bpp: 0.5,
    TextureType.GrayscaleAlpha8bpp: 1.0,
    TextureType.GrayscaleAlpha16bpp: 2.0,
}

class TextureTypeUtils:
    @staticmethod
    def num_to_texture_type(num: int) -> TextureType:
        mapping = {
            1: TextureType.RGBA32bpp,
            2: TextureType.RGBA16bpp,
            3: TextureType.Palette4bpp,
            4: TextureType.Palette8bpp,
            5: TextureType.Grayscale4bpp,
            6: TextureType.Grayscale8bpp,
            7: TextureType.GrayscaleAlpha4bpp,
            8: TextureType.GrayscaleAlpha8bpp,
            9: TextureType.GrayscaleAlpha16bpp,
        }
        if num not in mapping:
            raise ValueError(f"Unknown texture type number: {num}")
        return mapping[num]

    @staticmethod
    def str_to_texture_type(string: str) -> TextureType:
        mapping = {
            'RGBA32': TextureType.RGBA32bpp,
            'RGBA16': TextureType.RGBA16bpp,
            'TLUT': TextureType.RGBA16bpp,
            'CI4': TextureType.Palette4bpp,
            'CI8': TextureType.Palette8bpp,
            'I4': TextureType.Grayscale4bpp,
            'I8': TextureType.Grayscale8bpp,
            'IA4': TextureType.GrayscaleAlpha4bpp,
            'IA8': TextureType.GrayscaleAlpha8bpp,
            'IA16': TextureType.GrayscaleAlpha16bpp,
        }
        if string not in mapping:
            raise ValueError(f"Unknown texture type string: {string}")
        return mapping[string]

    @staticmethod
    def get_buffer_size(tex_type: TextureType, width: int, height: int) -> int:
        pixels = width * height
        if tex_type == TextureType.RGBA32bpp:
            return pixels * 4
        elif tex_type in (TextureType.RGBA16bpp, TextureType.GrayscaleAlpha16bpp):
            return pixels * 2
        elif tex_type in (TextureType.Palette8bpp, TextureType.Grayscale8bpp, TextureType.GrayscaleAlpha8bpp):
            return pixels
        elif tex_type in (TextureType.Palette4bpp, TextureType.Grayscale4bpp, TextureType.GrayscaleAlpha4bpp):
            return (pixels + 1) // 2
        return 0


class Texture:
    def __init__(self, width: int, height: int, texture_type: TextureType, tex_data: bytearray = None, tlut: Optional['Texture'] = None):
        self.width = width
        self.height = height
        self.texture_type = texture_type
        self.tex_data_size = TextureTypeUtils.get_buffer_size(texture_type, width, height)
        self.tex_data = tex_data if tex_data is not None else bytearray(self.tex_data_size)
        self.tlut = tlut

    def to_png_bytes(self) -> bytes:
        return N64Graphics.convert_n64_to_png(self)


# --- Main Implementation ---

class N64Graphics:

    @staticmethod
    def has_alpha(texture: Texture) -> bool:
        t = texture.texture_type
        return t in (
            TextureType.Palette4bpp,
            TextureType.Palette8bpp,
            TextureType.RGBA32bpp,
            TextureType.RGBA16bpp,
            TextureType.GrayscaleAlpha16bpp,
            TextureType.GrayscaleAlpha8bpp,
            TextureType.GrayscaleAlpha4bpp,
        )

    @staticmethod
    def pixels_to_png(texture: Texture, data: bytes) -> bytes:
        img = Image.frombytes("RGBA", (texture.width, texture.height), data)
        out_buffer = BytesIO()
        img.save(out_buffer, format="PNG")
        return out_buffer.getvalue()

    @staticmethod
    def convert_raw_to_n64(texture: Texture, img: Image.Image) -> None:
        texture.width = img.width
        texture.height = img.height
        texture.tex_data_size = TextureTypeUtils.get_buffer_size(texture.texture_type, texture.width, texture.height)
        texture.tex_data = bytearray(texture.tex_data_size)

        w, h = texture.width, texture.height
        tex_data = texture.tex_data
        tex_type = texture.texture_type

        if tex_type == TextureType.RGBA16bpp:
            img_rgba = img.convert("RGBA")
            pixels = img_rgba.load()
            for y in range(h):
                for x in range(w):
                    r, g, b, a = pixels[x, y]
                    pos = ((y * w) + x) * 2
                    r5 = r // 8
                    g5 = g // 8
                    b5 = b // 8
                    a_bit = 1 if a != 0 else 0

                    data_val = (r5 << 11) | (g5 << 6) | (b5 << 1) | a_bit
                    tex_data[pos] = (data_val & 0xFF00) >> 8
                    tex_data[pos + 1] = data_val & 0x00FF

        elif tex_type == TextureType.RGBA32bpp:
            img_rgba = img.convert("RGBA")
            pixels = img_rgba.load()
            for y in range(h):
                for x in range(w):
                    r, g, b, a = pixels[x, y]
                    pos = ((y * w) + x) * 4
                    tex_data[pos:pos+4] = [r, g, b, a]

        elif tex_type == TextureType.Palette4bpp:
            img_p = img.convert("P") if img.mode != "P" else img
            pixels = img_p.load()
            for y in range(h):
                for x in range(0, w, 2):
                    pos = ((y * w) + x) // 2
                    idx1 = pixels[x, y]
                    idx2 = pixels[x + 1, y] if x + 1 < w else 0
                    tex_data[pos] = ((idx1 & 0x0F) << 4) | (idx2 & 0x0F)

        elif tex_type == TextureType.Palette8bpp:
            img_p = img.convert("P") if img.mode != "P" else img
            pixels = img_p.load()
            for y in range(h):
                for x in range(w):
                    pos = (y * w) + x
                    tex_data[pos] = pixels[x, y] & 0xFF

        elif tex_type == TextureType.Grayscale4bpp:
            img_l = img.convert("L") if img.mode != "L" else img
            pixels = img_l.load()
            for y in range(h):
                for x in range(0, w, 2):
                    pos = ((y * w) + x) // 2
                    r1 = pixels[x, y]
                    r2 = pixels[x + 1, y] if x + 1 < w else 0
                    tex_data[pos] = (((r1 // 16) << 4) | (r2 // 16)) & 0xFF

        elif tex_type == TextureType.Grayscale8bpp:
            img_l = img.convert("L") if img.mode != "L" else img
            pixels = img_l.load()
            for y in range(h):
                for x in range(w):
                    pos = (y * w) + x
                    tex_data[pos] = pixels[x, y] & 0xFF

        elif tex_type == TextureType.GrayscaleAlpha4bpp:
            img_la = img.convert("LA") if img.mode != "LA" else img
            pixels = img_la.load()
            for y in range(h):
                for x in range(0, w, 2):
                    pos = ((y * w) + x) // 2
                    l1, a1 = pixels[x, y]
                    l2, a2 = pixels[x + 1, y] if x + 1 < w else (0, 0)
                    
                    alpha_bit1 = 1 if a1 != 0 else 0
                    alpha_bit2 = 1 if a2 != 0 else 0

                    data_val = ((((l1 // 32) << 1) | alpha_bit1) << 4) | (((l2 // 32) << 1) | alpha_bit2)
                    tex_data[pos] = data_val & 0xFF

        elif tex_type == TextureType.GrayscaleAlpha8bpp:
            img_la = img.convert("LA") if img.mode != "LA" else img
            pixels = img_la.load()
            for y in range(h):
                for x in range(w):
                    pos = (y * w) + x
                    l, a = pixels[x, y]
                    tex_data[pos] = (((l // 16) << 4) | (a // 16)) & 0xFF

        elif tex_type == TextureType.GrayscaleAlpha16bpp:
            img_la = img.convert("LA") if img.mode != "LA" else img
            pixels = img_la.load()
            for y in range(h):
                for x in range(w):
                    pos = ((y * w) + x) * 2
                    l, a = pixels[x, y]
                    tex_data[pos] = l & 0xFF
                    tex_data[pos + 1] = a & 0xFF

        elif tex_type == TextureType.Error:
            raise ValueError("Unknown texture type")

    @staticmethod
    def convert_n64_to_png(texture: Texture) -> Optional[bytes]:
        w, h = texture.width, texture.height
        tex_data = texture.tex_data
        tex_type = texture.texture_type
        is_palette = tex_type in (TextureType.Palette4bpp, TextureType.Palette8bpp)

        img: Optional[Image.Image] = None

        if tex_type == TextureType.RGBA32bpp:
            img = Image.frombytes("RGBA", (w, h), bytes(tex_data))

        elif tex_type == TextureType.RGBA16bpp:
            img = Image.new("RGBA", (w, h))
            pixels = img.load()
            for y in range(h):
                for x in range(w):
                    pos = ((y * w) + x) * 2
                    data_val = (tex_data[pos] << 8) | tex_data[pos + 1]
                    r = ((data_val & 0xF800) >> 11) * 8
                    g = ((data_val & 0x07C0) >> 6) * 8
                    b = ((data_val & 0x003E) >> 1) * 8
                    a = (data_val & 0x01) * 255
                    pixels[x, y] = (r, g, b, a)

        elif tex_type == TextureType.Palette4bpp:
            img = Image.new("P", (w, h))
            pixels = img.load()
            palette = [0] * (256 * 4) 
            for y in range(h):
                for x in range(0, w, 2):
                    pos = ((y * w) + x) // 2
                    idx1 = (tex_data[pos] & 0xF0) >> 4
                    idx2 = tex_data[pos] & 0x0F
                    
                    pixels[x, y] = idx1
                    if x + 1 < w:
                        pixels[x + 1, y] = idx2

                    palette[idx1*4 : idx1*4+4] = [idx1*16, idx1*16, idx1*16, 255]
                    palette[idx2*4 : idx2*4+4] = [idx2*16, idx2*16, idx2*16, 255]

        elif tex_type == TextureType.Palette8bpp:
            img = Image.new("P", (w, h))
            pixels = img.load()
            palette = [0] * (256 * 4)
            for y in range(h):
                for x in range(w):
                    pos = (y * w) + x
                    idx = tex_data[pos]
                    pixels[x, y] = idx
                    palette[idx*4 : idx*4+4] = [idx, idx, idx, 255]

        elif tex_type == TextureType.Grayscale4bpp:
            img = Image.new("L", (w, h))
            pixels = img.load()
            for y in range(h):
                for x in range(0, w, 2):
                    pos = ((y * w) + x) // 2
                    g1 = tex_data[pos] & 0xF0
                    g2 = (tex_data[pos] & 0x0F) << 4
                    
                    pixels[x, y] = g1
                    if x + 1 < w:
                        pixels[x + 1, y] = g2

        elif tex_type == TextureType.Grayscale8bpp:
            img = Image.new("L", (w, h))
            pixels = img.load()
            for y in range(h):
                for x in range(w):
                    pos = (y * w) + x
                    pixels[x, y] = tex_data[pos]

        elif tex_type == TextureType.GrayscaleAlpha4bpp:
            img = Image.new("LA", (w, h))
            pixels = img.load()
            for y in range(h):
                for x in range(0, w, 2):
                    pos = ((y * w) + x) // 2
                    val = tex_data[pos]

                    d1 = (val & 0xF0) >> 4
                    g1 = ((d1 & 0x0E) >> 1) * 32
                    a1 = (d1 & 0x01) * 255
                    pixels[x, y] = (g1, a1)

                    if x + 1 < w:
                        d2 = val & 0x0F
                        g2 = ((d2 & 0x0E) >> 1) * 32
                        a2 = (d2 & 0x01) * 255
                        pixels[x + 1, y] = (g2, a2)

        elif tex_type == TextureType.GrayscaleAlpha8bpp:
            img = Image.new("LA", (w, h))
            pixels = img.load()
            for y in range(h):
                for x in range(w):
                    pos = (y * w) + x
                    val = tex_data[pos]
                    g = val & 0xF0
                    a = (val & 0x0F) << 4
                    pixels[x, y] = (g, a)

        elif tex_type == TextureType.GrayscaleAlpha16bpp:
            img = Image.new("LA", (w, h))
            pixels = img.load()
            for y in range(h):
                for x in range(w):
                    pos = ((y * w) + x) * 2
                    g = tex_data[pos]
                    a = tex_data[pos + 1]
                    pixels[x, y] = (g, a)
        else:
            return None

        if is_palette:
            if texture.tlut:
                pal_bytes = texture.tlut.to_png_bytes()
                pal_img = Image.open(BytesIO(pal_bytes)).convert("RGBA")
                pal_pixels = pal_img.load()
                
                for y in range(pal_img.height):
                    for x in range(pal_img.width):
                        index = y * pal_img.width + x
                        if index >= 256:
                            continue
                        r, g, b, a = pal_pixels[x, y]
                        palette[index*4 : index*4+4] = [r, g, b, a]
            
            img.putpalette(bytearray(palette), rawmode='RGBA')

        out_buffer = BytesIO()
        img.save(out_buffer, format="PNG")
        return out_buffer.getvalue()

def convert_png_to_n64_texture(png_bytes: bytes, texture_type: TextureType) -> Texture:
    img = Image.open(BytesIO(png_bytes))
    texture = Texture(0, 0, texture_type)
    N64Graphics.convert_raw_to_n64(texture, img)
    return texture

def write_header(resource_type: int, version: int) -> bytes:
    endianness = 0x00
    game_version = 0
    rom_crc = 0
    rom_enum = 0
    magic = 0xDEADBEEFDEADBEEF

    # Struct format characters (assuming Little-Endian '<'):
    # I = unsigned int (4 bytes)
    # Q = unsigned long long (8 bytes)
    #
    # Order: Endianness(I), Type(I), Version(I), Magic(Q), GameVer(I), CRC(Q), Enum(I)
    header_data = struct.pack(
        '<IIIQIQI',
        endianness,     # [0x00] 4 bytes
        resource_type,  # [0x04] 4 bytes
        version,        # [0x08] 4 bytes
        magic,          # [0x0C] 8 bytes
        game_version,   # [0x14] 4 bytes
        rom_crc,        # [0x18] 8 bytes
        rom_enum        # [0x20] 4 bytes
    )

    # Pad with null bytes until we reach 0x40 (64 bytes)
    padding_needed = 0x40 - len(header_data)
    if padding_needed > 0:
        header_data += b'\x00' * padding_needed

    return header_data

ASSET_FORMATS = ('RGBA32', 'RGBA16', 'CI4', 'CI8', 'I4', 'I8', 'IA4', 'IA8', 'IA16', 'CI4_PAL', 'CI8_PAL')

_palette_cache = {}

def to_rgba5551(r: int, g: int, b: int, a: int) -> int:
    if a < 128:
        return 0
    return ((r >> 3) << 11) | ((g >> 3) << 6) | ((b >> 3) << 1) | 1

def image_pixels(img) -> list:
    flattened = getattr(img, "get_flattened_data", None)
    return list(flattened() if flattened is not None else img.getdata())

def png_palette_indices(img, colors: int):
    if img.mode != "P":
        return None
    indices = image_pixels(img)
    if max(indices, default=0) >= colors:
        return None
    rgb = img.getpalette() or []
    alpha = [255] * colors
    transparency = img.info.get("transparency")
    if isinstance(transparency, bytes):
        for i, a in enumerate(transparency[:colors]):
            alpha[i] = a
    elif isinstance(transparency, int) and transparency < colors:
        alpha[transparency] = 0
    palette = []
    for i in range(colors):
        r, g, b = rgb[i * 3:i * 3 + 3] if len(rgb) >= i * 3 + 3 else (0, 0, 0)
        palette.append(to_rgba5551(r, g, b, alpha[i]))
    return indices, palette

def quantize_indices(img, colors: int):
    values = [to_rgba5551(*p) for p in image_pixels(img.convert("RGBA"))]
    has_clear = 0 in values
    offset = 1 if has_clear else 0
    opaque = sorted(set(v for v in values if v != 0))
    palette = [0] if has_clear else []

    if len(opaque) <= colors - offset:
        lookup = {v: i + offset for i, v in enumerate(opaque)}
        palette += opaque
        indices = [lookup[v] if v != 0 else 0 for v in values]
    else:
        def expand(v):
            return (((v >> 11) & 31) << 3, ((v >> 6) & 31) << 3, ((v >> 1) & 31) << 3)

        strip_pixels = [expand(v) for v in values if v != 0]
        strip = Image.new("RGB", (len(strip_pixels), 1))
        strip.putdata(strip_pixels)
        method = getattr(Image, "Quantize", Image).MEDIANCUT
        dither = getattr(Image, "Dither", Image).NONE
        quantized = strip.quantize(colors=colors - offset, method=method, dither=dither)
        rgb = quantized.getpalette()
        palette += [to_rgba5551(rgb[i * 3], rgb[i * 3 + 1], rgb[i * 3 + 2], 255) for i in range(colors - offset)]
        strip_indices = iter(image_pixels(quantized))
        indices = [next(strip_indices) + offset if v != 0 else 0 for v in values]

    palette += [0] * (colors - len(palette))
    return indices, palette[:colors]

def palette_texture(img, colors: int, key: str):
    cache_key = (key, colors)
    if cache_key not in _palette_cache:
        _palette_cache[cache_key] = png_palette_indices(img, colors) or quantize_indices(img, colors)
    return _palette_cache[cache_key]

def write_otex(texture_type: TextureType, width: int, height: int, data: bytes) -> bytes:
    otr_header = write_header(resource_type=0x4F544558, version=0)
    return otr_header + struct.pack('<IIII', texture_type.value, width, height, len(data)) + bytes(data)

def convert_png_asset(bytes_data: bytes, key: str, fmt: str) -> bytes:
    img = Image.open(BytesIO(bytes_data))
    img.load()
    width, height = img.size

    if fmt in ('CI4', 'CI8', 'CI4_PAL', 'CI8_PAL'):
        colors = 16 if fmt.startswith('CI4') else 256
        indices, palette = palette_texture(img, colors, key)
        if fmt.endswith('_PAL'):
            data = bytearray()
            for color in palette:
                data += bytes(((color >> 8) & 0xFF, color & 0xFF))
            return write_otex(TextureType.RGBA16bpp, colors, 1, data)
        if colors == 256:
            return write_otex(TextureType.Palette8bpp, width, height, bytes(indices))
        data = bytearray()
        for y in range(height):
            row = indices[y * width:(y + 1) * width]
            if width % 2:
                row = row + [0]
            for x in range(0, len(row), 2):
                data.append(((row[x] & 0x0F) << 4) | (row[x + 1] & 0x0F))
        return write_otex(TextureType.Palette4bpp, width, height, data)

    texture = Texture(0, 0, TextureTypeUtils.str_to_texture_type(fmt))
    N64Graphics.convert_raw_to_n64(texture, img)
    return write_otex(texture.texture_type, texture.width, texture.height, texture.tex_data)

def preprocess_asset(bytes_data: bytes, filename: str, fmt: Optional[str] = None) -> bytes:
    file = filename.lower()

    if file.lower().endswith('.bin'):
        return bytes_data

    elif file.endswith('.png'):
        if Image is None:
            raise RuntimeError("Pillow is required for .png assets (pip install Pillow)")
        if fmt is not None and fmt != 'RGBA32':
            return convert_png_asset(bytes_data, filename, fmt)
        img = Image.open(BytesIO(bytes_data))
        width, height = img.size
        texture_type = TextureType.RGBA32bpp.value
        raw = bytes_data
        resource_type = 0x52544558  # RTEX

        tex_data_size = len(raw)

        otr_header = write_header(resource_type=resource_type, version=0x1)
        tex_header = struct.pack(
            '<IIIIffI',
            texture_type,   # type
            width,          # width
            height,         # height
            1 << 1,         # flags: TEX_FLAG_LOAD_AS_IMG
            1.0,            # h_byte_scale
            1.0,            # v_pixel_scale
            tex_data_size   # image_data_size
        )

        return otr_header + tex_header + raw
    else:
        raise ValueError(f"Unsupported asset file type for {filename}")

def preprocess_embed(bytes_data: bytes, filename: str) -> bytes:
    # If you want bytes to be embedded directly into the C file, you can preprocess them here.
    return bytes_data


# Macros known while merging: the game's defines, given with --defines, and those the merged headers define. A mod is
# merged on one machine and compiled by TinyCC on another, so the platform's own macros stay unknown, and both sides of
# a check on them keep their headers for TinyCC to choose from.
DEFINES = {}
UNKNOWN = {'_WIN32', '_WIN64', '__CYGWIN__', '__APPLE__', '__MACH__', '__linux__', '__ANDROID__', '__unix__',
           '__FreeBSD__', '__EMSCRIPTEN__', '__IOS__', 'TARGET_OS_IPHONE', 'TARGET_OS_MAC', '__aarch64__',
           '__x86_64__', '__i386__', '__arm__', '_M_X64', '_M_ARM64', '_M_IX86', '_MSC_VER', '__clang__', '__GNUC__',
           '__ANDROID_API__'}
in_progress = set()


def strip_comments(text):
    text = re.sub(r'/\*.*?\*/', ' ', text)
    return text.split('//')[0]


def eval_condition(expr):
    """True or False for an #if expression, None when it depends on an unknown macro or can't be read."""
    try:
        def defined(match):
            name = match.group(1) or match.group(2)
            if name in UNKNOWN:
                raise LookupError(name)
            return ' 1 ' if name in DEFINES else ' 0 '

        text = re.sub(r'defined\s*(?:\(\s*([A-Za-z_]\w*)\s*\)|([A-Za-z_]\w*))', defined, strip_comments(expr))
        for _ in range(16):
            changed = False

            def macro(match):
                nonlocal changed
                name = match.group(0)
                if name in UNKNOWN:
                    raise LookupError(name)
                value = DEFINES.get(name)
                if name in DEFINES:
                    if value is None:
                        raise LookupError(name)  # a function-like macro
                    changed = True
                    return ' (' + (value or '1') + ') '
                return ' 0 '

            text = re.sub(r'(?<![\w.])[A-Za-z_]\w*', macro, text)
            if not changed:
                break
        if '?' in text:
            return None
        text = re.sub(r'(\d+)[uUlL]+\b', r'\1', text)
        text = text.replace('&&', ' and ').replace('||', ' or ')
        text = re.sub(r'!(?!=)', ' not ', text).replace('/', '//')
        return bool(eval(text, {'__builtins__': {}}, {}))
    except Exception:
        return None


def open_branch(parent, result):
    if parent == 'off':
        return {'state': 'off', 'taken': True, 'maybe': False, 'parent': parent}
    frame = {'state': 'off', 'taken': False, 'maybe': False, 'parent': parent}
    next_branch(frame, result, first=True)
    return frame


def next_branch(frame, result, first=False):
    """Moves to the next branch of an #if; result is True for #else."""
    if frame['parent'] == 'off' or frame['taken']:
        frame['state'] = 'off'
    elif result is None:
        frame['state'] = 'maybe'
        frame['maybe'] = True
    elif result:
        frame['state'] = 'maybe' if (frame['maybe'] or frame['parent'] == 'maybe') else 'on'
        frame['taken'] = not frame['maybe']
    else:
        frame['state'] = 'off'


def find_file(name, delimiter, source, include_dirs):
    search_paths = list(include_dirs)
    if delimiter == '"':
        search_paths.insert(0, os.path.dirname(source))
    for path in search_paths:
        candidate = os.path.join(path, name)
        if os.path.exists(candidate):
            return candidate
    return None

def amalgamate(file_path, include_dirs, processed, out_file, assets_dir, base_state='on', is_header=False):
    abs_path = os.path.abspath(file_path)

    in_progress.add(abs_path)
    if is_header:
        # Headers can be inlined more than once, e.g. under both sides of a platform check, so each gets its own guard
        # in place of #pragma once, which means nothing inside one merged file.
        guard = "MERGE_GUARD_" + hashlib.md5(abs_path.encode('utf-8')).hexdigest()[:16]
        out_file.write(f"#ifndef {guard}\n#define {guard}\n")

    try:
        with open(abs_path, 'r', encoding='utf-8') as f:
            content = f.read()

        # Step 1: Find and process `#asset` blocks ONLY
        # Replaces `u8 array[] = { #asset ... };` with an aligned asset path and extracts .bin
        asset_block_pattern = re.compile(
            r'(?:(?:static|const|ALIGNED8|extern)\s+)*u8\s+([a-zA-Z0-9_]+)\s*\[\]\s*=\s*\{\s*#asset\s+([<"])([^>"]+)[>"]\s*([A-Za-z0-9_]+)?\s*\};',
            re.MULTILINE
        )

        def repl_asset_block(match):
            var_name = match.group(1)
            delimiter = match.group(2)
            target_name = match.group(3)
            fmt = match.group(4).upper() if match.group(4) else None

            if fmt is not None and fmt not in ASSET_FORMATS:
                print(f"Warning: Unknown asset format {fmt} for {target_name}, expected one of {', '.join(ASSET_FORMATS)}")
                return f"/* ERROR: Unknown asset format {fmt} for {target_name} */"

            target_path = None
            search_paths = list(include_dirs)
            if delimiter == '"':
                search_paths.insert(0, os.path.dirname(abs_path))

            for path in search_paths:
                potential_path = os.path.join(path, target_name)
                if os.path.exists(potential_path):
                    target_path = potential_path
                    break

            if target_path:
                try:
                    with open(target_path, 'rb') as bin_file:
                        raw_bytes = bin_file.read()

                    resource_name = target_name
                    if resource_name.lower().endswith('.png'):
                        resource_name = resource_name[:-4]
                        if fmt is not None and fmt != 'RGBA32':
                            resource_name += '.' + fmt.lower()

                    # Write the .bin companion file mirroring directory tree
                    if assets_dir:
                        companion_path = os.path.join(assets_dir, resource_name)
                        os.makedirs(os.path.dirname(companion_path), exist_ok=True)
                        with open(companion_path, 'wb') as cf:
                            cf.write(preprocess_asset(raw_bytes, target_path, fmt))

                    # Return formatted string literal block for C
                    return f'static const char {var_name}[] __attribute__((aligned(2))) = "__OTR__{resource_name}";'

                except Exception as e:
                    print(f"Warning: Failed to read asset file {target_path}: {e}")
                    return f"/* ERROR: Failed to process {target_name} */"
            else:
                print(f"Warning: Could not find asset file {target_name} requested from {abs_path}")
                return f"/* ERROR: Could not find {target_name} */"

        # Apply the #asset replacement over the whole text file
        content = asset_block_pattern.sub(repl_asset_block, content)

        # Step 2: Process the remaining lines one by one for standard #embeds and #includes. Conditionals are evaluated
        # as the mod will be compiled, so only the headers it uses are inlined.
        stack = []

        def state():
            return stack[-1]['state'] if stack else base_state

        for line in content.splitlines(keepends=True):
            stripped = line.strip()

            if is_header and re.match(r'#\s*pragma\s+once\b', stripped):
                continue

            directive = re.match(r'#\s*(ifdef|ifndef|if|elif|else|endif|define|undef)\b(.*)', stripped)
            if directive:
                kind, rest = directive.group(1), strip_comments(directive.group(2)).strip()
                parent = state()
                if kind in ('ifdef', 'ifndef', 'if'):
                    if kind == 'if':
                        result = eval_condition(rest)
                    else:
                        name = rest.split()[0] if rest else ''
                        result = None if name in UNKNOWN else ((name in DEFINES) == (kind == 'ifdef'))
                    stack.append(open_branch(parent, result))
                elif kind == 'elif' and stack:
                    next_branch(stack[-1], eval_condition(rest))
                elif kind == 'else' and stack:
                    next_branch(stack[-1], True)
                elif kind == 'endif' and stack:
                    stack.pop()
                elif kind in ('define', 'undef') and parent != 'off':
                    m = re.match(r'([A-Za-z_][A-Za-z0-9_]*)(\()?\s*(.*)', rest)
                    if m:
                        name = m.group(1)
                        if parent == 'maybe':
                            UNKNOWN.add(name)
                        elif kind == 'undef':
                            DEFINES.pop(name, None)
                        else:
                            DEFINES[name] = None if m.group(2) else m.group(3)
                out_file.write(line)
                continue

            if state() == 'off':
                out_file.write(line)
                continue

            # Look for legacy #embed (leaves the surrounding u8 array intact, just injects hex)
            embed = re.match(r'^\s*#\s*embed\s+([<"])([^>"]+)[>"]', line)
            if embed:
                delimiter = embed.group(1)
                target_name = embed.group(2)
                target_path = find_file(target_name, delimiter, abs_path, include_dirs)

                if target_path:
                    out_file.write(f"/* --- Start Embedded Bytes: {target_name} --- */\n")
                    try:
                        with open(target_path, 'rb') as bin_file:
                            raw_bytes = preprocess_embed(bin_file.read(), target_name)
                        hex_array = [f"0x{b:02x}" for b in raw_bytes]
                        for i in range(0, len(hex_array), 16):
                            out_file.write("    " + ", ".join(hex_array[i:i+16]) + ",\n")
                    except Exception as e:
                        print(f"Warning: Failed to read embedded file {target_path}: {e}")
                        out_file.write(f"/* ERROR: Failed to read {target_name} */\n")
                    out_file.write(f"/* --- End Embedded Bytes: {target_name} --- */\n")
                else:
                    out_file.write(f"/* ERROR: Could not find {target_name} */\n")
                continue

            # Standard #include amalgamation
            include = re.match(r'^\s*#\s*include\s+([<"])([^>"]+)[>"]', line)
            if include:
                header_name = include.group(2)
                header_path = find_file(header_name, include.group(1), abs_path, include_dirs)
                if header_path is None:
                    # A system header, which TinyCC has.
                    out_file.write(line)
                    continue
                header_abs = os.path.abspath(header_path)
                if header_abs in processed or header_abs in in_progress:
                    continue
                if state() == 'on':
                    processed.add(header_abs)
                out_file.write(f"/* --- Start: {header_name} --- */\n")
                amalgamate(header_path, include_dirs, processed, out_file, assets_dir, state(), True)
                out_file.write(f"/* --- End: {header_name} --- */\n")
            else:
                out_file.write(line)
        if is_header:
            # On its own line: a header may end without a newline, or in a // comment.
            out_file.write("\n#endif\n")
    except Exception as e:
        print(f"Warning: Could not process {abs_path}: {e}")
    finally:
        in_progress.discard(abs_path)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate a Unity Build amalgamation.")
    parser.add_argument('--out', required=True, help="The single output .c file")
    parser.add_argument('--assets-dir', default=None, help="Root output directory for companion .bin files")
    parser.add_argument('--includes', nargs='*', default=[], help="Include directories")
    parser.add_argument('--srcs', nargs='+', required=True, help="Input .c files")
    parser.add_argument('--defines', nargs='*', default=[], help="NAME or NAME=VALUE the mod is compiled with")

    args = parser.parse_args()
    for define in args.defines:
        name, _, value = define.partition('=')
        DEFINES[name] = value or '1'

    global_processed = set()

    with open(args.out, 'w', encoding='utf-8') as out_file:
        for src_file in args.srcs:
            out_file.write(f"\n/* ========================================= */\n")
            out_file.write(f"/* === Start of Source: {os.path.basename(src_file)} === */\n")
            out_file.write(f"/* ========================================= */\n\n")

            amalgamate(src_file, args.includes, global_processed, out_file, args.assets_dir)