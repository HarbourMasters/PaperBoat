@echo off
setlocal

echo ============================================================
echo  StarRod - Visual Studio Solution Generator
echo ============================================================
echo.

REM Check for CMake
where cmake >nul 2>&1
if %ERRORLEVEL% neq 0 (
    echo ERROR: CMake not found in PATH.
    echo Install CMake from https://cmake.org/download/
    pause
    exit /b 1
)

REM Ensure submodules are initialized
echo Checking git submodules...
git submodule update --init --recursive
if %ERRORLEVEL% neq 0 (
    echo WARNING: Failed to update submodules. Continuing anyway...
)
echo.

REM Create build directory
if not exist build-msvc mkdir build-msvc

echo Configuring with Visual Studio 17 2022 (x64)...
echo.

cmake -S . -B build-msvc -G "Visual Studio 17 2022" -A x64 ^
    -DVCPKG_TARGET_TRIPLET=x64-windows-static

if %ERRORLEVEL% neq 0 (
    echo.
    echo ERROR: CMake configuration failed.
    pause
    exit /b 1
)

echo.
echo ============================================================
echo  Solution generated: build-msvc\StarRod.sln
echo  Open it with Visual Studio 2022.
echo  StarRod is set as the startup project.
echo ============================================================
echo.

REM Optionally open the solution
set /p OPEN_SOL="Open solution now? [Y/n] "
if /i "%OPEN_SOL%" neq "n" (
    start "" "build-msvc\StarRod.sln"
)

pause
