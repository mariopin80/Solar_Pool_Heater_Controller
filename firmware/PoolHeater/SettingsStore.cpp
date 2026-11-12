#include "SettingsStore.h"

#include <EEPROM.h>
#include <avr/eeprom.h>
#include <math.h>
#include <util/crc16.h>

namespace {
constexpr int FirstSlot = 80; // The archived layout uses addresses 0–67.
constexpr int SlotSize = 32;
constexpr uint8_t Format = 1;
constexpr uint8_t Committed = 0xA5;
constexpr uint8_t PayloadSize = 3 + ParameterCount * 2 + PumpCount * 6;
constexpr int LegacyTemperatureAddresses[] = {0, 4, 8, 12, 16, 60, 64};

int slotAddress(uint8_t slot) {
  return FirstSlot + slot * SlotSize;
}

uint16_t read16(const uint8_t *&cursor) {
  const uint16_t value = cursor[0] | (static_cast<uint16_t>(cursor[1]) << 8);
  cursor += 2;
  return value;
}

void write16(uint8_t *&cursor, uint16_t value) {
  *cursor++ = value & 0xFF;
  *cursor++ = value >> 8;
}

uint16_t checksum(const uint8_t *bytes) {
  uint16_t crc = 0xFFFF;
  for (uint8_t i = 0; i < PayloadSize; ++i) crc = _crc16_update(crc, bytes[i]);
  return crc;
}

bool decode(const uint8_t *bytes, Settings &settings) {
  const uint8_t *storedChecksum = bytes + PayloadSize;
  if (bytes[0] != Format || read16(storedChecksum) != checksum(bytes)) return false;
  const uint8_t *cursor = bytes + 2;
  for (int16_t &value : settings.temp) value = static_cast<int16_t>(read16(cursor));
  if (!validTemperatures(settings)) return false;
  for (uint8_t i = 0; i < PumpCount; ++i) {
    Schedule &schedule = settings.schedule[i];
    schedule.day = *cursor++;
    schedule.start = read16(cursor);
    schedule.end = read16(cursor);
    const uint8_t mode = *cursor++;
    if (!validSchedule(schedule) || mode > Off) return false;
    settings.mode[i] = static_cast<Mode>(mode);
  }
  if (*cursor > 1) return false;
  settings.bluetooth = *cursor;
  return true;
}

void encode(uint8_t *bytes, uint8_t generation, const Settings &settings) {
  uint8_t *cursor = bytes;
  *cursor++ = Format;
  *cursor++ = generation;
  for (int16_t value : settings.temp) write16(cursor, value);
  for (uint8_t i = 0; i < PumpCount; ++i) {
    const Schedule &schedule = settings.schedule[i];
    *cursor++ = schedule.day;
    write16(cursor, schedule.start);
    write16(cursor, schedule.end);
    *cursor++ = settings.mode[i];
  }
  *cursor++ = settings.bluetooth;
  write16(cursor, checksum(bytes));
}

void setDefaults(Settings &settings) {
  settings = Settings{};
  for (uint8_t i = 0; i < ParameterCount; ++i) {
    settings.temp[i] = limits(static_cast<Parameter>(i)).initial;
  }
  for (Mode &mode : settings.mode) mode = Off;
}

void loadLegacy(Settings &settings) {
  for (uint8_t i = 0; i < ParameterCount; ++i) {
    float value;
    EEPROM.get(LegacyTemperatureAddresses[i], value);
    const Limits range = limits(static_cast<Parameter>(i));
    // The original menu used float increments and can overshoot the limit slightly.
    const float tenths = value * 10;
    if (isfinite(tenths) && tenths >= range.min - 1.1f && tenths <= range.max + 1.1f) {
      const int16_t rounded = lroundf(tenths);
      settings.temp[i] = rounded < range.min ? range.min : (rounded > range.max ? range.max : rounded);
    }
  }
  if (!validTemperatures(settings)) {
    settings.temp[DeltaOn] = limits(DeltaOn).initial;
    settings.temp[DeltaOff] = limits(DeltaOff).initial;
  }
  for (uint8_t i = 0; i < PumpCount; ++i) {
    const uint8_t offset = i == Solar ? 4 : 0;
    const uint8_t day = EEPROM.read(20 + offset);
    const uint8_t startHour = EEPROM.read(30 + offset);
    const uint8_t startMinute = EEPROM.read(40 + offset);
    const uint8_t endHour = EEPROM.read(32 + offset);
    const uint8_t endMinute = EEPROM.read(42 + offset);
    settings.schedule[i] = {0, 0, 0};
    if (day <= 9 && startHour < 24 && endHour < 24 && startMinute < 60 && endMinute < 60) {
      settings.schedule[i] = {day, static_cast<uint16_t>(startHour * 60U + startMinute),
                             static_cast<uint16_t>(endHour * 60U + endMinute)};
    }
    // Old firmware treated a reversed interval as empty.
    if (settings.schedule[i].start > settings.schedule[i].end) {
      settings.schedule[i].end = settings.schedule[i].start;
    }
    const uint8_t mode = EEPROM.read(i == Solar ? 50 : 52);
    settings.mode[i] = mode <= Off ? static_cast<Mode>(mode) : Off;
  }
}
}

void SettingsStore::begin(Settings &settings) {
  static_assert(RecordSize == PayloadSize + 2, "EEPROM record length");
  static_assert(RecordSize + 1 <= SlotSize, "EEPROM slot length");
  bool found = false;
  bool hadRecord = false;
  Settings candidate;
  for (uint8_t slot = 0; slot < 2; ++slot) {
    const int base = slotAddress(slot);
    if (EEPROM.read(base) != Committed) continue;
    hadRecord = true;
    for (uint8_t i = 0; i < RecordSize; ++i) bytes_[i] = EEPROM.read(base + 1 + i);
    if (!decode(bytes_, candidate)) continue;
    const uint8_t advance = bytes_[1] - generation_;
    if (!found || (advance > 0 && advance < 128)) {
      settings = candidate;
      generation_ = bytes_[1];
      activeSlot_ = slot;
      found = true;
    }
  }
  if (!found) {
    setDefaults(settings);
    if (!hadRecord) loadLegacy(settings);
    requestSave();
  }
}

void SettingsStore::tick(const Settings &settings) {
  if (!eeprom_is_ready()) return;
  if (!writing_) {
    if (!pending_) return;
    encode(bytes_, generation_ + 1, settings);
    pending_ = false;
    writing_ = true;
    step_ = 0;
  }
  const uint8_t nextSlot = 1 - activeSlot_;
  const int base = slotAddress(nextSlot);
  // The previous slot is still valid throughout the write. Commit the new slot last.
  if (step_ == 0) EEPROM.update(base, 0);
  else if (step_ <= RecordSize) EEPROM.update(base + step_, bytes_[step_ - 1]);
  else if (step_ == RecordSize + 1) EEPROM.update(base, Committed);
  else {
    activeSlot_ = nextSlot;
    generation_ = bytes_[1];
    writing_ = false;
    return;
  }
  ++step_;
}
