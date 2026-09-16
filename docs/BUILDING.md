# Paperboat

### Prerequisites

#### Windows

Install **Visual Studio 2022** (Community edition or higher) with these
workloads/components:

- `Desktop development with C++`
- `C++ Clang tools for Windows` (provides `clang-cl`)
- `CMake tools for Windows`

The Ninja build system is bundled with the CMake tools component.

> **Note:** If you are building from a standalone PowerShell (outside of VS Code
> or Visual Studio), you need to run from a **Developer PowerShell for VS 2022**
> so that `clang-cl`, `ninja`, and the Windows SDK are on your PATH.
> Open one from the Start Menu, or run this in any PowerShell first:
> ```powershell
> & "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\Launch-VsDevShell.ps1" -Arch amd64 -HostArch amd64
> ```
> (adjust the path for your VS edition if needed, e.g. `Enterprise` or `Professional`)

#### macOS / Linux

Install `cmake`, `ninja`, and a C/C++ compiler (clang or gcc) via your
package manager.

### Building

Clone with submodules:

```
git clone --recurse-submodules <repo-url>
cd PaperBoat
```

If you already cloned without `--recurse-submodules`:

```
git submodule update --init
```

#### Windows (from a Developer PowerShell)

```
cmake --preset windows-debug
cmake --build --preset windows-debug -j
```

#### macOS / Linux

```
cmake --preset ninja-debug
cmake --build --preset ninja-debug -j
```

### Windows compiler support

Windows builds use `clang-cl` via the CMake presets and the repo-local
toolchain file in [cmake/toolchains/windows-clang-cl.cmake](cmake/toolchains/windows-clang-cl.cmake).

The plain MSVC C compiler (`cl.exe`) is **not** supported for the C99 decomp
sources. The project relies on C99-era constructs that would require large
direct edits to decomp files, so the supported Windows path is
`Ninja + clang-cl`.

# Configuration

### Default keyboard configuration
| N64 | A | B | Z | Start | Analog stick | C buttons | D-Pad |
| - | - | - | - | - | - | - | - |
| Keyboard | X | C | Z | Space | WASD | Arrow keys | TFGH |

### Other shortcuts
| Keys | Action |
| - | - |
| Esc | Toggle menu |
| Ctrl+R | Reset (inside levels) |
| F11 | Fullscreen |
| Tab | Toggle Alternate assets |
