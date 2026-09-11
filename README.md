# Paper Mario DX

[![Release](https://img.shields.io/github/v/release/bates64/papermario-dx)][releases]
[![Download](https://img.shields.io/github/downloads/bates64/papermario-dx/total)][download]
![Build Status](https://img.shields.io/github/actions/workflow/status/bates64/papermario-dx/build.yaml)

This is a fork of the [Paper Mario decompilation][papermario-repo] which provides a flexible, easy-to-use base for creating romhacks.

To get started, [read the docs](https://docs.starhaven.dev).

Paperboat is the native port built on top of it. Alongside Windows, macOS and
Linux it builds for **Android, iOS and the browser** — see
[docs/android-ios-web.md](docs/android-ios-web.md). No game
data ships with any of them: each one extracts `pm64.o2r` from your own ROM,
on your own device.

[discord]: https://discord.gg/star-haven
[discord-badge]: https://img.shields.io/discord/279322074412089344?color=%237289DA&logo=discord&logoColor=ffffff
[papermario-repo]: https://github.com/pmret/papermario
[releases]: https://github.com/bates64/papermario-dx/releases
[download]: https://github.com/bates64/papermario-dx/releases/download/latest/papermario.bps

### List of changes (incomplete)

- US release only (no JP, PAL, or iQue - none of these are near 100% yet).
- Default configure flags: `--shift --modern-gcc --non-matching --ccache`
- Backtrace (call stack) on crash screen including file names and line numbers.
    - You can call [`debug_backtrace()`](src/dx/backtrace.h) to print a backtrace in any function.
    - Failed assertions (`ASSERT`) will trigger the crash screen and print a backtrace instead of hanging.
    - Backtraces provide filenames and line numbers for files with debug symbols (pass `--debug` to configure to enable for all files).
- `assets/star_rod_build` directory for Star Rod to write assets to.
- Fixed many bugs / incorrect behaviour.
- Skip compiling or linking dead code.
- Link with [libgcc_vr4300] to provide compiler intrinsics.
- Added a debug/cheats menu.
- Enemy HP is now a `s16`, increasing the cap to 32767.
- Added support for badges with negative BP costs.
- Additional features can be configured in [src/dx/config.h](src/dx/config.h).

[libgcc_vr4300]: https://github.com/Decompollaborate/libgcc_vr4300

