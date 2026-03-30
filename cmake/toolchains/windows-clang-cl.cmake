if(NOT WIN32)
    message(FATAL_ERROR "windows-clang-cl.cmake is intended for Windows only")
endif()

if(DEFINED CMAKE_C_COMPILER AND DEFINED CMAKE_CXX_COMPILER)
    return()
endif()

set(_vswhere_candidates
    "C:/Program Files (x86)/Microsoft Visual Studio/Installer/vswhere.exe"
    "C:/Program Files/Microsoft Visual Studio/Installer/vswhere.exe"
)

set(_vswhere "")
foreach(_candidate IN LISTS _vswhere_candidates)
    if(EXISTS "${_candidate}")
        set(_vswhere "${_candidate}")
        break()
    endif()
endforeach()

if(_vswhere STREQUAL "")
    message(FATAL_ERROR "Could not find vswhere.exe in a standard Visual Studio installer location")
endif()

execute_process(
    COMMAND "${_vswhere}" -latest -products * -property installationPath
    OUTPUT_VARIABLE _vs_installation_path
    OUTPUT_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE _vswhere_result
)

if(NOT _vswhere_result EQUAL 0 OR _vs_installation_path STREQUAL "")
    message(FATAL_ERROR "vswhere could not locate a Visual Studio installation")
endif()

set(_clang_candidates
    "${_vs_installation_path}/VC/Tools/Llvm/x64/bin/clang-cl.exe"
    "${_vs_installation_path}/VC/Tools/Llvm/bin/clang-cl.exe"
)

set(_clang_cl "")
foreach(_candidate IN LISTS _clang_candidates)
    if(EXISTS "${_candidate}")
        set(_clang_cl "${_candidate}")
        break()
    endif()
endforeach()

if(_clang_cl STREQUAL "")
    message(FATAL_ERROR "Could not locate clang-cl.exe under '${_vs_installation_path}/VC/Tools/Llvm'")
endif()

set(CMAKE_C_COMPILER "${_clang_cl}" CACHE FILEPATH "Resolved clang-cl C compiler" FORCE)
set(CMAKE_CXX_COMPILER "${_clang_cl}" CACHE FILEPATH "Resolved clang-cl CXX compiler" FORCE)
