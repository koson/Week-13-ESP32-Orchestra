#ifndef ORCHESTRA_TYPES_H
#define ORCHESTRA_TYPES_H

#include "orchestra_common.h"

// Note Event Structure for Orchestra
typedef struct {
    uint8_t note;           // MIDI note number (0 = rest)
    uint16_t duration_ms;   // ความยาวโน๊ต
    uint16_t delay_ms;      // หน่วงเวลาก่อนโน๊ตถัดไป
} note_event_t;

// Song Part Structure
typedef struct {
    const note_event_t* events;  // Array ของโน๊ต
    uint16_t event_count;        // จำนวนโน๊ต
    const char* part_name;       // ชื่อ part
} song_part_t;

// Complete Song Structure  
typedef struct {
    const char* song_name;      // ชื่อเพลง
    uint8_t song_id;           // รหัสเพลง
    uint8_t tempo_bpm;         // Beats per minute
    uint8_t part_count;        // จำนวน parts
    const song_part_t* parts;  // Array ของ parts
} orchestra_song_t;

#endif // ORCHESTRA_TYPES_H