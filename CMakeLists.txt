# libultraship's floor, and what FetchContent's OVERRIDE_FIND_PACKAGE needs.
cmake_minimum_required(VERSION 3.24)

project(Paperboat
    VERSION 1.0.1
    LANGUAGES C CXX
    DESCRIPTION "PM64"
)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS ON)  # Enable GNU extensions (gnu99)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)

include(cmake/paperboat-cvars.cmake)
include(cmake/lus-cvars.cmake)

################################################################################
# Mobile / web platform setup
#
# Must run before anything else: the iOS toolchain rewrites the compiler, and
# the Emscripten flags have to reach libultraship and ImGui too.
################################################################################
if(IOS)
    if(NOT DEFINED PLATFORM)
        set(PLATFORM "OS64")
    endif()
    option(IOS_SIGNING "Code sign the iOS app (OFF produces an unsigned bundle for sideloading)" ON)
    include(cmake/ios.toolchain.cmake)
    # cmake/ios.paperboat.toolchain.cmake sets this before the toolchain bakes
    # it into the target triple. Anything lower dies deep in <format> instead.
    if(DEPLOYMENT_TARGET VERSION_LESS 16.3)
        message(FATAL_ERROR
            "iOS deployment target is ${DEPLOYMENT_TARGET}; Paperboat needs 16.3 or newer "
            "(std::format's floating-point path calls std::to_chars, which libc++ marks "
            "unavailable before then).\n"
            "Configure with -DCMAKE_TOOLCHAIN_FILE=cmake/ios.paperboat.toolchain.cmake, "
            "or pass -DDEPLOYMENT_TARGET=16.3 yourself.")
    endif()
    add_compile_definitions(
        PLATFORM_IOS=1
        __IOS__
    )
    if(IOS_SIGNING)
        # Empty means "whatever the signing identity says".
        set(CMAKE_XCODE_ATTRIBUTE_DEVELOPMENT_TEAM "$ENV{IOS_DEVELOPMENT_TEAM}")
    endif()
    set(BUNDLE_ID "dev.net64.paperboat")
    set(SIGN_LIBRARY ${IOS_SIGNING})
    set(PROJECT_ID "${BUNDLE_ID}")
endif()

if(EMSCRIPTEN)
    # The macro, not the CMake option: the option would also try to link a
    # libGLESv2 that Emscripten does not have.
    add_compile_definitions(USE_OPENGLES=1)
    add_compile_options(-pthread -sUSE_SDL=2 -fexceptions)
    add_link_options(-pthread -sUSE_SDL=2)
endif()

if(ANDROID)
    add_compile_definitions(USE_OPENGLES=1)
endif()

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

set(PROJECT_BUILD_NAME "Mulberry ${PROJECT_PATCH_WORD}" CACHE STRING "" FORCE)
set(PROJECT_TEAM "Caladius" CACHE STRING "" FORCE)

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
endif()

include(FetchContent)

################################################################################
# libultraship dependencies the platform files don't cover
#
# libultraship has no cmake/dependencies/emscripten.cmake, so its
# find_package(... REQUIRED) calls have nothing to find without these.
################################################################################
if(EMSCRIPTEN)
    set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

    set(tinyxml2_BUILD_TESTING OFF)
    FetchContent_Declare(
        tinyxml2
        GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
        GIT_TAG 11.0.0
        GIT_SHALLOW TRUE
        OVERRIDE_FIND_PACKAGE
    )
    FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.12.0
        GIT_SHALLOW TRUE
        OVERRIDE_FIND_PACKAGE
    )
    FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.16.0
        GIT_SHALLOW TRUE
        OVERRIDE_FIND_PACKAGE
    )

    # libzip finds zlib through find_package; a stale redirect from an earlier
    # configure would point at a port emcc has not built yet.
    file(REMOVE
        "${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/zlib-config.cmake"
        "${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/zlib-config-version.cmake"
        "${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/zlibConfig.cmake"
        "${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/zlibConfigVersion.cmake")
    set(_emsysroot "${EMSCRIPTEN_SYSROOT}")
    if(NOT _emsysroot)
        set(_emsysroot "${CMAKE_SYSROOT}")
    endif()
    if(NOT _emsysroot)
        message(FATAL_ERROR "Could not determine the Emscripten sysroot for zlib")
    endif()
    set(ZLIB_INCLUDE_DIR "${_emsysroot}/include" CACHE PATH "" FORCE)
    set(ZLIB_LIBRARY "${_emsysroot}/lib/wasm32-emscripten/libz.a" CACHE FILEPATH "" FORCE)

    set(BUILD_TOOLS OFF)
    set(BUILD_REGRESS OFF)
    set(BUILD_EXAMPLES OFF)
    set(BUILD_DOC OFF)
    set(BUILD_OSSFUZZ OFF)
    set(BUILD_SHARED_LIBS OFF)
    set(ENABLE_BZIP2 OFF)
    set(ENABLE_LZMA OFF)
    set(ENABLE_ZSTD OFF)
    set(ENABLE_COMMONCRYPTO OFF)
    set(ENABLE_GNUTLS OFF)
    set(ENABLE_MBEDTLS OFF)
    set(ENABLE_OPENSSL OFF)
    FetchContent_Declare(
        libzip
        GIT_REPOSITORY https://github.com/nih-at/libzip.git
        GIT_TAG v1.11.4
        GIT_SHALLOW TRUE
        OVERRIDE_FIND_PACKAGE
    )

    FetchContent_MakeAvailable(tinyxml2 nlohmann_json spdlog libzip)
endif()

# None of these can dlopen a native mod, and TCC has no backend for them.
if(ANDROID OR IOS OR EMSCRIPTEN)
    set(ENABLE_SCRIPTING OFF CACHE BOOL "" FORCE)
    set(DISABLE_DLL_LOADER ON CACHE BOOL "" FORCE)
endif()

# Add libultraship BEFORE setting include directories to avoid polluting its builds.
# Into the binary tree, not the submodule: Android configures once per ABI, and
# an in-source build dir has them all overwriting the same libImGui.a.
add_subdirectory(external/libultraship ${CMAKE_BINARY_DIR}/libultraship)

# Prism (fetched by libultraship) misdetects clang-cl as non-MSVC and skips /EHsc
if(MSVC AND TARGET prism)
    target_compile_options(prism PRIVATE /EHsc)
endif()

# Add torch as a library for asset extraction
set(USE_STANDALONE OFF CACHE BOOL "" FORCE)
set(ROM_CRC_BSWAP ON CACHE BOOL "" FORCE)
set(BUILD_PM64 ON CACHE BOOL "" FORCE)
set(BUILD_SM64 OFF CACHE BOOL "" FORCE)
set(BUILD_MK64 OFF CACHE BOOL "" FORCE)
set(BUILD_SF64 OFF CACHE BOOL "" FORCE)
set(BUILD_FZERO OFF CACHE BOOL "" FORCE)
set(BUILD_MARIO_ARTIST OFF CACHE BOOL "" FORCE)
set(BUILD_BK64 OFF CACHE BOOL "" FORCE)
set(BUILD_OOT OFF CACHE BOOL "" FORCE)
add_subdirectory(external/torch)

# Collect all game C sources (excluding .inc.c which are included by other files)
# Also, dx now has some cpp files.
file(GLOB_RECURSE GAME_SOURCES ${CMAKE_SOURCE_DIR}/src/*.c ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE INC_FILES ${CMAKE_SOURCE_DIR}/src/*.inc.c ${CMAKE_SOURCE_DIR}/src/*.inc.cpp)
list(REMOVE_ITEM GAME_SOURCES ${INC_FILES})

# Exclude port sources (handled separately), os/ (handled by libultraship)
list(FILTER GAME_SOURCES EXCLUDE REGEX "/src/port/")
list(FILTER GAME_SOURCES EXCLUDE REGEX "/src/os/")
list(FILTER GAME_SOURCES EXCLUDE REGEX "/src/boot/")

# nusys runs as written on top of src/port/os
file(GLOB NUSYS_SOURCES ${CMAKE_SOURCE_DIR}/src/os/nusys/*.c)
list(FILTER NUSYS_SOURCES EXCLUDE REGEX "/src/os/nusys/(nucontinit|nucontpakmgr|nupi|nugfxinit)")
list(APPEND GAME_SOURCES ${NUSYS_SOURCES})

# Exclude effects/gfx/ asset data files (replaced by OTR)
list(FILTER GAME_SOURCES EXCLUDE REGEX "/src/effects/gfx/")
list(FILTER GAME_SOURCES EXCLUDE REGEX "unused_gfx\\.c$")

# Exclude region-specific files (for building VERSION_US)
list(FILTER GAME_SOURCES EXCLUDE REGEX "/[^/]*_(jp|fr|es|de|en|en_de|pal|ique)\\.c$")

# Exclude language selection (PAL-only feature)
list(FILTER GAME_SOURCES EXCLUDE REGEX "/filemenu_selectlanguage\\.c$")

# Exclude .c files that are #included in npc.c files (not compiled separately)
list(FILTER GAME_SOURCES EXCLUDE REGEX "/(npc_composer|npc_hint_dryite_companion|npc_hint_dryite|npc_merlee|npc_moustafa|npc_shop_owner)\\.c$")

# Exclude kzn_19 animation files that are #included
list(FILTER GAME_SOURCES EXCLUDE REGEX "/kzn_19_anim[0-9]+\\.c$")

# Exclude JP-only narrator file (uses MSG_Intro_JP_* not available in US)
list(FILTER GAME_SOURCES EXCLUDE REGEX "/hos_10/narrator\\.c$")

# Exclude sam2 dlist/vtx — DL and vertices loaded from OTR (sam2_monstar.yml)
list(FILTER GAME_SOURCES EXCLUDE REGEX "/battle/area/sam2/(dlist|vtx)\\.c$")

# Exclude pra_02/entity.c old unsplit version. pra_02_3_entity.c is the correct dx split... I think?
list(FILTER GAME_SOURCES EXCLUDE REGEX "/pra_02/entity\\.c$")

#=================== SSE2NEON ===================
if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64|ARM64")
    set(SSE2NEON_DIR ${CMAKE_BINARY_DIR}/_deps/sse2neon)
    file(DOWNLOAD "https://raw.githubusercontent.com/DLTcollab/sse2neon/refs/heads/master/sse2neon.h" "${SSE2NEON_DIR}/sse2neon.h")
    include_directories(${SSE2NEON_DIR})
endif()

FetchContent_Declare(
    dr_libs
    GIT_REPOSITORY https://github.com/mackron/dr_libs.git
	GIT_TAG da35f9d6c7374a95353fd1df1d394d44ab66cf01
)
FetchContent_MakeAvailable(dr_libs)

file(GLOB_RECURSE PORT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    src/port/*.cpp
    src/port/*.c
)

list(FILTER PORT_SOURCES EXCLUDE REGEX ".*.inc.c")

if(IOS)
    set(IOS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ios)
    set(STORYBOARD_FILE ${IOS_DIR}/Launch.storyboard)
    set(IMAGE_FILES ${IOS_DIR}/PoweredBy.png)
    set(ICON_FILES ${IOS_DIR}/Icon.png)

    add_executable(${PROJECT_NAME}
        ${GAME_SOURCES}
        ${PORT_SOURCES}
        ${STORYBOARD_FILE}
        ${IMAGE_FILES}
        ${ICON_FILES}
    )

    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST ${IOS_DIR}/plist.in
        RESOURCE "${IMAGE_FILES};${STORYBOARD_FILE};${ICON_FILES}"
        XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "${BUNDLE_ID}"
    )

    if(IOS_SIGNING)
        set_target_properties(${PROJECT_NAME} PROPERTIES
            XCODE_ATTRIBUTE_CODE_SIGN_STYLE "Automatic"
            XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED "YES"
            XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED "YES"
            XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "Apple Development"
        )
    else()
        set_target_properties(${PROJECT_NAME} PROPERTIES
            XCODE_ATTRIBUTE_CODE_SIGN_STYLE "Manual"
            XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED "NO"
            XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED "NO"
            XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY ""
        )
    endif()
elseif(ANDROID)
    # SDLActivity loads "SDL2" and then "main"; the second name is this library.
    add_library(${PROJECT_NAME} SHARED
        ${GAME_SOURCES}
        ${PORT_SOURCES}
    )
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")
else()
    add_executable(${PROJECT_NAME}
        ${GAME_SOURCES}
        ${PORT_SOURCES}
    )
endif()

if(EMSCRIPTEN)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "paperboat" SUFFIX ".html")
endif()

# Organize source files into folders for Visual Studio Solution Explorer
source_group(TREE ${CMAKE_SOURCE_DIR}/src PREFIX "Game" FILES ${GAME_SOURCES})
source_group(TREE ${CMAKE_SOURCE_DIR}/src/port PREFIX "Port" FILES ${PORT_SOURCES})

# Embed the application icon (paperboat.ico) into the Windows executable
target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Resource.rc)
source_group("Resources" FILES ${CMAKE_SOURCE_DIR}/Resource.rc)

if (NOT MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<COMPILE_LANGUAGE:C>:-Wno-implicit-function-declaration>
        $<$<COMPILE_LANGUAGE:C>:-Wno-int-conversion>
        $<$<COMPILE_LANGUAGE:C>:-Wno-initializer-overrides>
        $<$<C_COMPILER_ID:GNU>:-Wreturn-mismatch>
    )
endif()

# Neither the VS nor the Xcode generator can put COMPILE_LANGUAGE in a compile
# *definition* — one definition list per config, no per-language split. Without
# the per-file fallback, iOS compiles the game's C as C++ and every
# `extern "C" {` in the headers fails with "expected identifier".
if(MSVC OR CMAKE_GENERATOR STREQUAL "Xcode")
    set(PAPERBOAT_PER_FILE_LANGUAGE_DEFS TRUE)
endif()

if(PAPERBOAT_PER_FILE_LANGUAGE_DEFS)
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
    $<$<NOT:$<BOOL:${PAPERBOAT_PER_FILE_LANGUAGE_DEFS}>>:$<$<COMPILE_LANGUAGE:C>:_LANGUAGE_C>>
    $<$<NOT:$<BOOL:${PAPERBOAT_PER_FILE_LANGUAGE_DEFS}>>:$<$<COMPILE_LANGUAGE:CXX>:_LANGUAGE_C_PLUS_PLUS>>
    PORT
    MODERN_COMPILER
    VERSION=us
    VERSION_US
    F3DEX_GBI_2
    __CTX__
    SPDLOG_ACTIVE_LEVEL=0
)

# Compute YAML asset files count for proper progress tracking
file(GLOB_RECURSE PAPERBOAT_ASSET_YAMLS CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/assets/yaml/us/*.yaml
    ${CMAKE_SOURCE_DIR}/assets/yaml/us/*.yml
)
list(FILTER PAPERBOAT_ASSET_YAMLS EXCLUDE REGEX "/(config\\.yml|hashes\\.yaml)$")
list(LENGTH PAPERBOAT_ASSET_YAMLS PAPERBOAT_ASSET_YAML_COUNT)
message(STATUS "${PAPERBOAT_ASSET_YAML_COUNT} asset YAMLs")
target_compile_definitions(${PROJECT_NAME} PRIVATE
    PAPERBOAT_ASSET_YAML_COUNT=${PAPERBOAT_ASSET_YAML_COUNT}
)

# Target-specific include directories (only applies to Paperboat, not dependencies)
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

# The engine's own archive: everything under port/ zipped up. A target rather
# than a POST_BUILD step because the web build preloads it at link time.
set(PAPERBOAT_PORT_O2R "${CMAKE_BINARY_DIR}/paperboat.o2r")
file(GLOB_RECURSE PAPERBOAT_PORT_FILES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/port/*")
add_custom_command(
    OUTPUT "${PAPERBOAT_PORT_O2R}"
    COMMENT "Generating paperboat.o2r shader archive..."
    COMMAND ${CMAKE_COMMAND} -E tar cf "${PAPERBOAT_PORT_O2R}" --format=zip -- .
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/port"
    DEPENDS ${PAPERBOAT_PORT_FILES}
    VERBATIM
)
add_custom_target(GeneratePortO2R DEPENDS "${PAPERBOAT_PORT_O2R}")
add_dependencies(${PROJECT_NAME} GeneratePortO2R)

target_link_libraries(${PROJECT_NAME} PRIVATE libultraship torch yaml-cpp)

if(ANDROID)
    # libzip comes from libultraship's android.cmake, so its headers are in the
    # build tree rather than on a system include path.
    FetchContent_GetProperties(libzip)
    if(libzip_SOURCE_DIR)
        target_include_directories(${PROJECT_NAME} PRIVATE ${libzip_SOURCE_DIR}/lib ${libzip_BINARY_DIR})
    endif()
    target_link_libraries(${PROJECT_NAME} PRIVATE libzip::zip GLESv3 EGL android log)
endif()

if(EMSCRIPTEN)
    # zip.h/zipconf.h, for the libultraship headers the game code includes.
    FetchContent_GetProperties(libzip)
    if(libzip_SOURCE_DIR)
        target_include_directories(${PROJECT_NAME} PRIVATE ${libzip_SOURCE_DIR}/lib ${libzip_BINARY_DIR})
    endif()

    target_link_options(${PROJECT_NAME} PRIVATE
        -sUSE_SDL=2
        -sUSE_WEBGL2=1
        -sMAX_WEBGL_VERSION=2
        -sMIN_WEBGL_VERSION=2
        -sFULL_ES3=1
        -sINITIAL_MEMORY=536870912
        -sALLOW_MEMORY_GROWTH=1
        -sEXIT_RUNTIME=1
        -sSTACK_SIZE=5242880
        -sPTHREAD_POOL_SIZE=8
        # The frame loop blocks; Asyncify lets it yield to the browser. Torch
        # is excluded — see src/port/web/asyncify-remove.txt.
        -sASYNCIFY=1
        "-sASYNCIFY_REMOVE=@${CMAKE_SOURCE_DIR}/src/port/web/asyncify-remove.txt"
        -sASYNCIFY_STACK_SIZE=8388608
        -sASSERTIONS=1
        -sFORCE_FILESYSTEM=1
        -sEXPORTED_FUNCTIONS=_main,_malloc,_free
        -sEXPORTED_RUNTIME_METHODS=FS,ccall,cwrap,UTF8ToString,stringToUTF8
        -lembind
        # Saves and the generated pm64.o2r live in IndexedDB under /storage.
        -lidbfs.js
        "SHELL:--shell-file ${CMAKE_SOURCE_DIR}/src/port/web/shell.html"
        "SHELL:--preload-file ${CMAKE_SOURCE_DIR}/assets@/assets"
        "SHELL:--preload-file ${CMAKE_SOURCE_DIR}/config.yml@/config.yml"
        "SHELL:--preload-file ${PAPERBOAT_PORT_O2R}@/paperboat.o2r"
    )

    # Development shortcut; players generate the archive from their own ROM.
    set(PAPERBOAT_WEB_PRELOAD_ROM "" CACHE FILEPATH "Path to a pm64.o2r to embed (debug only)")
    if(PAPERBOAT_WEB_PRELOAD_ROM)
        target_link_options(${PROJECT_NAME} PRIVATE
            "SHELL:--preload-file ${PAPERBOAT_WEB_PRELOAD_ROM}@/storage/pm64.o2r")
    endif()

    set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY LINK_DEPENDS
        "${CMAKE_SOURCE_DIR}/src/port/web/shell.html"
        "${CMAKE_SOURCE_DIR}/src/port/web/asyncify-remove.txt"
        "${PAPERBOAT_PORT_O2R}")

    # SharedArrayBuffer needs COOP/COEP headers a static host won't send.
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_SOURCE_DIR}/src/port/web/coi-serviceworker.js"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/coi-serviceworker.js"
    )
endif()

# Torch reads config.yml and the asset yamls off disk to extract a ROM. Android
# unpacks its own out of the APK and the web build preloads them at link time;
# iOS needs them inside the .app, where GetAppBundlePath() points.
if(IOS)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMENT "Bundling config.yml and asset yamls..."
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/config.yml" "$<TARGET_BUNDLE_CONTENT_DIR:${PROJECT_NAME}>/config.yml"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/assets/" "$<TARGET_BUNDLE_CONTENT_DIR:${PROJECT_NAME}>/assets/"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PAPERBOAT_PORT_O2R}" "$<TARGET_BUNDLE_CONTENT_DIR:${PROJECT_NAME}>/paperboat.o2r"
    )
elseif(NOT ANDROID AND NOT EMSCRIPTEN)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMENT "Copying config.yml, asset yamls and paperboat.o2r..."
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/config.yml" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/config.yml"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/assets/" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets/"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PAPERBOAT_PORT_O2R}" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/paperboat.o2r"
    )
endif()

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

    # Set working directory for visual studio debugger
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

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

    # Compile options (clang-cl vs MSVC)
    if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
        # Clang-CL: no /ZI (Edit & Continue)
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:/w;/Od;/MTd;/Zi>
            $<$<CONFIG:Release>:/Oi;/Gy;/W3;/MT;/Zi>
            /permissive-
            /clang:-Wno-implicit-function-declaration
            /clang:-Wno-int-conversion
            /clang:-Wno-narrowing
            /clang:-fcommon
            /MP
        )
    else()
        # MSVC (cl.exe)
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:/w;/Od;/MTd;/ZI>
            $<$<CONFIG:Release>:/Oi;/Gy;/W3;/MT;/Zi>
            /permissive-
            /MP
        )
    endif()

    # MSVC link options
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:/INCREMENTAL;/FORCE:MULTIPLE>
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

elseif(ANDROID OR EMSCRIPTEN)
    # GL comes from the platform; neither has a desktop OpenGL to find.
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
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-c++11-narrowing>
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-enum-conversion>
        -pthread
    )
    target_link_options(${PROJECT_NAME} PRIVATE -pthread)

elseif(UNIX)
    # Linux-specific settings
    find_package(OpenGL REQUIRED)

    # CPU-specific optimizations
    if(NOT DEFINED CPU_OPTION)
        if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
            set(CPU_OPTION -msse2 -mfpmath=sse)
        elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
            set(CPU_OPTION -mcpu=native)
        endif()
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

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    if(POLICY CMP0177)
        cmake_policy(SET CMP0177 NEW)
    endif()

    install(FILES "${PAPERBOAT_PORT_O2R}" DESTINATION . COMPONENT ${PROJECT_NAME})
    install(FILES "${CMAKE_SOURCE_DIR}/config.yml" DESTINATION . COMPONENT ${PROJECT_NAME})
    install(DIRECTORY "${CMAKE_SOURCE_DIR}/assets/" DESTINATION ./assets COMPONENT ${PROJECT_NAME})

    set_property(TARGET ${PROJECT_NAME} PROPERTY APPIMAGE_DESKTOP_FILE_TERMINAL NO)
    set_property(TARGET ${PROJECT_NAME} PROPERTY APPIMAGE_DESKTOP_FILE "${CMAKE_SOURCE_DIR}/Paperboat.desktop")
    set_property(TARGET ${PROJECT_NAME} PROPERTY APPIMAGE_ICON_FILE "${CMAKE_SOURCE_DIR}/logo.png")

    set(CPACK_GENERATOR "External")
    set(CPACK_PROJECT_CONFIG_FILE ${CMAKE_SOURCE_DIR}/cmake/configure-packaging.cmake)
    include(cmake/packaging.cmake)
endif()

if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    add_custom_target(CreateOSXIcons
        COMMAND mkdir -p ${CMAKE_BINARY_DIR}/macosx/paperboat.iconset
        COMMAND sips -z 16 16     logo.png --out ${CMAKE_BINARY_DIR}/macosx/paperboat.iconset/icon_16x16.png
        COMMAND sips -z 32 32     logo.png --out ${CMAKE_BINARY_DIR}/macosx/paperboat.iconset/icon_16x16@2x.png
        COMMAND sips -z 32 32     logo.png --out ${CMAKE_BINARY_DIR}/macosx/paperboat.iconset/icon_32x32.png
        COMMAND sips -z 64 64     logo.png --out ${CMAKE_BINARY_DIR}/macosx/paperboat.iconset/icon_32x32@2x.png
        COMMAND sips -z 128 128   logo.png --out ${CMAKE_BINARY_DIR}/macosx/paperboat.iconset/icon_128x128.png
        COMMAND sips -z 256 256   logo.png --out ${CMAKE_BINARY_DIR}/macosx/paperboat.iconset/icon_128x128@2x.png
        COMMAND sips -z 256 256   logo.png --out ${CMAKE_BINARY_DIR}/macosx/paperboat.iconset/icon_256x256.png
        COMMAND sips -z 512 512   logo.png --out ${CMAKE_BINARY_DIR}/macosx/paperboat.iconset/icon_256x256@2x.png
        COMMAND sips -z 512 512   logo.png --out ${CMAKE_BINARY_DIR}/macosx/paperboat.iconset/icon_512x512.png
        COMMAND cp                logo.png ${CMAKE_BINARY_DIR}/macosx/paperboat.iconset/icon_512x512@2x.png
        COMMAND iconutil -c icns -o ${CMAKE_BINARY_DIR}/macosx/paperboat.icns ${CMAKE_BINARY_DIR}/macosx/paperboat.iconset
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Creating OSX icons ..."
    )
    add_dependencies(${PROJECT_NAME} CreateOSXIcons)
    configure_file("${CMAKE_SOURCE_DIR}/Info.plist" "${CMAKE_BINARY_DIR}/Info.plist" @ONLY)

    file(DOWNLOAD
        https://raw.githubusercontent.com/mdqinc/SDL_GameControllerDB/master/gamecontrollerdb.txt
        ${CMAKE_BINARY_DIR}/gamecontrollerdb.txt)

    install(TARGETS ${PROJECT_NAME} DESTINATION ../MacOS COMPONENT ${PROJECT_NAME})
    install(FILES ${CMAKE_BINARY_DIR}/gamecontrollerdb.txt DESTINATION ../Resources COMPONENT ${PROJECT_NAME})
    install(FILES ${PAPERBOAT_PORT_O2R} DESTINATION ../Resources COMPONENT ${PROJECT_NAME})
    install(FILES ${CMAKE_SOURCE_DIR}/config.yml DESTINATION ../Resources COMPONENT ${PROJECT_NAME})
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets/ DESTINATION ../Resources/assets COMPONENT ${PROJECT_NAME})

    install(CODE "
        include(BundleUtilities)
        fixup_bundle(\"\${CMAKE_INSTALL_PREFIX}/../MacOS/Paperboat\" \"\" \"\")
    ")

    set(CPACK_GENERATOR "Bundle")
    set(CPACK_PROJECT_CONFIG_FILE ${CMAKE_SOURCE_DIR}/cmake/configure-packaging.cmake)
    include(cmake/packaging.cmake)
endif()

message(STATUS "Configuring ${PROJECT_NAME} v${PROJECT_VERSION}")
