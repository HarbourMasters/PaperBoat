# Upstream ios.toolchain.cmake with our minimum OS version applied first.
#
# It has to be set here, not in CMakeLists.txt: the toolchain bakes it into the
# compiler's -target triple before any project code runs. 16.3 is where libc++
# marks std::to_chars available, which std::format's float path calls.
if(NOT DEFINED DEPLOYMENT_TARGET)
    set(DEPLOYMENT_TARGET "16.3")
endif()

include("${CMAKE_CURRENT_LIST_DIR}/ios.toolchain.cmake")
