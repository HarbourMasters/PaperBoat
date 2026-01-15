cmake_minimum_required(VERSION 3.16)

project(StarRod
    VERSION 0.1.0
    LANGUAGES C CXX
    DESCRIPTION "PM64"
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

# Build options

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/libultra
    ${CMAKE_SOURCE_DIR}/include/libc
    ${CMAKE_SOURCE_DIR}/include/PR
    ${CMAKE_SOURCE_DIR}/include/assets
    ${CMAKE_SOURCE_DIR}/src/port/*.h
)

# Source directories - add your sources here
# set(ENGINE_SOURCES
#     src/engine/...
# )

# set(AUDIO_SOURCES
#     src/audio/...
# )

# set(SYS_SOURCES
#     src/sys/...
# )

# set(OVERLAY_SOURCES
#     src/overlays/...
# )

add_subdirectory(external/libultraship ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship)

include_directories(
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
  ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/src/config
  ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/src/public
  ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/src/public/libultra
  ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/src/public/bridge
  ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/extern
  ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/extern/tinyxml2
  ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/libultraship/Lib/
  ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/libultraship/Lib/libjpeg/include/
  ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/libultraship/Lib/spdlog/include/
  ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/src/graphic/Fast3D/U64/PR
  ${CMAKE_CURRENT_SOURCE_DIR}/external/libultraship/src/graphic
  ${SDL2_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIRS}
  ${dr_libs_SOURCE_DIR}
)
#set(LIBULTRA_SOURCES
#    src/libultra/...
#)

set(PORT_SOURCES
    src/port/Game.cpp
    src/port/Engine.cpp
)

add_executable(${PROJECT_NAME}
#    ${ENGINE_SOURCES}
#    ${AUDIO_SOURCES}
#    ${SYS_SOURCES}
#    ${OVERLAY_SOURCES}
    ${LIBULTRA_SOURCES}
    ${PORT_SOURCES}
)

add_dependencies(${PROJECT_NAME} libultraship)

target_link_libraries(${PROJECT_NAME} PRIVATE libultraship)

# Custom CMake modules
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
