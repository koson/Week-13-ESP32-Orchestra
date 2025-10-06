# ESP32 Orchestra MIDI Parser Tools
## เครื่องมือแปลงไฟล์ MIDI เป็น C Header Files

![MIDI Parser](https://via.placeholder.com/800x200?text=MIDI+to+ESP32+Orchestra+Converter)

เครื่องมือนี้จะแปลงไฟล์ MIDI (.mid) ให้เป็น C header files ที่ ESP32 Orchestra สามารถเล่นได้

---

## 🎯 คุณสมบัติ

- ✅ **อ่านไฟล์ MIDI** รูปแบบมาตรฐาน (.mid, .midi)
- ✅ **แบ่ง Parts อัตโนมัติ** ตาม pitch range และ channel
- ✅ **สร้าง C Header** พร้อม note arrays และ timing
- ✅ **Batch Conversion** แปลงหลายไฟล์พร้อมกัน
- ✅ **Tempo Detection** อ่าน BPM จากไฟล์ MIDI
- ✅ **Multi-track Support** รวม tracks หลายตัว

---

## 🛠️ การติดตั้ง

### ขั้นตอนที่ 1: ติดตั้ง Python Dependencies
```bash
# ติดตั้ง MIDI library
pip install mido python-rtmidi

# สำหรับ Windows อาจต้องติดตั้งเพิ่ม
pip install python-rtmidi-win
```

### ขั้นตอนที่ 2: ตรวจสอบการติดตั้ง
```bash
python3 -c "import mido; print('MIDI library OK')"
```

---

## 📁 โครงสร้างไฟล์

```
tools/
├── midi_parser.py          # MIDI parser หลัก
├── convert_midi_batch.sh   # Batch converter (Linux/Mac)
├── convert_midi_batch.bat  # Batch converter (Windows)
└── README.md              # คู่มือนี้

midi_files/                # วางไฟล์ MIDI ที่ต้องการแปลง
├── twinkle_star.mid
├── happy_birthday.mid
└── mary_lamb.mid

conductor/main/generated_songs/  # ผลลัพธ์ที่ได้
├── twinkle_star.h
├── happy_birthday.h
├── mary_lamb.h
└── all_generated_songs.h
```

---

## 🎵 วิธีใช้งาน

### แบบแปลงไฟล์เดียว
```bash
python3 midi_parser.py input.mid output.h [options]

# ตัวอย่าง
python3 midi_parser.py twinkle_star.mid twinkle_star.h --parts 4
```

### แบบ Batch (แปลงหลายไฟล์)
```bash
# Linux/Mac
./convert_midi_batch.sh

# Windows
convert_midi_batch.bat
```

### Parameters
```bash
python3 midi_parser.py [input.mid] [output.h] [options]

Options:
  --parts N      จำนวน parts สูงสุด (default: 4)
  --tempo BPM    กำหนด tempo เอง (override MIDI)
  --help         แสดงความช่วยเหลือ
```

---

## 📋 ขั้นตอนการใช้งาน

### ขั้นตอนที่ 1: เตรียมไฟล์ MIDI
```bash
# สร้างโฟลเดอร์
mkdir -p midi_files

# วางไฟล์ .mid ลงในโฟลเดอร์
cp your_song.mid midi_files/
```

### ขั้นตอนที่ 2: แปลงไฟล์
```bash
# Linux/Mac
chmod +x convert_midi_batch.sh
./convert_midi_batch.sh

# Windows
convert_midi_batch.bat
```

### ขั้นตอนที่ 3: ผลลัพธ์ที่ได้
จะได้ไฟล์ดังนี้:
- `song_name.h` - Header สำหรับแต่ละเพลง
- `all_generated_songs.h` - Header รวมทุกเพลง

### ขั้นตอนที่ 4: นำไปใช้กับ ESP32
```c
// ใน conductor/main/midi_songs.h
#include "generated_songs/all_generated_songs.h"

// เพิ่มเพลงลงใน database
static const orchestra_song_t all_songs[] = {
    // เพลงเิดิม...
    
    // เพลงที่แปลงใหม่
    {
        .song_name = "My MIDI Song",
        .song_id = SONG_MY_MIDI,
        .tempo_bpm = 120,
        .part_count = 4,
        .parts = my_midi_song_parts
    }
};
```

---

## 🎼 วิธีการแบ่ง Parts

### อัตโนมัติตาม Pitch Range
| Part | Range | บทบาท |
|------|-------|--------|
| **Part 0 (Melody)** | C5+ (72+) | ทำนองหลัก |
| **Part 1 (Harmony)** | C4-B4 (60-71) | เสียงประสาน |
| **Part 2 (Bass)** | <C4 (<60) | เสียงเบส |
| **Part 3 (Rhythm)** | Channel 9 | จังหวะ/กลอง |

### ตาม MIDI Channel
- **Channel 1-8**: แบ่งตาม pitch range
- **Channel 9 (Drums)**: ไปที่ Rhythm part
- **Channel 10+**: แบ่งตาม pitch range

---

## 📊 ตัวอย่าง Output

### ไฟล์ Input: `twinkle_star.mid`
```
📁 Loading MIDI file: twinkle_star.mid
🎵 Song: twinkle_star
📊 Type: 1, Tracks: 4, Ticks per beat: 480
🎵 Tempo: 120 BPM
⏱️  Total duration: 24.50 seconds
🎹 Total notes: 156
🎼 Part 0 (Melody): 42 notes
🎼 Part 1 (Harmony): 38 notes
🎼 Part 2 (Bass): 24 notes
🎼 Part 3 (Rhythm): 52 notes
```

### ไฟล์ Output: `twinkle_star.h`
```c
#ifndef MIDI_TWINKLE_STAR_H
#define MIDI_TWINKLE_STAR_H

// Part 0: Melody
static const note_event_t twinkle_star_melody[] = {
    {NOTE_C4, 400, 0},    // Note 60 (C4) - 0ms
    {NOTE_C4, 400, 100},  // Note 60 (C4) - 500ms
    {NOTE_G4, 400, 100},  // Note 67 (G4) - 1000ms
    // ...
    {NOTE_REST, 0, 0}     // End of part
};

// Song definition
static const orchestra_song_t twinkle_star_song = {
    .song_name = "twinkle_star",
    .song_id = SONG_TWINKLE_STAR,
    .tempo_bpm = 120,
    .part_count = 4,
    .parts = twinkle_star_parts
};
```

---

## 🔧 การแก้ไขปัญหา

### ปัญหาที่พบบ่อย

#### 1. Import Error: No module named 'mido'
```bash
# แก้ไข: ติดตั้ง dependencies
pip install mido python-rtmidi
```

#### 2. ไม่มีเสียงออกจาก Musicians
```bash
# ตรวจสอบ: MIDI notes อยู่ในย่านที่ถูกต้องไหม
# ESP32 buzzer เล่นได้ดีที่ 200-2000 Hz
```

#### 3. เพลงเล่นไม่พร้อมกัน
```bash
# ตรวจสอบ: timing synchronization
# ลอง override tempo ด้วย --tempo 120
```

#### 4. บาง Parts ไม่มีเสียง
```bash
# สาเหตุ: MIDI file อาจมี track น้อย
# แก้ไข: ลดจำนวน --parts 2
```

### Debug Commands
```bash
# ดูข้อมูล MIDI file
python3 -c "
import mido
mid = mido.MidiFile('song.mid')
print(f'Type: {mid.type}, Tracks: {len(mid.tracks)}')
for i, track in enumerate(mid.tracks):
    print(f'Track {i}: {track.name}, Messages: {len(track)}')
"

# ตรวจสอบ notes ในแต่ละ track
python3 -c "
import mido
mid = mido.MidiFile('song.mid')
for i, track in enumerate(mid.tracks):
    notes = [msg for msg in track if msg.type in ['note_on', 'note_off']]
    print(f'Track {i}: {len(notes)} note events')
"
```

---

## 🎶 แหล่งไฟล์ MIDI ฟรี

### เว็บไฟล์ MIDI ฟรี
- [MidiWorld](https://www.midiworld.com/) - คลาสสิคและป๊อป
- [FreeMidi.org](https://freemidi.org/) - หลากหลายแนว
- [MuseScore](https://musescore.com/) - sheet music + MIDI
- [IMSLP](https://imslp.org/) - คลาสสิคคุณภาพสูง

### เพลงแนะนำสำหรับทดสอบ
- **ง่าย:** Twinkle Star, Mary Had a Little Lamb
- **ปานกลาง:** Happy Birthday, Ode to Joy
- **ยาก:** Canon in D, Fur Elise
- **Electronic:** เพลง 8-bit, chiptune

---

## 📈 การพัฒนาต่อ

### คุณสมบัติที่จะเพิ่ม
- [ ] **GUI Interface** สำหรับ drag & drop
- [ ] **Real-time Preview** ฟังเพลงก่อนแปลง
- [ ] **Volume Control** ต่อ part
- [ ] **Effects Processing** reverb, chorus
- [ ] **Chord Detection** แยก melody/chord อัตโนมัติ

### การปรับปรุง Algorithm
- [ ] **Smart Part Assignment** ใช้ AI แบ่ง parts
- [ ] **Percussion Mapping** แปลงกลองเป็นเสียงพิเศษ
- [ ] **Dynamic Tempo** เปลี่ยนจังหวะระหว่างเพลง
- [ ] **Key Transposition** เปลี่ยน key อัตโนมัติ

---

## 🤝 การสนับสนุน

### การรายงานปัญหา
1. ลองใช้ไฟล์ MIDI ตัวอื่น
2. ตรวจสอบ console output
3. แนบไฟล์ MIDI ที่มีปัญหา
4. ระบุ OS และ Python version

### การขอคุณสมบัติใหม่
1. อธิบายการใช้งานที่ต้องการ
2. ยกตัวอย่างไฟล์ MIDI
3. แสดงผลลัพธ์ที่คาดหวัง

---

## 📝 License & Credits

**License:** MIT License  
**Author:** ESP32 Orchestra Team  
**Dependencies:** 
- [mido](https://mido.readthedocs.io/) - MIDI library for Python
- [python-rtmidi](https://pypi.org/project/python-rtmidi/) - MIDI I/O

---

*"Turn any MIDI file into an ESP32 Orchestra masterpiece! 🎵"*