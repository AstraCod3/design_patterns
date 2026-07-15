@echo off
setlocal enabledelayedexpansion

echo.
echo Starting Build ...
echo.

:: Include the common environment file for paths
call "%~dp0env.cmd"

:: Set default actions and build type
set "build_type=Release"
set "build_examples=on"

:: If no arguments provided, default to building the project
:parse_args
if "%~1"=="" goto end_parse_args

if "%~1"=="-h" goto show_help
if "%~1"=="--help" goto show_help
if "%~1"=="debug" (
    set "build_type=Debug"
    shift
    goto parse_args
)
if "%~1"=="release" (
    set "build_type=Release"
    shift
    goto parse_args
)
if "%~1"=="examples" (
    set "build_examples=on"
    shift
    goto parse_args
)

:: If argument is invalid, show error
echo Error: Invalid option '%~1'
echo Use -h or --help to see available options.
exit /b 1

:end_parse_args

set "current_path=%cd%"

if "%build_examples%"=="on" (
    if not exist "%build_examples_path%" mkdir "%build_examples_path%"
    cd /d "%build_examples_path%"
    echo.
    echo Building examples
    cmake "%examples_path%" -DCMAKE_BUILD_TYPE=%build_type%
    cmake --build . --config %build_type%
)

cd /d "%current_path%"

echo Cleaning debug symbols ...
if exist "%bin_path%\*.pdb" del /f /q "%bin_path%\*.pdb"
if exist "%bin_path%\*.ilk" del /f /q "%bin_path%\*.ilk"
if exist "%bin_path%\*.exp" del /f /q "%bin_path%\*.exp"
if exist "%bin_path%\*.lib" del /f /q "%bin_path%\*.lib"

exit /b 0

:show_help
echo Usage: %~nx0 [OPTION]
echo.
echo Available options:
echo   -h, --help     Print this menu and exit
echo   debug          Compile the project in Debug mode (with symbols)
echo   release        Compile the project in Release mode (optimized)
echo   examples       Compile only the examples (default true)
echo.
echo  Compile examples in release mode
echo Example: %~nx0 example release
echo.
exit /b 0