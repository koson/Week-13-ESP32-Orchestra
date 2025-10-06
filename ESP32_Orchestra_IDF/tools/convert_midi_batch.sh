#!/bin/bash
# 
# ESP32 Orchestra MIDI Batch Converter
# แปลงไฟล์ MIDI หลายไฟล์พร้อมกัน
#

set -e

SCRIPT_DIR="$(dirname "$0")"
MIDI_PARSER="$SCRIPT_DIR/midi_parser.py"
INPUT_DIR="$SCRIPT_DIR/../midi_files"
OUTPUT_DIR="$SCRIPT_DIR/../conductor/main/generated_songs"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}🎵 ESP32 Orchestra MIDI Batch Converter${NC}"
echo "=" * 50

# Check if Python script exists
if [ ! -f "$MIDI_PARSER" ]; then
    echo -e "${RED}❌ MIDI parser not found: $MIDI_PARSER${NC}"
    exit 1
fi

# Check Python dependencies
echo -e "${YELLOW}🔍 Checking Python dependencies...${NC}"
python3 -c "import mido" 2>/dev/null || {
    echo -e "${RED}❌ Missing dependency: mido${NC}"
    echo "Install with: pip install mido python-rtmidi"
    exit 1
}

# Create directories
mkdir -p "$INPUT_DIR"
mkdir -p "$OUTPUT_DIR"

# Check if input directory has MIDI files
MIDI_COUNT=$(find "$INPUT_DIR" -name "*.mid" -o -name "*.midi" | wc -l)

if [ "$MIDI_COUNT" -eq 0 ]; then
    echo -e "${YELLOW}⚠️  No MIDI files found in: $INPUT_DIR${NC}"
    echo "Please add some .mid or .midi files to convert"
    echo ""
    echo "Example MIDI files to try:"
    echo "- Twinkle Twinkle Little Star"
    echo "- Happy Birthday"
    echo "- Mary Had a Little Lamb" 
    echo "- Canon in D"
    echo ""
    echo "You can find free MIDI files at:"
    echo "- https://www.midiworld.com/"
    echo "- https://freemidi.org/"
    exit 1
fi

echo -e "${GREEN}📁 Found $MIDI_COUNT MIDI files${NC}"
echo ""

# Convert each MIDI file
converted_count=0
failed_count=0

for midi_file in "$INPUT_DIR"/*.mid "$INPUT_DIR"/*.midi; do
    # Skip if no files match pattern
    [ -f "$midi_file" ] || continue
    
    # Get filename without extension
    basename=$(basename "$midi_file")
    filename="${basename%.*}"
    output_file="$OUTPUT_DIR/${filename}.h"
    
    echo -e "${BLUE}🎼 Converting: $basename${NC}"
    
    # Run converter
    if python3 "$MIDI_PARSER" "$midi_file" "$output_file" --parts 4; then
        echo -e "${GREEN}✅ Success: ${filename}.h${NC}"
        ((converted_count++))
    else
        echo -e "${RED}❌ Failed: $basename${NC}"
        ((failed_count++))
    fi
    echo ""
done

# Generate combined header file
echo -e "${BLUE}📝 Generating combined header file...${NC}"

COMBINED_HEADER="$OUTPUT_DIR/all_generated_songs.h"
cat > "$COMBINED_HEADER" << 'EOF'
#ifndef ALL_GENERATED_SONGS_H
#define ALL_GENERATED_SONGS_H

/*
 * Auto-generated file containing all converted MIDI songs
 * Include this file in your midi_songs.h to use converted songs
 */

#include "orchestra_common.h"

EOF

# Include all generated headers
for header_file in "$OUTPUT_DIR"/*.h; do
    [ -f "$header_file" ] || continue
    [ "$header_file" != "$COMBINED_HEADER" ] || continue
    
    basename=$(basename "$header_file")
    echo "#include \"$basename\"" >> "$COMBINED_HEADER"
done

echo "" >> "$COMBINED_HEADER"

# Create songs array
echo "// Array of all generated songs" >> "$COMBINED_HEADER"
echo "static const orchestra_song_t* generated_songs[] = {" >> "$COMBINED_HEADER"

for header_file in "$OUTPUT_DIR"/*.h; do
    [ -f "$header_file" ] || continue
    [ "$header_file" != "$COMBINED_HEADER" ] || continue
    
    # Extract song variable name from header file
    song_var=$(grep "static const orchestra_song_t.*_song = {" "$header_file" | sed 's/.*orchestra_song_t \([^=]*\) = {.*/\1/' | head -1)
    if [ -n "$song_var" ]; then
        echo "    &$song_var," >> "$COMBINED_HEADER"
    fi
done

cat >> "$COMBINED_HEADER" << 'EOF'
    NULL  // End marker
};

#define GENERATED_SONGS_COUNT (sizeof(generated_songs) / sizeof(orchestra_song_t*) - 1)

// Helper function to get song by index
static inline const orchestra_song_t* get_generated_song(int index) {
    if (index >= 0 && index < GENERATED_SONGS_COUNT) {
        return generated_songs[index];
    }
    return NULL;
}

#endif // ALL_GENERATED_SONGS_H
EOF

echo -e "${GREEN}✅ Combined header created: all_generated_songs.h${NC}"

# Summary
echo ""
echo "=" * 50
echo -e "${GREEN}🎉 Conversion Summary${NC}"
echo -e "Successfully converted: ${GREEN}$converted_count${NC} files"
if [ "$failed_count" -gt 0 ]; then
    echo -e "Failed conversions: ${RED}$failed_count${NC} files"
fi
echo ""
echo -e "${BLUE}📄 Generated files:${NC}"
for header_file in "$OUTPUT_DIR"/*.h; do
    [ -f "$header_file" ] || continue
    basename=$(basename "$header_file")
    echo "  - $basename"
done

echo ""
echo -e "${YELLOW}📝 Next Steps:${NC}"
echo "1. Review generated .h files in: $OUTPUT_DIR"
echo "2. Include all_generated_songs.h in your conductor project"
echo "3. Add songs to your main song database"
echo "4. Build and test with your ESP32 Orchestra!"

echo ""
echo -e "${GREEN}🎵 Ready to rock your ESP32 Orchestra! 🎸${NC}"