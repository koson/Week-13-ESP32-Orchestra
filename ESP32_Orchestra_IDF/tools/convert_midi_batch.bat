@echo off
REM ESP32 Orchestra MIDI Batch Converter for Windows
REM แปลงไฟล์ MIDI หลายไฟล์พร้อมกัน

setlocal enabledelayedexpansion

set "SCRIPT_DIR=%~dp0"
set "MIDI_PARSER=%SCRIPT_DIR%midi_parser.py"
set "INPUT_DIR=%SCRIPT_DIR%..\midi_files"
set "OUTPUT_DIR=%SCRIPT_DIR%..\conductor\main\generated_songs"

echo 🎵 ESP32 Orchestra MIDI Batch Converter
echo ==================================================

REM Check if Python script exists
if not exist "%MIDI_PARSER%" (
    echo ❌ MIDI parser not found: %MIDI_PARSER%
    pause
    exit /b 1
)

REM Check Python dependencies
echo 🔍 Checking Python dependencies...
python -c "import mido" 2>nul || (
    echo ❌ Missing dependency: mido
    echo Install with: pip install mido python-rtmidi
    pause
    exit /b 1
)

REM Create directories
if not exist "%INPUT_DIR%" mkdir "%INPUT_DIR%"
if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"

REM Check if input directory has MIDI files
set MIDI_COUNT=0
for %%f in ("%INPUT_DIR%\*.mid" "%INPUT_DIR%\*.midi") do (
    if exist "%%f" set /a MIDI_COUNT+=1
)

if !MIDI_COUNT! equ 0 (
    echo ⚠️  No MIDI files found in: %INPUT_DIR%
    echo Please add some .mid or .midi files to convert
    echo.
    echo Example MIDI files to try:
    echo - Twinkle Twinkle Little Star
    echo - Happy Birthday
    echo - Mary Had a Little Lamb
    echo - Canon in D
    echo.
    echo You can find free MIDI files at:
    echo - https://www.midiworld.com/
    echo - https://freemidi.org/
    pause
    exit /b 1
)

echo 📁 Found !MIDI_COUNT! MIDI files
echo.

REM Convert each MIDI file
set converted_count=0
set failed_count=0

for %%f in ("%INPUT_DIR%\*.mid" "%INPUT_DIR%\*.midi") do (
    if exist "%%f" (
        set "basename=%%~nf"
        set "output_file=%OUTPUT_DIR%\!basename!.h"
        
        echo 🎼 Converting: %%~nxf
        
        python "%MIDI_PARSER%" "%%f" "!output_file!" --parts 4
        if !errorlevel! equ 0 (
            echo ✅ Success: !basename!.h
            set /a converted_count+=1
        ) else (
            echo ❌ Failed: %%~nxf
            set /a failed_count+=1
        )
        echo.
    )
)

REM Generate combined header file
echo 📝 Generating combined header file...

set "COMBINED_HEADER=%OUTPUT_DIR%\all_generated_songs.h"

echo #ifndef ALL_GENERATED_SONGS_H > "%COMBINED_HEADER%"
echo #define ALL_GENERATED_SONGS_H >> "%COMBINED_HEADER%"
echo. >> "%COMBINED_HEADER%"
echo /* >> "%COMBINED_HEADER%"
echo  * Auto-generated file containing all converted MIDI songs >> "%COMBINED_HEADER%"
echo  * Include this file in your midi_songs.h to use converted songs >> "%COMBINED_HEADER%"
echo  */ >> "%COMBINED_HEADER%"
echo. >> "%COMBINED_HEADER%"
echo #include "orchestra_common.h" >> "%COMBINED_HEADER%"
echo. >> "%COMBINED_HEADER%"

REM Include all generated headers
for %%f in ("%OUTPUT_DIR%\*.h") do (
    if exist "%%f" (
        if not "%%~nxf"=="all_generated_songs.h" (
            echo #include "%%~nxf" >> "%COMBINED_HEADER%"
        )
    )
)

echo. >> "%COMBINED_HEADER%"
echo // Array of all generated songs >> "%COMBINED_HEADER%"
echo static const orchestra_song_t* generated_songs[] = { >> "%COMBINED_HEADER%"

REM Add songs to array (simplified version)
for %%f in ("%OUTPUT_DIR%\*.h") do (
    if exist "%%f" (
        if not "%%~nxf"=="all_generated_songs.h" (
            REM Extract song variable name (simplified)
            set "song_name=%%~nf"
            echo     ^&!song_name!_song, >> "%COMBINED_HEADER%"
        )
    )
)

echo     NULL  // End marker >> "%COMBINED_HEADER%"
echo }; >> "%COMBINED_HEADER%"
echo. >> "%COMBINED_HEADER%"
echo #define GENERATED_SONGS_COUNT (sizeof(generated_songs) / sizeof(orchestra_song_t*) - 1) >> "%COMBINED_HEADER%"
echo. >> "%COMBINED_HEADER%"
echo // Helper function to get song by index >> "%COMBINED_HEADER%"
echo static inline const orchestra_song_t* get_generated_song(int index) { >> "%COMBINED_HEADER%"
echo     if (index ^>= 0 ^&^& index ^< GENERATED_SONGS_COUNT) { >> "%COMBINED_HEADER%"
echo         return generated_songs[index]; >> "%COMBINED_HEADER%"
echo     } >> "%COMBINED_HEADER%"
echo     return NULL; >> "%COMBINED_HEADER%"
echo } >> "%COMBINED_HEADER%"
echo. >> "%COMBINED_HEADER%"
echo #endif // ALL_GENERATED_SONGS_H >> "%COMBINED_HEADER%"

echo ✅ Combined header created: all_generated_songs.h

REM Summary
echo.
echo ==================================================
echo 🎉 Conversion Summary
echo Successfully converted: !converted_count! files
if !failed_count! gtr 0 (
    echo Failed conversions: !failed_count! files
)
echo.
echo 📄 Generated files:
for %%f in ("%OUTPUT_DIR%\*.h") do (
    if exist "%%f" (
        echo   - %%~nxf
    )
)

echo.
echo 📝 Next Steps:
echo 1. Review generated .h files in: %OUTPUT_DIR%
echo 2. Include all_generated_songs.h in your conductor project
echo 3. Add songs to your main song database
echo 4. Build and test with your ESP32 Orchestra!

echo.
echo 🎵 Ready to rock your ESP32 Orchestra! 🎸
pause