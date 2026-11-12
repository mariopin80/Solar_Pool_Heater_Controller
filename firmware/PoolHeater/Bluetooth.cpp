#include "Bluetooth.h"

#if POOLHEATER_ENABLE_BLUETOOTH
#include <avr/pgmspace.h>
#include <stdlib.h>
#include <string.h>

namespace {
constexpr uint16_t ReceiveTimeoutMs = 500;
constexpr uint8_t BytesPerLoop = 8;
constexpr uint8_t ReplyEnd = 0;

bool parseNumber(const char *word, int16_t minimum, int16_t maximum, int16_t &out) {
  if (!word || !*word) return false;
  const bool negative = *word == '-';
  if (negative) ++word;
  if (!*word) return false;
  long value = 0;
  for (; *word; ++word) {
    if (*word < '0' || *word > '9' || value > 3276) return false;
    value = value * 10 + (*word - '0');
  }
  if (negative) value = -value;
  if (value < minimum || value > maximum) return false;
  out = static_cast<int16_t>(value);
  return true;
}

void writeTwo(char *to, uint8_t value) {
  to[0] = '0' + value / 10;
  to[1] = '0' + value % 10;
}

void updateMode(Settings &settings, SettingsStore &store, Pump pump, Mode mode) {
  if (settings.mode[pump] == mode) return;
  settings.mode[pump] = mode;
  store.requestSave();
}

bool parseDateTime(const char *date, const char *clock, DateTime &time) {
  if (!date || !clock || strlen(date) != 8 || strlen(clock) != 6 ||
      date[0] != '2' || date[1] != '0') return false;
  const char *pairs[] = {date + 2, date + 4, date + 6, clock, clock + 2, clock + 4};
  uint8_t fields[6];
  for (uint8_t i = 0; i < sizeof(fields); ++i) {
    const char *pair = pairs[i];
    if (pair[0] < '0' || pair[0] > '9' || pair[1] < '0' || pair[1] > '9') return false;
    fields[i] = (pair[0] - '0') * 10 + pair[1] - '0';
  }
  time = {fields[0], fields[1], fields[2], fields[3], fields[4], fields[5]};
  return validDateTime(time);
}
}

void Bluetooth::tick(uint32_t now, Settings &settings, Status &status, Inputs &inputs, SettingsStore &store) {
  if (settings.bluetooth != enabled_) {
    enabled_ = settings.bluetooth;
    if (enabled_) serial_.begin(9600);
    else serial_.end();
    framed_ = overflow_ = trailingCr_ = framedSession_ = false;
    length_ = transmit_ = 0;
    response_[0] = ReplyEnd;
  }
  if (!enabled_) return;

  // SoftwareSerial sends synchronously. Limit transmission to one byte per loop.
  if (response_[transmit_] != ReplyEnd) {
    serial_.write(static_cast<uint8_t>(response_[transmit_++]));
    if (response_[transmit_] == ReplyEnd) response_[transmit_ = 0] = ReplyEnd;
    return;
  }

  if (serial_.overflow()) {
    // Re-entering listen clears the AVR SoftwareSerial receive buffer.
    serial_.stopListening();
    serial_.listen();
    framed_ = false;
    framedSession_ = true;
    reply(0, F("ERR OVERRUN"));
    return;
  }

  if (framed_ && now - lastByte_ >= ReceiveTimeoutMs) {
    // Discard the rest of a truncated frame, including any legacy digits.
    framed_ = false;
    framedSession_ = true;
    reply(0, F("ERR TIMEOUT"));
    return;
  }
  for (uint8_t count = 0; count < BytesPerLoop && serial_.available(); ++count) {
    accept(serial_.read(), now, settings, status, inputs, store);
    if (response_[0] != ReplyEnd) break;
  }
}

void Bluetooth::accept(char byte, uint32_t now, Settings &settings, Status &status, Inputs &inputs,
                       SettingsStore &store) {
  if (byte == '@') {
    framed_ = framedSession_ = true;
    overflow_ = trailingCr_ = false;
    length_ = 0;
    lastByte_ = now;
    return;
  }
  if (!framed_) {
#if POOLHEATER_ENABLE_LEGACY_BT
    if (!framedSession_) legacy(byte, settings, status, store);
#endif
    return;
  }
  lastByte_ = now;
  if (byte == '\n') {
    framed_ = false;
    request_[length_] = '\0';
    if (overflow_) reply(0, F("ERR FRAME"));
    else dispatch(settings, status, inputs, store);
  } else if (byte == '\r' && !trailingCr_) {
    trailingCr_ = true;
  } else if (trailingCr_ || byte < ' ' || byte > '~' || length_ == sizeof(request_) - 1) {
    overflow_ = true;
  } else if (!overflow_) {
    request_[length_++] = byte;
  }
}

void Bluetooth::dispatch(Settings &settings, Status &status, Inputs &inputs, SettingsStore &store) {
  char *state;
  int16_t id;
  if (!parseNumber(strtok_r(request_, " ", &state), 1, 32767, id)) {
    reply(0, F("ERR ID"));
    return;
  }

  const char *command = strtok_r(nullptr, " ", &state);
  const char *first = strtok_r(nullptr, " ", &state);
  const char *second = strtok_r(nullptr, " ", &state);
  const char *third = strtok_r(nullptr, " ", &state);
  const char *fourth = strtok_r(nullptr, " ", &state);
  const char *extra = strtok_r(nullptr, " ", &state);

  if (!command) {
    reply(id, F("ERR COMMAND"));
    return;
  }
  if (!first && !strcmp_P(command, PSTR("INFO"))) {
    reply(id, F("OK INFO 1 " POOLHEATER_VERSION " MPS01-1.1"));
    return;
  }
  if (!first && !strcmp_P(command, PSTR("STATUS"))) {
    statusReply(id, settings, status, store.saving());
    return;
  }
  if (!first && !strcmp_P(command, PSTR("GET"))) {
    settingsReply(id, settings);
    return;
  }

  int16_t pump, value;
  if (!strcmp_P(command, PSTR("MODE"))) {
    if (third || !parseNumber(first, Solar, Filter, pump) || !parseNumber(second, Auto, Off, value)) {
      reply(id, F("ERR ARG"));
      return;
    }
    updateMode(settings, store, static_cast<Pump>(pump), static_cast<Mode>(value));
  } else if (!strcmp_P(command, PSTR("SET"))) {
    int16_t parameter;
    if (third || !parseNumber(first, Target, Hot, parameter) || !parseNumber(second, -50, 900, value)) {
      reply(id, F("ERR ARG"));
      return;
    }
    Settings candidate = settings;
    candidate.temp[parameter] = value;
    if (!validTemperatures(candidate)) {
      reply(id, F("ERR RANGE"));
      return;
    }
    if (settings.temp[parameter] != value) {
      settings.temp[parameter] = value;
      store.requestSave();
    }
  } else if (!strcmp_P(command, PSTR("SCHED"))) {
    int16_t day, start, end;
    if (extra || !parseNumber(first, Solar, Filter, pump) || !parseNumber(second, 0, 9, day) ||
        !parseNumber(third, 0, 1439, start) || !parseNumber(fourth, 0, 1439, end)) {
      reply(id, F("ERR ARG"));
      return;
    }
    Schedule &schedule = settings.schedule[pump];
    const Schedule requested = {static_cast<uint8_t>(day), static_cast<uint16_t>(start),
                                static_cast<uint16_t>(end)};
    if (schedule.day != requested.day || schedule.start != requested.start || schedule.end != requested.end) {
      schedule = requested;
      store.requestSave();
    }
  } else if (!strcmp_P(command, PSTR("CLOCK"))) {
    DateTime time;
    if (third || !parseDateTime(first, second, time)) {
      reply(id, F("ERR ARG"));
      return;
    }
    if (!inputs.setClock(time, status)) {
      reply(id, F("ERR RTC"));
      return;
    }
  } else {
    reply(id, F("ERR COMMAND"));
    return;
  }
  reply(id, store.saving() ? F("OK PENDING") : F("OK"));
}

void Bluetooth::reply(uint16_t id, const __FlashStringHelper *text) {
  transmit_ = 0;
  response_[0] = '@';
  utoa(id, response_ + 1, 10);
  field(text);
}

char *Bluetooth::startField(uint8_t length) {
  char *end = response_ + strlen(response_);
  if (end[-1] == '\n') --end;
  if (static_cast<size_t>(end - response_) + length + 3 > sizeof(response_)) return nullptr;
  *end++ = ' ';
  end[length] = '\n';
  end[length + 1] = '\0';
  return end;
}

void Bluetooth::field(int16_t value) {
  char digits[7];
  itoa(value, digits, 10);
  const uint8_t length = strlen(digits);
  if (char *target = startField(length)) memcpy(target, digits, length);
}

void Bluetooth::field(const __FlashStringHelper *value) {
  PGM_P text = reinterpret_cast<PGM_P>(value);
  const uint8_t length = strlen_P(text);
  if (char *target = startField(length)) memcpy_P(target, text, length);
}

void Bluetooth::temperature(const Temperature &reading) {
  field(reading.status);
  if (reading.status == SensorOk) field(reading.tenths);
  else field(F("-"));
}

void Bluetooth::clock(const Status &status) {
  if (!status.clockOk) {
    field(F("-"));
    field(F("-"));
    return;
  }
  char *end = startField(15); // YYYYMMDD HHMMSS
  if (!end) return;
  *end++ = '2';
  *end++ = '0';
  writeTwo(end, status.time.year); end += 2;
  writeTwo(end, status.time.month); end += 2;
  writeTwo(end, status.time.day); end += 2;
  *end++ = ' ';
  writeTwo(end, status.time.hour); end += 2;
  writeTwo(end, status.time.minute); end += 2;
  writeTwo(end, status.time.second);
}

void Bluetooth::statusReply(uint16_t id, const Settings &settings, const Status &status, bool saving) {
  reply(id, F("OK STATUS"));
  temperature(status.pool);
  temperature(status.collector);
  for (uint8_t pump = 0; pump < PumpCount; ++pump) {
    field(settings.mode[pump]);
    field(status.output[pump].on);
    field(status.output[pump].reason);
  }
  field(status.clockOk);
  clock(status);
  field(saving);
}

void Bluetooth::settingsReply(uint16_t id, const Settings &settings) {
  reply(id, F("OK GET"));
  for (int16_t value : settings.temp) field(value);
  for (const Schedule &schedule : settings.schedule) {
    field(schedule.day);
    field(schedule.start);
    field(schedule.end);
  }
  field(settings.bluetooth);
}

#if POOLHEATER_ENABLE_LEGACY_BT
void Bluetooth::legacy(char byte, Settings &settings, const Status &status, SettingsStore &store) {
  if (byte >= '1' && byte <= '6') {
    const uint8_t command = byte - '1';
    updateMode(settings, store, command < 3 ? Solar : Filter, static_cast<Mode>(command % 3));
  } else if (byte == '7') {
    transmit_ = 0;
    char *end = response_;
    const Temperature readings[] = {status.pool, status.collector};
    for (uint8_t i = 0; i < 2; ++i) {
      strcpy_P(end, i == 0 ? PSTR("PSC T: ") : PSTR("CLT T: "));
      end += 7;
      if (readings[i].status == SensorOk) {
        dtostrf(readings[i].tenths / 10.0, 0, 1, end);
        end += strlen(end);
        *end++ = static_cast<char>(223);
        *end++ = 'C';
      } else {
        strcpy_P(end, PSTR("ERR"));
        end += 3;
      }
      *end++ = '\r';
      *end++ = '\n';
    }
    *end = '\0';
  }
}
#endif
#endif
