@echo off
setlocal enabledelayedexpansion

:: 1. Load global environment variables from the common file
call "%~dp0env.cmd"

:: Create bin and build directories in the root folder if they do not exist
if not exist "%bin_path%" mkdir "%bin_path%"
if not exist "%build_path%" mkdir "%build_path%"

:: Default build type configuration
set "build_type=Release"

:parse_args
if "%~1"=="" goto end_parse_args
if "%~1"=="-h" goto show_help
if "%~1"=="--help" goto show_help

if /i "%~1"=="debug" (
    set "build_type=Debug"
    shift
    goto parse_args
)
if /i "%~1"=="release" (
    set "build_type=Release"
    shift
    goto parse_args
)

echo Error: Invalid option '%~1'
echo Use -h or --help to see available options.
exit /b 1

:end_parse_args

:: Move into the build directory to isolate CMake cache files
cd /d "%build_path%"

echo =======================================================
echo Global generation and compilation [Mode: %build_type%]
echo =======================================================

:: CMake generation: Point to "examples" folder containing CMakeLists.txt
cmake "%examples_source_path%" -DCMAKE_BUILD_TYPE=%build_type%

:: Compilation step: Build all project targets
cmake --build . --config %build_type%

:: Clean up unwanted debug symbols and temporary files from bin
echo.
echo Cleaning unwanted temp files from bin...
if exist "%bin_path%\*.ilk" del /f /q "%bin_path%\*.ilk"
if exist "%bin_path%\*.exp" del /f /q "%bin_path%\*.exp"
if exist "%bin_path%\*.lib" del /f /q "%bin_path%\*.lib"

cd /d "%root_path%"
echo Build process completed successfully!
exit /b 0

:show_help
echo Usage: .\%~nx0 [debug|release]
echo Example: .\%~nx0 debug
exit /b 0
