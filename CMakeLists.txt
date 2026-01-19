cmake_minimum_required(VERSION 3.16)

project(StarRod
    VERSION 0.1.0
    LANGUAGES C CXX
    DESCRIPTION "PM64"
)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS ON)  # Enable GNU extensions (gnu99)
set(CMAKE_CXX_STANDARD 20)

# Add libultraship BEFORE setting include directories to avoid polluting its builds
add_subdirectory(external/libultraship ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship)

# Collect all game C sources (excluding .inc.c which are included by other files)
file(GLOB_RECURSE GAME_SOURCES ${CMAKE_SOURCE_DIR}/src/game/*.c)
file(GLOB_RECURSE INC_FILES ${CMAKE_SOURCE_DIR}/src/game/*.inc.c)
list(REMOVE_ITEM GAME_SOURCES ${INC_FILES})

# Exclude region-specific files (for building VERSION_US)
list(FILTER GAME_SOURCES EXCLUDE REGEX "/[^/]*_(jp|fr|es|de|en|en_de|pal|ique)\\.c$")

# Exclude language selection (PAL-only feature)
list(FILTER GAME_SOURCES EXCLUDE REGEX "/filemenu_selectlanguage\\.c$")

# Exclude .c files that are #included in npc.c files (not compiled separately)
list(FILTER GAME_SOURCES EXCLUDE REGEX "/(npc_composer|npc_hint_dryite_companion|npc_hint_dryite|npc_merlee|npc_moustafa|npc_shop_owner)\\.c$")

# Exclude kzn_19 animation files that are #included
list(FILTER GAME_SOURCES EXCLUDE REGEX "/kzn_19_anim[0-9]+\\.c$")

set(PORT_SOURCES
    src/port/Game.cpp
    src/port/Engine.cpp
    src/port/nusys_overrides.c
    src/port/gu.c
    src/port/ld_addr.c
    src/port/undefined_symbols.c
    src/port/libc_compat.c
    src/port/decode_yay0.c
    src/port/effects_shim.c
)

add_executable(${PROJECT_NAME}
    ${GAME_SOURCES}
    ${PORT_SOURCES}
)

target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<COMPILE_LANGUAGE:C>:-Wno-implicit-function-declaration>
    $<$<COMPILE_LANGUAGE:C>:-Wno-int-conversion>
    $<$<COMPILE_LANGUAGE:C>:-Wno-initializer-overrides>
    "-Wa,-I${CMAKE_SOURCE_DIR}"  # tells assembler to search project root for .incbin files
    "-Wreturn-mismatch"
)

# __CTX__ disables INCLUDE_ASM macros and inline assembly
target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<COMPILE_LANGUAGE:C>:_LANGUAGE_C>
    $<$<COMPILE_LANGUAGE:CXX>:_LANGUAGE_C_PLUS_PLUS>
    PORT
    MODERN_COMPILER
    VERSION=us
    VERSION_US
    F3DEX_GBI_2
    __CTX__
)

# Target-specific include directories (only applies to StarRod, not dependencies)
# Note: We exclude include/gcc and include/stdlib
# Note: We use libultraship's headers for most things, but keep some of include/PR
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/ignored/assets/us # TODO
    ${CMAKE_SOURCE_DIR}/ignored/include # TODO
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/libultra
    ${CMAKE_SOURCE_DIR}/include/PR
    ${CMAKE_SOURCE_DIR}/include/assets
    ${CMAKE_SOURCE_DIR}/src/port
    ${CMAKE_SOURCE_DIR}/src/game
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/include/libultraship
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/src
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/src/log
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/src/debug
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/src/menu
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/src/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/src/utils/binarytools
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/src/config
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/src/resource
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/src/resource/type
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/src/resource/factory
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/src/audio
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/src/window
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/src/window/gui
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/src/public
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/src/public/libultra
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/src/public/bridge
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/extern
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/extern/tinyxml2
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/src/graphic/Fast3D/U64/PR
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/src/graphic
)

add_dependencies(${PROJECT_NAME} libultraship)

target_link_libraries(${PROJECT_NAME} PRIVATE libultraship)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

# Platform-specific configuration
if(WIN32)
    # Windows-specific settings
elseif(APPLE)
    # macOS-specific settings
elseif(UNIX)
    # Linux-specific settings
endif()

message(STATUS "Configuring ${PROJECT_NAME} v${PROJECT_VERSION}")
