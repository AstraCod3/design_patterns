@echo off

:: 1. Find the absolute directory of the script
set "script_path=%~dp0"
if "%script_path:~-1%"=="\" set "script_path=%script_path:~0,-1%"

:: 2. Convert relative paths to clean, fully-resolved absolute paths
for %%I in ("%script_path%\..") do set "root_path=%%~fI"
for %%I in ("%root_path%\bin") do set "bin_path=%%~fI"
for %%I in ("%root_path%\build") do set "build_path=%%~fI"
for %%I in ("%root_path%\examples") do set "examples_source_path=%%~fI"
