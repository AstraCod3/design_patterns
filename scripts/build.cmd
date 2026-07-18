@echo off
setlocal enabledelayedexpansion

:: 1. Imposta la Root del progetto in modo sicuro al 100% senza manipolazione di stringhe
:: %~dp0 restituisce la cartella dello script (finisce sempre con \)
:: Entriamo nella cartella superiore (la root) e salviamo il percorso assoluto pulito
cd /d "%~dp0.."
set "root_path=%cd%"

:: 2. Definizione delle variabili globali
set "bin_path=%root_path%\bin"
set "build_base_path=%root_path%\build"
set "examples_source_path=%root_path%\examples"

:: Creazione della cartella bin globale se non esiste
if not exist "%bin_path%" mkdir "%bin_path%"

:: Default di compilazione
set "pattern_filter="
set "build_type=Release"

:: 3. Parsing degli argomenti (In qualsiasi ordine)
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

if not defined pattern_filter (
    set "pattern_filter=%~1"
    shift
    goto parse_args
)

echo Error: Invalid option '%~1'
echo Use -h or --help to see available options.
exit /b 1

:end_parse_args

if not defined pattern_filter (
    echo Error: Devi specificare il nome di un design pattern (es. singleton).
    echo Esempio d'uso: .^/scripts^/build.cmd singleton debug
    exit /b 1
)

set "current_path=%cd%"

:: Verifichiamo che l'esempio esista nella cartella globale examples
set "source_cpp=%examples_source_path%\example_%pattern_filter%.cpp"
if not exist "%source_cpp%" (
    echo Error: File sorgente non trovato: %source_cpp%
    exit /b 1
)

:: Impostiamo la cartella di build specifica richiesta: build/examples/<nome_pattern>
set "build_target_path=%build_base_path%\examples\%pattern_filter%"

echo.
echo ==============================================================================
echo Building Isolated Target via Zero-Modify CMake
echo Target Pattern: %pattern_filter% [%build_type%]
echo Source File:    %source_cpp%
echo Build Folder:   %build_target_path%
echo Bin Folder:     %bin_path%
==============================================================================
echo.

:: 4. Prepariamo la cartella isolata build/examples/<nome_pattern>
if exist "%build_target_path%" rmdir /s /q "%build_target_path%"
mkdir "%build_target_path%"
cd /d "%build_target_path%"

:: Copiamo SOLO il file .cpp richiesto e il CMakeLists.txt dentro la cartella di build
copy /y "%source_cpp%" ".\%pattern_filter%.cpp" >nul
copy /y "%examples_source_path%\CMakeLists.txt" ".\CMakeLists.txt" >nul

:: 5. Generazione dei file di configurazione CMake
cmake . -DCMAKE_BUILD_TYPE=%build_type%

:: 6. Compilazione effettiva
cmake --build . --config %build_type%

:: 7. Pulizia simboli e file temporanei copiati
echo.
echo Cleaning debug symbols and temp files...
del /f /q ".\%pattern_filter%.cpp" ".\CMakeLists.txt"
if exist "%bin_path%\*.pdb" del /f /q "%bin_path%\*.pdb"
if exist "%bin_path%\*.ilk" del /f /q "%bin_path%\*.ilk"
if exist "%bin_path%\*.exp" del /f /q "%bin_path%\*.exp"
if exist "%bin_path%\*.lib" del /f /q "%bin_path%\*.lib"

cd /d "%current_path%"
exit /b 0

:show_help
echo Usage: .\%~nx0 [pattern_name] [debug|release]
echo Example: .\%~nx0 singleton debug
exit /b 0
