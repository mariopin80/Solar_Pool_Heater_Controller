#include "Inputs.h"

#include <Arduino.h>
#include <Wire.h>
#include <math.h>

#include "Board.h"

namespace {
constexpr uint8_t RtcAddress = 0x68;
constexpr uint16_t SampleMs = 250;
constexpr uint16_t ClockMs = 500;
constexpr uint16_t WireTimeoutUs = 12000;
constexpr uint8_t MaxMissedClockReads = 2;
constexpr uint8_t Samples = 16;
constexpr uint8_t RecoverSamples = 3;
constexpr float Beta = 3600.0f;
constexpr float KelvinAt25 = 298.15f;

Temperature measure(uint8_t pin, int16_t offset) {
  // Discard the first conversion after changing ADC channels.
  analogRead(pin);
  uint16_t sum = 0;
  for (uint8_t i = 0; i < Samples; ++i) sum += analogRead(pin);
  if (sum <= 2U * Samples) return {0, SensorShort};
  if (sum >= 1021U * Samples) return {0, SensorOpen};
  // Both the NTC at 25 C and the pull-up are 10 kΩ, so the ratio needs no Vcc term.
  const float ratio = static_cast<float>(sum) / (1023U * Samples - sum);
  const float celsius = 1.0f / (1.0f / KelvinAt25 + logf(ratio) / Beta) - 273.15f;
  if (!(celsius >= -40.0f && celsius <= 125.0f)) return {0, SensorRange};
  return {static_cast<int16_t>(lroundf(celsius * 10) + offset), SensorOk};
}

uint8_t fromBcd(uint8_t value) {
  const uint8_t low = value & 0x0F;
  const uint8_t high = value >> 4;
  return low <= 9 && high <= 9 ? high * 10 + low : 0xFF;
}

uint8_t toBcd(uint8_t value) {
  return ((value / 10) << 4) | (value % 10);
}

void updateTemperature(Temperature measured, Temperature &reading, uint8_t &validSamples) {
  if (measured.status != SensorOk) {
    validSamples = 0;
    reading = measured;
    return;
  }
  if (validSamples < RecoverSamples) ++validSamples;
  if (validSamples == RecoverSamples) reading = measured;
}

enum class ClockRead : uint8_t { Ok, BusError, Invalid };

ClockRead readClock(DateTime &time) {
  Wire.beginTransmission(RtcAddress);
  Wire.write(static_cast<uint8_t>(0));
  if (Wire.endTransmission(false) != 0) return ClockRead::BusError;
  const uint8_t length = 7;
  if (Wire.requestFrom(RtcAddress, length) != length) return ClockRead::BusError;
  const uint8_t seconds = Wire.read();
  const uint8_t minutes = Wire.read();
  const uint8_t hours = Wire.read();
  Wire.read(); // Weekday is derived from the calendar.
  const uint8_t day = Wire.read();
  const uint8_t month = Wire.read();
  const uint8_t year = Wire.read();
  if ((seconds & 0x80) || (hours & 0x80)) return ClockRead::Invalid;
  uint8_t hour = fromBcd(hours);
  if (hours & 0x40) {
    const uint8_t twelveHour = fromBcd(hours & 0x1F);
    if (twelveHour < 1 || twelveHour > 12) return ClockRead::Invalid;
    hour = twelveHour % 12 + ((hours & 0x20) ? 12 : 0);
  }
  const DateTime candidate = {fromBcd(year), fromBcd(month), fromBcd(day),
                              hour, fromBcd(minutes), fromBcd(seconds)};
  if (!validDateTime(candidate)) return ClockRead::Invalid;
  time = candidate;
  return ClockRead::Ok;
}
}

void Inputs::begin() {
  Wire.begin();
  // Allow the I2C transaction to progress during SoftwareSerial receive interrupts.
  Wire.setWireTimeout(WireTimeoutUs, true);
  lastSample_ = millis() - SampleMs;
  lastClock_ = millis() - ClockMs;
}

void Inputs::tick(uint32_t now, const Settings &settings, Status &status) {
  if (now - lastSample_ >= SampleMs) {
    lastSample_ = now;
    updateTemperature(measure(Pins::PoolNtc, settings.temp[PoolOffset]), status.pool, validSamples_[0]);
    updateTemperature(measure(Pins::CollectorNtc, settings.temp[CollectorOffset]),
                      status.collector, validSamples_[1]);
  }
  if (now - lastClock_ >= ClockMs) {
    lastClock_ = now;
    const ClockRead reading = readClock(status.time);
    if (reading == ClockRead::Ok) {
      missedClockReads_ = 0;
      status.clockOk = true;
    } else if (reading == ClockRead::Invalid || ++missedClockReads_ >= MaxMissedClockReads) {
      missedClockReads_ = MaxMissedClockReads;
      status.clockOk = false;
    }
  }
}

bool Inputs::setClock(const DateTime &time, Status &status) {
  if (!validDateTime(time)) return false;
  Wire.beginTransmission(RtcAddress);
  Wire.write(static_cast<uint8_t>(0));
  Wire.write(toBcd(time.second)); // Clears the clock-halt bit.
  Wire.write(toBcd(time.minute));
  Wire.write(toBcd(time.hour));   // Selects 24-hour format.
  Wire.write(dayOfWeek(time));
  Wire.write(toBcd(time.day));
  Wire.write(toBcd(time.month));
  Wire.write(toBcd(time.year));
  if (Wire.endTransmission() != 0) {
    status.clockOk = false;
    return false;
  }
  status.clockOk = readClock(status.time) == ClockRead::Ok;
  if (status.clockOk) missedClockReads_ = 0;
  const DateTime &readback = status.time;
  // Writing the seconds register resets the divider, so this read is in the same second.
  return status.clockOk && readback.year == time.year && readback.month == time.month &&
         readback.day == time.day && readback.hour == time.hour &&
         readback.minute == time.minute && readback.second == time.second;
}
