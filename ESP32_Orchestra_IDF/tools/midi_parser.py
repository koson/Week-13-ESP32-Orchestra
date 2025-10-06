#!/usr/bin/env python3
"""
MIDI to ESP32 Orchestra Converter
แปลงไฟล์ MIDI เป็น C header file สำหรับ ESP32 Orchestra

วิธีติดตั้ง dependencies:
pip install mido python-rtmidi

วิธีใช้งาน:
python midi_parser.py input.mid output.h [max_parts]
"""

import sys
import os
import argparse
from typing import List, Dict, Tuple, Optional
import mido
from mido import MidiFile, tick2second

class MidiNote:
    def __init__(self, note: int, start_time: float, end_time: float, velocity: int, channel: int):
        self.note = note
        self.start_time = start_time  # seconds
        self.end_time = end_time      # seconds
        self.velocity = velocity
        self.channel = channel
        
    @property
    def duration_ms(self) -> int:
        return int((self.end_time - self.start_time) * 1000)
    
    @property
    def start_time_ms(self) -> int:
        return int(self.start_time * 1000)

class OrchestralPart:
    def __init__(self, part_id: int, name: str):
        self.part_id = part_id
        self.name = name
        self.notes: List[MidiNote] = []
        
    def add_note(self, note: MidiNote):
        self.notes.append(note)
        
    def sort_notes(self):
        """เรียงโน๊ตตามเวลา"""
        self.notes.sort(key=lambda n: n.start_time)

class MidiToOrchestra:
    def __init__(self, max_parts: int = 4):
        self.max_parts = max_parts
        self.parts: List[OrchestralPart] = []
        self.tempo_bpm = 120
        self.song_name = "Unknown Song"
        self.total_duration = 0.0
        
    def parse_midi_file(self, midi_path: str) -> bool:
        """แปลงไฟล์ MIDI เป็น orchestral parts"""
        try:
            mid = MidiFile(midi_path)
            self.song_name = os.path.splitext(os.path.basename(midi_path))[0]
            
            print(f"📁 Loading MIDI file: {midi_path}")
            print(f"🎵 Song: {self.song_name}")
            print(f"📊 Type: {mid.type}, Tracks: {len(mid.tracks)}, Ticks per beat: {mid.ticks_per_beat}")
            
            # รวมเหตุการณ์ทั้งหมดจากทุก track
            all_events = []
            current_time = 0
            
            for i, track in enumerate(mid.tracks):
                current_time = 0
                active_notes = {}  # note_number -> (start_time, velocity, channel)
                
                print(f"🎼 Processing track {i}: {track.name}")
                
                for msg in track:
                    current_time += msg.time
                    absolute_time = tick2second(current_time, mid.ticks_per_beat, 500000)  # Default tempo
                    
                    if msg.type == 'set_tempo':
                        # คำนวณ BPM จาก microseconds per beat
                        microseconds_per_beat = msg.tempo
                        self.tempo_bpm = int(60000000 / microseconds_per_beat)
                        print(f"🎵 Tempo: {self.tempo_bpm} BPM")
                        
                    elif msg.type == 'note_on' and msg.velocity > 0:
                        # เริ่มโน๊ต
                        key = (msg.note, msg.channel)
                        active_notes[key] = (absolute_time, msg.velocity, msg.channel)
                        
                    elif msg.type == 'note_off' or (msg.type == 'note_on' and msg.velocity == 0):
                        # จบโน๊ต
                        key = (msg.note, msg.channel)
                        if key in active_notes:
                            start_time, velocity, channel = active_notes[key]
                            note = MidiNote(msg.note, start_time, absolute_time, velocity, channel)
                            all_events.append(note)
                            del active_notes[key]
                
                # Update total duration
                self.total_duration = max(self.total_duration, absolute_time)
            
            print(f"⏱️  Total duration: {self.total_duration:.2f} seconds")
            print(f"🎹 Total notes: {len(all_events)}")
            
            # แบ่งโน๊ตเป็น parts
            self._distribute_notes_to_parts(all_events)
            
            return True
            
        except Exception as e:
            print(f"❌ Error parsing MIDI file: {e}")
            return False
    
    def _distribute_notes_to_parts(self, notes: List[MidiNote]):
        """แบ่งโน๊ตเป็น parts ตาม channel หรือ pitch range"""
        
        # สร้าง parts
        part_names = ["Melody", "Harmony", "Bass", "Rhythm", "Percussion", "Effects"]
        for i in range(min(self.max_parts, len(part_names))):
            self.parts.append(OrchestralPart(i, part_names[i]))
        
        # กรองและแบ่งโน๊ต
        if len(notes) == 0:
            print("⚠️  No notes found in MIDI file")
            return
            
        # แบ่งตาม pitch range
        melody_notes = []    # High notes (C5 and above)
        harmony_notes = []   # Mid-high notes (C4-B4)
        bass_notes = []      # Low notes (below C4)
        rhythm_notes = []    # Channel 9 (drums) or very short notes
        
        for note in notes:
            if note.channel == 9:  # MIDI channel 10 (drums)
                rhythm_notes.append(note)
            elif note.note >= 72:  # C5 and above
                melody_notes.append(note)
            elif note.note >= 60:  # C4 to B4
                harmony_notes.append(note)
            else:  # Below C4
                bass_notes.append(note)
        
        # กำหนดโน๊ตให้ parts
        note_groups = [melody_notes, harmony_notes, bass_notes, rhythm_notes]
        
        for i, part in enumerate(self.parts):
            if i < len(note_groups):
                part.notes = note_groups[i]
                part.sort_notes()
                print(f"🎼 Part {i} ({part.name}): {len(part.notes)} notes")
    
    def generate_c_header(self, output_path: str) -> bool:
        """สร้าง C header file"""
        try:
            with open(output_path, 'w', encoding='utf-8') as f:
                self._write_header(f)
                self._write_note_arrays(f)
                self._write_parts_array(f)
                self._write_song_struct(f)
                self._write_footer(f)
            
            print(f"✅ Generated C header: {output_path}")
            return True
            
        except Exception as e:
            print(f"❌ Error generating C header: {e}")
            return False
    
    def _write_header(self, f):
        """เขียน header ของไฟล์"""
        safe_name = self._make_safe_name(self.song_name)
        f.write(f"""#ifndef MIDI_{safe_name.upper()}_H
#define MIDI_{safe_name.upper()}_H

/*
 * Auto-generated MIDI file: {self.song_name}
 * Duration: {self.total_duration:.2f} seconds
 * Tempo: {self.tempo_bpm} BPM
 * Parts: {len(self.parts)}
 * Generated by: ESP32 Orchestra MIDI Parser
 */

#include "orchestra_common.h"

""")
    
    def _write_note_arrays(self, f):
        """เขียน arrays ของโน๊ตแต่ละ part"""
        safe_name = self._make_safe_name(self.song_name)
        
        for part in self.parts:
            f.write(f"// Part {part.part_id}: {part.name}\n")
            f.write(f"static const note_event_t {safe_name}_{part.name.lower()}[] = {{\n")
            
            if not part.notes:
                f.write("    {NOTE_REST, 0, 0}  // Empty part\n")
            else:
                last_end_time = 0
                
                for note in part.notes:
                    # คำนวณ delay จากโน๊ตก่อนหน้า
                    delay_ms = max(0, note.start_time_ms - last_end_time)
                    
                    # แปลง MIDI note เป็น NOTE_xxx
                    note_name = self._midi_to_note_name(note.note)
                    
                    f.write(f"    {{{note_name}, {note.duration_ms}, {delay_ms}}},")
                    f.write(f"  // Note {note.note} ({self._note_to_string(note.note)})")
                    f.write(f" - {note.start_time_ms}ms\n")
                    
                    last_end_time = note.start_time_ms + note.duration_ms
                
                f.write("    {NOTE_REST, 0, 0}  // End of part\n")
            
            f.write("};\n\n")
    
    def _write_parts_array(self, f):
        """เขียน array ของ parts"""
        safe_name = self._make_safe_name(self.song_name)
        
        f.write(f"// {self.song_name} Parts Array\n")
        f.write(f"static const song_part_t {safe_name}_parts[] = {{\n")
        
        for part in self.parts:
            part_name_lower = part.name.lower()
            f.write(f"    {{{safe_name}_{part_name_lower}, ")
            f.write(f"sizeof({safe_name}_{part_name_lower})/sizeof(note_event_t) - 1, ")
            f.write(f'"{part.name}"}},\n')
        
        f.write("};\n\n")
    
    def _write_song_struct(self, f):
        """เขียน song structure"""
        safe_name = self._make_safe_name(self.song_name)
        song_id = f"SONG_{safe_name.upper()}"
        
        f.write(f"// {self.song_name} Song Definition\n")
        f.write(f"#define {song_id} {hash(self.song_name) & 0xFF}  // Auto-generated ID\n\n")
        
        f.write(f"static const orchestra_song_t {safe_name}_song = {{\n")
        f.write(f'    .song_name = "{self.song_name}",\n')
        f.write(f"    .song_id = {song_id},\n")
        f.write(f"    .tempo_bpm = {self.tempo_bpm},\n")
        f.write(f"    .part_count = {len(self.parts)},\n")
        f.write(f"    .parts = {safe_name}_parts\n")
        f.write("};\n\n")
    
    def _write_footer(self, f):
        """เขียน footer ของไฟล์"""
        safe_name = self._make_safe_name(self.song_name)
        f.write(f"""// Helper function to get the song
static inline const orchestra_song_t* get_{safe_name}_song(void) {{
    return &{safe_name}_song;
}}

#endif // MIDI_{safe_name.upper()}_H
""")
    
    def _make_safe_name(self, name: str) -> str:
        """แปลงชื่อให้ใช้ในโค้ด C ได้"""
        safe = ""
        for char in name:
            if char.isalnum():
                safe += char
            elif char in " -_.":
                safe += "_"
        return safe.strip("_")
    
    def _midi_to_note_name(self, midi_note: int) -> str:
        """แปลง MIDI note number เป็น NOTE_xxx"""
        if midi_note == 0:
            return "NOTE_REST"
        
        note_names = ["C", "CS", "D", "DS", "E", "F", "FS", "G", "GS", "A", "AS", "B"]
        octave = (midi_note - 12) // 12
        note = note_names[midi_note % 12]
        
        return f"NOTE_{note}{octave}"
    
    def _note_to_string(self, midi_note: int) -> str:
        """แปลง MIDI note เป็นชื่อโน๊ตที่อ่านได้"""
        if midi_note == 0:
            return "REST"
        
        note_names = ["C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"]
        octave = (midi_note - 12) // 12
        note = note_names[midi_note % 12]
        
        return f"{note}{octave}"

def main():
    parser = argparse.ArgumentParser(description="Convert MIDI files to ESP32 Orchestra format")
    parser.add_argument("input", help="Input MIDI file (.mid)")
    parser.add_argument("output", help="Output C header file (.h)")
    parser.add_argument("--parts", type=int, default=4, help="Maximum number of parts (default: 4)")
    parser.add_argument("--tempo", type=int, help="Override tempo BPM")
    
    args = parser.parse_args()
    
    if not os.path.exists(args.input):
        print(f"❌ Input file not found: {args.input}")
        return 1
    
    print("🎵 ESP32 Orchestra MIDI Parser")
    print("=" * 50)
    
    converter = MidiToOrchestra(max_parts=args.parts)
    
    # Parse MIDI file
    if not converter.parse_midi_file(args.input):
        return 1
    
    # Override tempo if specified
    if args.tempo:
        converter.tempo_bpm = args.tempo
        print(f"🎵 Tempo overridden to: {args.tempo} BPM")
    
    # Generate C header
    if not converter.generate_c_header(args.output):
        return 1
    
    print("\n✅ Conversion completed successfully!")
    print(f"📄 Output: {args.output}")
    print(f"🎼 Parts generated: {len(converter.parts)}")
    print(f"⏱️  Duration: {converter.total_duration:.2f} seconds")
    
    # Usage instructions
    print("\n📝 Usage Instructions:")
    print("1. Copy the generated .h file to your conductor/main/ directory")
    print("2. Include it in your midi_songs.h file")
    print("3. Add the song to the all_songs[] array")
    print("4. Build and flash your conductor!")
    
    return 0

if __name__ == "__main__":
    sys.exit(main())