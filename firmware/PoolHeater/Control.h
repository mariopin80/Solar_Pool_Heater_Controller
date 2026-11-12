#pragma once

#include <stdint.h>

enum Pump : uint8_t { Solar, Filter, PumpCount };
enum Mode : uint8_t { Auto, On, Off };
enum Parameter : uint8_t {
  Target, DeltaOn, DeltaOff, PoolOffset, CollectorOffset, Freeze, Hot, ParameterCount
};

struct Limits {
  int16_t min;
  int16_t max;
  int16_t initial;
};

struct Schedule {
  uint8_t day; // 0 every day, 1 Sunday through 7 Saturday, 8 weekends, 9 weekdays
  uint16_t start;
  uint16_t end;
};

struct Settings {
  int16_t temp[ParameterCount]; // tenths of a degree Celsius
  Schedule schedule[PumpCount];
  Mode mode[PumpCount];
  bool bluetooth;
};

struct DateTime {
  uint8_t year; // 0 through 99, relative to 2000
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
};

enum SensorStatus : uint8_t { SensorOk, SensorWait, SensorShort, SensorOpen, SensorRange };

struct Temperature {
  int16_t tenths;
  SensorStatus status;
};

enum Reason : uint8_t {
  Idle, ManualOn, ManualOff, Heating, Scheduled, AntiFreeze, HotCollector, SensorFault, ClockFault
};

struct Output {
  bool on;
  Reason reason;
};

struct Status {
  DateTime time;
  bool clockOk;
  Temperature pool;
  Temperature collector;
  Output output[PumpCount];
};

class PumpControl {
 public:
  void update(const Settings &settings, Status &status);

 private:
  bool heatDemand_ = false;
  bool freezeDemand_ = false;
  bool hotDemand_ = false;
};

Limits limits(Parameter parameter);
bool validTemperatures(const Settings &settings);
bool validSchedule(const Schedule &schedule);
uint8_t daysInMonth(uint8_t year, uint8_t month);
bool validDateTime(const DateTime &time);
uint8_t dayOfWeek(const DateTime &time); // 1 Sunday through 7 Saturday, valid dates only
bool scheduleActive(const Schedule &schedule, uint8_t weekday, uint16_t minute);
