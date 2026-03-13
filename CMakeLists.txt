cmake_minimum_required(VERSION 3.16)

project(StarRod
    VERSION 0.1.0
    LANGUAGES C CXX
    DESCRIPTION "PM64"
)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS ON)  # Enable GNU extensions (gnu99)
set(CMAKE_CXX_STANDARD 20)

include(cmake/paperboat-cvars.cmake)
include(cmake/lus-cvars.cmake)

set(NATO_PHONETIC_ALPHABET
  "Alfa" "Bravo" "Charlie" "Delta" "Echo" "Foxtrot" "Golf" "Hotel"
  "India" "Juliett" "Kilo" "Lima" "Mike" "November" "Oscar" "Papa"
  "Quebec" "Romeo" "Sierra" "Tango" "Uniform" "Victor" "Whiskey"
  "Xray" "Yankee" "Zulu"
)

# Get the patch version number from the project version
math(EXPR PATCH_INDEX "${PROJECT_VERSION_PATCH}")

# Use the patch number to select the correct word
list(GET NATO_PHONETIC_ALPHABET ${PATCH_INDEX} PROJECT_PATCH_WORD)

set(PROJECT_BUILD_NAME "Dutchman ${PROJECT_PATCH_WORD}" CACHE STRING "" FORCE)
set(PROJECT_TEAM "Lywx" CACHE STRING "" FORCE)

# Get Git Information
execute_process(
    COMMAND git branch --show-current
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(CMAKE_PROJECT_GIT_BRANCH "${GIT_BRANCH}" CACHE STRING "Git branch" FORCE)

execute_process(
    COMMAND git rev-parse HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get only the first 7 characters of the hash
string(SUBSTRING "${GIT_COMMIT_HASH}" 0 7 SHORT_COMMIT_HASH)

set(CMAKE_PROJECT_GIT_COMMIT_HASH "${SHORT_COMMIT_HASH}" CACHE STRING "Git commit hash" FORCE)

execute_process(
    COMMAND git describe --tags --abbrev=0 --exact-match HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_TAG
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(NOT GIT_COMMIT_TAG)
    set(GIT_COMMIT_TAG "" CACHE STRING "Git commit tag" FORCE)
endif()

set(CMAKE_PROJECT_GIT_COMMIT_TAG "${GIT_COMMIT_TAG}" CACHE STRING "Git commit tag" FORCE)

################################################################################
# Sources
################################################################################
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/src/port/build.c.in ${CMAKE_CURRENT_SOURCE_DIR}/src/port/build.c @ONLY)

################################################################################
# Use solution folders feature
################################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

################################################################################
# Windows vcpkg bootstrap (must happen BEFORE add_subdirectory)
################################################################################
if (WIN32)
    include(cmake/automate-vcpkg.cmake)
    set(VCPKG_TRIPLET x64-windows-static)
    set(VCPKG_TARGET_TRIPLET x64-windows-static)
    vcpkg_bootstrap()
    vcpkg_install_packages(zlib bzip2 sdl2 glew libzip nlohmann-json tinyxml2 spdlog)

    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endif()

# Add libultraship BEFORE setting include directories to avoid polluting its builds
add_subdirectory(external/libultraship ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship)

# Add torch as a library for asset extraction
set(USE_STANDALONE OFF CACHE BOOL "" FORCE)
set(BUILD_PM64 ON CACHE BOOL "" FORCE)
set(BUILD_SM64 OFF CACHE BOOL "" FORCE)
set(BUILD_MK64 OFF CACHE BOOL "" FORCE)
set(BUILD_SF64 OFF CACHE BOOL "" FORCE)
set(BUILD_FZERO OFF CACHE BOOL "" FORCE)
set(BUILD_MARIO_ARTIST OFF CACHE BOOL "" FORCE)
add_subdirectory(external/torch)

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

#=================== SSE2NEON ===================
if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64|ARM64")
    set(SSE2NEON_DIR ${CMAKE_BINARY_DIR}/_deps/sse2neon)
    file(DOWNLOAD "https://raw.githubusercontent.com/DLTcollab/sse2neon/refs/heads/master/sse2neon.h" "${SSE2NEON_DIR}/sse2neon.h")
    include_directories(${SSE2NEON_DIR})
endif()

include(FetchContent)
FetchContent_Declare(
    dr_libs
    GIT_REPOSITORY https://github.com/mackron/dr_libs.git
	GIT_TAG da35f9d6c7374a95353fd1df1d394d44ab66cf01
)
FetchContent_MakeAvailable(dr_libs)

file(GLOB_RECURSE PORT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    src/port/*.cpp
    src/port/audio/*.c
    src/port/audio/*.cpp
    src/port/importer/*.cpp
    src/port/sprite/*.cpp
    src/port/*.c
)

list(FILTER PORT_SOURCES EXCLUDE REGEX ".*.inc.c")

add_executable(${PROJECT_NAME}
    ${GAME_SOURCES}
    ${PORT_SOURCES}
)

# Organize source files into folders for Visual Studio Solution Explorer
source_group(TREE ${CMAKE_SOURCE_DIR}/src/game PREFIX "Game" FILES ${GAME_SOURCES})
source_group(TREE ${CMAKE_SOURCE_DIR}/src/port PREFIX "Port" FILES ${PORT_SOURCES})

if (NOT MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<COMPILE_LANGUAGE:C>:-Wno-implicit-function-declaration>
        $<$<COMPILE_LANGUAGE:C>:-Wno-int-conversion>
        $<$<COMPILE_LANGUAGE:C>:-Wno-initializer-overrides>
        $<$<C_COMPILER_ID:GNU>:-Wreturn-mismatch>
    )
endif()

# VS generator can't handle COMPILE_LANGUAGE generator expressions,
# so set _LANGUAGE_C / _LANGUAGE_C_PLUS_PLUS per-file based on extension
if(MSVC)
    foreach(src ${GAME_SOURCES} ${PORT_SOURCES})
        if(src MATCHES "\\.c$")
            set_source_files_properties(${src} PROPERTIES COMPILE_DEFINITIONS "_LANGUAGE_C")
        else()
            set_source_files_properties(${src} PROPERTIES COMPILE_DEFINITIONS "_LANGUAGE_C_PLUS_PLUS")
        endif()
    endforeach()
endif()

# __CTX__ disables INCLUDE_ASM macros and inline assembly
target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:$<$<COMPILE_LANGUAGE:C>:_LANGUAGE_C>>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:$<$<COMPILE_LANGUAGE:CXX>:_LANGUAGE_C_PLUS_PLUS>>
    PORT
    MODERN_COMPILER
    VERSION=us
    VERSION_US
    F3DEX_GBI_2
    GBI_FLOATS
    __CTX__
    SPDLOG_ACTIVE_LEVEL=0
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
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/external/torch/src
    ${CMAKE_CURRENT_SOURCE_DIR}/external/torch/lib
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

target_link_libraries(${PROJECT_NAME} PRIVATE libultraship torch)

# Copy config.yml and assets to output directory for torch asset extraction
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMENT "Copying config.yml and asset yamls..."
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/config.yml" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/config.yml"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/assets/" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets/"
)

# Generate paperboat.o2r shader archive from libultraship shaders
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMENT "Generating paperboat.o2r shader archive..."
    COMMAND ${CMAKE_COMMAND} -E tar cf "$<TARGET_FILE_DIR:${PROJECT_NAME}>/paperboat.o2r" --format=zip -- .
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/port"
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

################################################################################
# Platform-specific configuration
################################################################################
if(MSVC)
    # MSVC runtime library (static CRT)
    get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
    string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        $<$<CONFIG:Debug>:MultiThreadedDebug>
        $<$<CONFIG:Release>:MultiThreaded>
        $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Release>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
    )
    set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

    # Windows compile definitions
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:_DEBUG;_CRT_SECURE_NO_WARNINGS;ENABLE_DX11>"
        "$<$<CONFIG:Release>:NDEBUG>"
        UNICODE
        _UNICODE
        _CRT_SECURE_NO_WARNINGS
        _SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS
    )
    add_compile_definitions(STORMLIB_NO_AUTO_LINK)
    set(STORMLIB_NO_AUTO_LINK ON)

    # MSVC compile options
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:/w;/Od;/MTd;/ZI>
        $<$<CONFIG:Release>:/Oi;/Gy;/W3;/MT;/Zi>
        /permissive-
        /MP
    )

    # MSVC link options
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:/INCREMENTAL>
        $<$<CONFIG:Release>:/OPT:REF;/OPT:ICF;/INCREMENTAL:NO;/FORCE:MULTIPLE>
        /MANIFEST:NO
        /DEBUG
        /SUBSYSTEM:WINDOWS
    )

    # Remove /RTC from MSVC flags
    foreach(fentry CMAKE_C_FLAGS CMAKE_CXX_FLAGS)
        string(REGEX REPLACE "/RTC(su|[1su])" "" ${fentry} "${${fentry}}")
    endforeach()

elseif(APPLE)
    # macOS-specific settings
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall -Wextra -Wno-error
        -Wno-unused-parameter
        -Wno-unused-function
        -Wno-unused-variable
        -Wno-missing-field-initializers
        -Wno-parentheses
        -Wno-narrowing
        -Wno-missing-braces
        $<$<COMPILE_LANGUAGE:CXX>:-fpermissive>
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-c++11-narrowing>
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-enum-conversion>
        -pthread
    )
    target_link_options(${PROJECT_NAME} PRIVATE -pthread)

elseif(UNIX)
    # Linux-specific settings
    find_package(OpenGL REQUIRED)

    # CPU-specific optimizations
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
        set(CPU_OPTION -msse2 -mfpmath=sse)
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
        set(CPU_OPTION -mcpu=native)
    endif()

    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall -Wextra -Wno-error
        -Wno-unused-parameter
        -Wno-unused-function
        -Wno-unused-variable
        -Wno-missing-field-initializers
        -Wno-parentheses
        -Wno-narrowing
        -Wno-missing-braces
        $<$<COMPILE_LANGUAGE:C>:-Wno-incompatible-pointer-types>
        $<$<COMPILE_LANGUAGE:CXX>:-fpermissive>
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-enum-conversion>
        -pthread
        ${CPU_OPTION}
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        -pthread
        -Wl,-export-dynamic
        -Wl,--allow-multiple-definition
    )
endif()

message(STATUS "Configuring ${PROJECT_NAME} v${PROJECT_VERSION}")
