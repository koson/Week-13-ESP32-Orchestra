#ifndef MIDI_SONGS_H
#define MIDI_SONGS_H

#include "orchestra_types.h"

// =============================================================
// 🎵 SONG 1: Twinkle Twinkle Little Star (4 Parts)
// =============================================================

// Part A: Main Melody
static const note_event_t twinkle_melody[] = {
    {NOTE_C4, 400, 100},  // Twin-
    {NOTE_C4, 400, 100},  // -kle
    {NOTE_G4, 400, 100},  // twin-
    {NOTE_G4, 400, 100},  // -kle
    {NOTE_A4, 400, 100},  // lit-
    {NOTE_A4, 400, 100},  // -tle
    {NOTE_G4, 800, 200},  // star
    
    {NOTE_F4, 400, 100},  // How
    {NOTE_F4, 400, 100},  // I
    {NOTE_E4, 400, 100},  // won-
    {NOTE_E4, 400, 100},  // -der
    {NOTE_D4, 400, 100},  // what
    {NOTE_D4, 400, 100},  // you
    {NOTE_C4, 800, 200},  // are
    
    {NOTE_G4, 400, 100},  // Up
    {NOTE_G4, 400, 100},  // a-
    {NOTE_F4, 400, 100},  // -bove
    {NOTE_F4, 400, 100},  // the
    {NOTE_E4, 400, 100},  // world
    {NOTE_E4, 400, 100},  // so
    {NOTE_D4, 800, 200},  // high
    
    {NOTE_G4, 400, 100},  // Like
    {NOTE_G4, 400, 100},  // a
    {NOTE_F4, 400, 100},  // dia-
    {NOTE_F4, 400, 100},  // -mond
    {NOTE_E4, 400, 100},  // in
    {NOTE_E4, 400, 100},  // the
    {NOTE_D4, 800, 200},  // sky
    
    {NOTE_C4, 400, 100},  // Twin-
    {NOTE_C4, 400, 100},  // -kle
    {NOTE_G4, 400, 100},  // twin-
    {NOTE_G4, 400, 100},  // -kle
    {NOTE_A4, 400, 100},  // lit-
    {NOTE_A4, 400, 100},  // -tle
    {NOTE_G4, 800, 200},  // star
    
    {NOTE_F4, 400, 100},  // How
    {NOTE_F4, 400, 100},  // I
    {NOTE_E4, 400, 100},  // won-
    {NOTE_E4, 400, 100},  // -der
    {NOTE_D4, 400, 100},  // what
    {NOTE_D4, 400, 100},  // you
    {NOTE_C4, 800, 400},  // are
    {NOTE_REST, 0, 0}     // End
};

// Part B: Harmony (3rd above melody)
static const note_event_t twinkle_harmony[] = {
    {NOTE_E4, 400, 100},  // Harmony for C
    {NOTE_E4, 400, 100},  // Harmony for C
    {NOTE_B4, 400, 100},  // Harmony for G
    {NOTE_B4, 400, 100},  // Harmony for G
    {NOTE_C5, 400, 100},  // Harmony for A
    {NOTE_C5, 400, 100},  // Harmony for A
    {NOTE_B4, 800, 200},  // Harmony for G
    
    {NOTE_A4, 400, 100},  // Harmony for F
    {NOTE_A4, 400, 100},  // Harmony for F
    {NOTE_G4, 400, 100},  // Harmony for E
    {NOTE_G4, 400, 100},  // Harmony for E
    {NOTE_F4, 400, 100},  // Harmony for D
    {NOTE_F4, 400, 100},  // Harmony for D
    {NOTE_E4, 800, 200},  // Harmony for C
    
    {NOTE_B4, 400, 100},  // Harmony for G
    {NOTE_B4, 400, 100},  // Harmony for G
    {NOTE_A4, 400, 100},  // Harmony for F
    {NOTE_A4, 400, 100},  // Harmony for F
    {NOTE_G4, 400, 100},  // Harmony for E
    {NOTE_G4, 400, 100},  // Harmony for E
    {NOTE_F4, 800, 200},  // Harmony for D
    
    {NOTE_B4, 400, 100},  // Harmony for G
    {NOTE_B4, 400, 100},  // Harmony for G
    {NOTE_A4, 400, 100},  // Harmony for F
    {NOTE_A4, 400, 100},  // Harmony for F
    {NOTE_G4, 400, 100},  // Harmony for E
    {NOTE_G4, 400, 100},  // Harmony for E
    {NOTE_F4, 800, 200},  // Harmony for D
    
    {NOTE_E4, 400, 100},  // Harmony for C
    {NOTE_E4, 400, 100},  // Harmony for C
    {NOTE_B4, 400, 100},  // Harmony for G
    {NOTE_B4, 400, 100},  // Harmony for G
    {NOTE_C5, 400, 100},  // Harmony for A
    {NOTE_C5, 400, 100},  // Harmony for A
    {NOTE_B4, 800, 200},  // Harmony for G
    
    {NOTE_A4, 400, 100},  // Harmony for F
    {NOTE_A4, 400, 100},  // Harmony for F
    {NOTE_G4, 400, 100},  // Harmony for E
    {NOTE_G4, 400, 100},  // Harmony for E
    {NOTE_F4, 400, 100},  // Harmony for D
    {NOTE_F4, 400, 100},  // Harmony for D
    {NOTE_E4, 800, 400},  // Harmony for C
    {NOTE_REST, 0, 0}     // End
};

// Part C: Bass Line (octave lower)
static const note_event_t twinkle_bass[] = {
    {NOTE_C3, 800, 200},  // C chord
    {NOTE_C3, 800, 200},  // C chord
    {NOTE_F3, 800, 200},  // F chord
    {NOTE_C3, 800, 200},  // C chord
    
    {NOTE_F3, 800, 200},  // F chord
    {NOTE_C3, 800, 200},  // C chord
    {NOTE_G3, 800, 200},  // G chord
    {NOTE_C3, 800, 200},  // C chord
    
    {NOTE_C3, 800, 200},  // C chord
    {NOTE_F3, 800, 200},  // F chord
    {NOTE_C3, 800, 200},  // C chord
    {NOTE_G3, 800, 200},  // G chord
    
    {NOTE_C3, 800, 200},  // C chord
    {NOTE_F3, 800, 200},  // F chord
    {NOTE_C3, 800, 200},  // C chord
    {NOTE_G3, 800, 200},  // G chord
    
    {NOTE_C3, 800, 200},  // C chord
    {NOTE_C3, 800, 200},  // C chord
    {NOTE_F3, 800, 200},  // F chord
    {NOTE_C3, 800, 200},  // C chord
    
    {NOTE_F3, 800, 200},  // F chord
    {NOTE_C3, 800, 200},  // C chord
    {NOTE_G3, 800, 200},  // G chord
    {NOTE_C3, 800, 400},  // C chord (end)
    {NOTE_REST, 0, 0}     // End
};

// Part D: Rhythm/Percussion (using different frequencies)
static const note_event_t twinkle_rhythm[] = {
    {NOTE_G3, 200, 200},  // Beat 1
    {NOTE_REST, 0, 200},  // Rest
    {NOTE_G3, 200, 200},  // Beat 2
    {NOTE_REST, 0, 200},  // Rest
    {NOTE_G3, 200, 200},  // Beat 3
    {NOTE_REST, 0, 200},  // Rest
    {NOTE_G3, 200, 600},  // Beat 4
    
    {NOTE_G3, 200, 200},  // Beat 1
    {NOTE_REST, 0, 200},  // Rest
    {NOTE_G3, 200, 200},  // Beat 2
    {NOTE_REST, 0, 200},  // Rest
    {NOTE_G3, 200, 200},  // Beat 3
    {NOTE_REST, 0, 200},  // Rest
    {NOTE_G3, 200, 600},  // Beat 4
    
    // ... ทำซ้ำตามจำนวนมาตร
    {NOTE_G3, 200, 200}, {NOTE_REST, 0, 200}, {NOTE_G3, 200, 200}, {NOTE_REST, 0, 200},
    {NOTE_G3, 200, 200}, {NOTE_REST, 0, 200}, {NOTE_G3, 200, 600},
    {NOTE_G3, 200, 200}, {NOTE_REST, 0, 200}, {NOTE_G3, 200, 200}, {NOTE_REST, 0, 200},
    {NOTE_G3, 200, 200}, {NOTE_REST, 0, 200}, {NOTE_G3, 200, 600},
    {NOTE_G3, 200, 200}, {NOTE_REST, 0, 200}, {NOTE_G3, 200, 200}, {NOTE_REST, 0, 200},
    {NOTE_G3, 200, 200}, {NOTE_REST, 0, 200}, {NOTE_G3, 200, 600},
    {NOTE_G3, 200, 200}, {NOTE_REST, 0, 200}, {NOTE_G3, 200, 200}, {NOTE_REST, 0, 200},
    {NOTE_G3, 200, 200}, {NOTE_REST, 0, 200}, {NOTE_G3, 200, 400},
    {NOTE_REST, 0, 0}     // End
};

// Twinkle Star Parts Array
static const song_part_t twinkle_parts[] = {
    {twinkle_melody,  sizeof(twinkle_melody)/sizeof(note_event_t) - 1,  "Melody"},
    {twinkle_harmony, sizeof(twinkle_harmony)/sizeof(note_event_t) - 1, "Harmony"},
    {twinkle_bass,    sizeof(twinkle_bass)/sizeof(note_event_t) - 1,    "Bass"},
    {twinkle_rhythm,  sizeof(twinkle_rhythm)/sizeof(note_event_t) - 1,  "Rhythm"}
};

// =============================================================
// 🎵 SONG 2: Happy Birthday (3 Parts)
// =============================================================

// Part A: Main Melody
static const note_event_t birthday_melody[] = {
    {NOTE_REST, 0, 400},  // Pick up
    {NOTE_C4, 200, 100},  // Hap-
    {NOTE_C4, 400, 100},  // -py
    {NOTE_D4, 800, 100},  // Birth-
    {NOTE_C4, 800, 100},  // -day
    {NOTE_F4, 800, 100},  // to
    {NOTE_E4, 1200, 200}, // you
    
    {NOTE_C4, 200, 100},  // Hap-
    {NOTE_C4, 400, 100},  // -py
    {NOTE_D4, 800, 100},  // Birth-
    {NOTE_C4, 800, 100},  // -day
    {NOTE_G4, 800, 100},  // to
    {NOTE_F4, 1200, 200}, // you
    
    {NOTE_C4, 200, 100},  // Hap-
    {NOTE_C4, 400, 100},  // -py
    {NOTE_C5, 800, 100},  // Birth-
    {NOTE_A4, 800, 100},  // -day
    {NOTE_F4, 800, 100},  // dear
    {NOTE_E4, 800, 100},  // [name]
    {NOTE_D4, 1200, 200}, // [name]
    
    {NOTE_B4, 200, 100},  // Hap-
    {NOTE_B4, 400, 100},  // -py
    {NOTE_A4, 800, 100},  // Birth-
    {NOTE_F4, 800, 100},  // -day
    {NOTE_G4, 800, 100},  // to
    {NOTE_F4, 1200, 400}, // you
    {NOTE_REST, 0, 0}     // End
};

// Part B: Harmony
static const note_event_t birthday_harmony[] = {
    {NOTE_REST, 0, 400},
    {NOTE_A3, 200, 100},  // Harmony
    {NOTE_A3, 400, 100},
    {NOTE_B3, 800, 100},
    {NOTE_A3, 800, 100},
    {NOTE_D4, 800, 100},
    {NOTE_C4, 1200, 200},
    
    {NOTE_A3, 200, 100},
    {NOTE_A3, 400, 100},
    {NOTE_B3, 800, 100},
    {NOTE_A3, 800, 100},
    {NOTE_E4, 800, 100},
    {NOTE_D4, 1200, 200},
    
    {NOTE_A3, 200, 100},
    {NOTE_A3, 400, 100},
    {NOTE_A4, 800, 100},
    {NOTE_F4, 800, 100},
    {NOTE_D4, 800, 100},
    {NOTE_C4, 800, 100},
    {NOTE_B3, 1200, 200},
    
    {NOTE_G4, 200, 100},
    {NOTE_G4, 400, 100},
    {NOTE_F4, 800, 100},
    {NOTE_D4, 800, 100},
    {NOTE_E4, 800, 100},
    {NOTE_D4, 1200, 400},
    {NOTE_REST, 0, 0}
};

// Part C: Bass
static const note_event_t birthday_bass[] = {
    {NOTE_REST, 0, 400},
    {NOTE_F3, 600, 200},  // F chord
    {NOTE_F3, 800, 100},
    {NOTE_C3, 800, 100},  // C chord
    {NOTE_F3, 800, 100},  // F chord
    {NOTE_C3, 1200, 200}, // C chord
    
    {NOTE_F3, 600, 200},  // F chord
    {NOTE_F3, 800, 100},
    {NOTE_C3, 800, 100},  // C chord
    {NOTE_G3, 800, 100},  // G chord
    {NOTE_F3, 1200, 200}, // F chord
    
    {NOTE_F3, 600, 200},  // F chord
    {NOTE_F3, 800, 100},
    {NOTE_F3, 800, 100},  // F chord
    {NOTE_F3, 800, 100},  // F chord
    {NOTE_B3, 800, 100},  // Bb chord
    {NOTE_A3, 800, 100},  // A chord
    {NOTE_G3, 1200, 200}, // G chord
    
    {NOTE_G3, 600, 200},  // G chord
    {NOTE_G3, 800, 100},
    {NOTE_F3, 800, 100},  // F chord
    {NOTE_F3, 800, 100},  // F chord
    {NOTE_C3, 800, 100},  // C chord
    {NOTE_F3, 1200, 400}, // F chord
    {NOTE_REST, 0, 0}
};

// Happy Birthday Parts Array
static const song_part_t birthday_parts[] = {
    {birthday_melody,  sizeof(birthday_melody)/sizeof(note_event_t) - 1,  "Melody"},
    {birthday_harmony, sizeof(birthday_harmony)/sizeof(note_event_t) - 1, "Harmony"},
    {birthday_bass,    sizeof(birthday_bass)/sizeof(note_event_t) - 1,    "Bass"}
};

// =============================================================
// 🎵 SONG 3: Mary Had a Little Lamb (2 Parts)
// =============================================================

// Part A: Melody
static const note_event_t mary_melody[] = {
    {NOTE_E4, 400, 100},  // Ma-
    {NOTE_D4, 400, 100},  // -ry
    {NOTE_C4, 400, 100},  // had
    {NOTE_D4, 400, 100},  // a
    {NOTE_E4, 400, 100},  // lit-
    {NOTE_E4, 400, 100},  // -tle
    {NOTE_E4, 800, 200},  // lamb
    
    {NOTE_D4, 400, 100},  // lit-
    {NOTE_D4, 400, 100},  // -tle
    {NOTE_D4, 800, 200},  // lamb
    {NOTE_E4, 400, 100},  // lit-
    {NOTE_E4, 400, 100},  // -tle
    {NOTE_E4, 800, 200},  // lamb
    
    {NOTE_E4, 400, 100},  // Ma-
    {NOTE_D4, 400, 100},  // -ry
    {NOTE_C4, 400, 100},  // had
    {NOTE_D4, 400, 100},  // a
    {NOTE_E4, 400, 100},  // lit-
    {NOTE_E4, 400, 100},  // -tle
    {NOTE_E4, 400, 100},  // lamb
    {NOTE_D4, 400, 100},  // its
    {NOTE_D4, 400, 100},  // fleece
    {NOTE_E4, 400, 100},  // was
    {NOTE_D4, 400, 100},  // white
    {NOTE_C4, 800, 400},  // as snow
    {NOTE_REST, 0, 0}     // End
};

// Part B: Harmony
static const note_event_t mary_harmony[] = {
    {NOTE_C4, 400, 100},  // Harmony
    {NOTE_B3, 400, 100},
    {NOTE_A3, 400, 100},
    {NOTE_B3, 400, 100},
    {NOTE_C4, 400, 100},
    {NOTE_C4, 400, 100},
    {NOTE_C4, 800, 200},
    
    {NOTE_B3, 400, 100},
    {NOTE_B3, 400, 100},
    {NOTE_B3, 800, 200},
    {NOTE_C4, 400, 100},
    {NOTE_C4, 400, 100},
    {NOTE_C4, 800, 200},
    
    {NOTE_C4, 400, 100},
    {NOTE_B3, 400, 100},
    {NOTE_A3, 400, 100},
    {NOTE_B3, 400, 100},
    {NOTE_C4, 400, 100},
    {NOTE_C4, 400, 100},
    {NOTE_C4, 400, 100},
    {NOTE_B3, 400, 100},
    {NOTE_B3, 400, 100},
    {NOTE_C4, 400, 100},
    {NOTE_B3, 400, 100},
    {NOTE_A3, 800, 400},
    {NOTE_REST, 0, 0}
};

// Mary Parts Array
static const song_part_t mary_parts[] = {
    {mary_melody,  sizeof(mary_melody)/sizeof(note_event_t) - 1,  "Melody"},
    {mary_harmony, sizeof(mary_harmony)/sizeof(note_event_t) - 1, "Harmony"}
};

// =============================================================
// 🎵 All Songs Database
// =============================================================

// Include Thailand song definitions after type definitions
#include "Thailand.h"
#include "titanic_orchestra.h"

static const orchestra_song_t all_songs[] = {
    {
        .song_name = "Twinkle Twinkle Little Star",
        .song_id = SONG_TWINKLE_STAR,
        .tempo_bpm = 120,
        .part_count = 4,
        .parts = twinkle_parts
    },
    {
        .song_name = "Happy Birthday",
        .song_id = SONG_HAPPY_BIRTHDAY,
        .tempo_bpm = 120,
        .part_count = 3,
        .parts = birthday_parts
    },
    {
        .song_name = "Mary Had a Little Lamb",
        .song_id = SONG_MARY_LAMB,
        .tempo_bpm = 140,
        .part_count = 2,
        .parts = mary_parts
    },
    {
        .song_name = "Thailand",
        .song_id = SONG_THAILAND,
        .tempo_bpm = 116,
        .part_count = 4,
        .parts = Thailand_parts
    },
    {
        .song_name = "Movie_Themes_-_Titanic_-_My_Heart_Will_Go_On_(Techno_Mix)",
        .song_id = SONG_MOVIE_THEMES___TITANIC___MY_HEART_WILL_GO_ON_TECHNO_MIX,
        .tempo_bpm = 135,
        .part_count = 4,
        .parts = Movie_Themes___Titanic___My_Heart_Will_Go_On_Techno_Mix_parts
    }
};

#define TOTAL_SONGS (sizeof(all_songs) / sizeof(orchestra_song_t))

// Helper function to get song by ID
static inline const orchestra_song_t* get_song_by_id(uint8_t song_id) {
    for (int i = 0; i < TOTAL_SONGS; i++) {
        if (all_songs[i].song_id == song_id) {
            return &all_songs[i];
        }
    }
    return NULL;
}

#endif // MIDI_SONGS_H