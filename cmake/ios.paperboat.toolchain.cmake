# Paperboat's iOS toolchain: upstream ios.toolchain.cmake with our minimum OS
# version applied before it runs.
#
# The deployment target has to be settled here rather than in CMakeLists.txt.
# ios.toolchain.cmake bakes it into the compiler's -target triple and caches it
# as an INTERNAL variable, and both of those happen before any of the project's
# own code executes — so setting it later has no effect on how anything compiles.
#
# 16.3 is where libc++ marks std::to_chars available. std::format's
# floating-point path calls it, so an older target fails to compile the engine.
if(NOT DEFINED DEPLOYMENT_TARGET)
    set(DEPLOYMENT_TARGET "16.3")
endif()

include("${CMAKE_CURRENT_LIST_DIR}/ios.toolchain.cmake")
