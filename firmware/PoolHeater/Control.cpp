#include "Control.h"

Limits limits(Parameter parameter) {
  switch (parameter) {
    case Target:          return {100, 400, 250};
    case DeltaOn:         return {20, 250, 120};
    case DeltaOff:        return {20, 250, 50};
    case PoolOffset:
    case CollectorOffset: return {-50, 50, 0};
    case Freeze:          return {0, 70, 40};
    case Hot:             return {500, 900, 650};
    default:              return {0, 0, 0};
  }
}

bool validTemperatures(const Settings &settings) {
  for (uint8_t i = 0; i < ParameterCount; ++i) {
    const Limits range = limits(static_cast<Parameter>(i));
    if (settings.temp[i] < range.min || settings.temp[i] > range.max) return false;
  }
  return settings.temp[DeltaOff] < settings.temp[DeltaOn];
}

bool validSchedule(const Schedule &schedule) {
  return schedule.day <= 9 && schedule.start < 1440 && schedule.end < 1440;
}

uint8_t daysInMonth(uint8_t year, uint8_t month) {
  switch (month) {
    case 2: return year % 4 == 0 ? 29 : 28;
    case 4: case 6: case 9: case 11: return 30;
    default: return 31;
  }
}

bool validDateTime(const DateTime &time) {
  return time.year <= 99 && time.month >= 1 && time.month <= 12 &&
         time.day >= 1 && time.day <= daysInMonth(time.year, time.month) &&
         time.hour <= 23 && time.minute <= 59 && time.second <= 59;
}

uint8_t dayOfWeek(const DateTime &time) {
  // 2000-01-01 was Saturday. The counter includes the leap day in year 2000.
  uint16_t days = 365U * time.year + (time.year + 3U) / 4U + time.day - 1U;
  for (uint8_t month = 1; month < time.month; ++month) {
    days += daysInMonth(time.year, month);
  }
  return (days + 6U) % 7U + 1U;
}

static bool matchesDay(uint8_t selection, uint8_t day) {
  const bool weekend = day == 1 || day == 7;
  return selection == 0 || selection == day ||
         (selection == 8 && weekend) || (selection == 9 && !weekend);
}

bool scheduleActive(const Schedule &schedule, uint8_t weekday, uint16_t minute) {
  if (schedule.start == schedule.end) return false;
  if (schedule.start < schedule.end) {
    return matchesDay(schedule.day, weekday) && minute >= schedule.start && minute < schedule.end;
  }
  // An overnight interval belongs to the day on which it started.
  if (minute >= schedule.start) return matchesDay(schedule.day, weekday);
  const uint8_t previousDay = weekday == 1 ? 7 : weekday - 1;
  return minute < schedule.end && matchesDay(schedule.day, previousDay);
}

void PumpControl::update(const Settings &settings, Status &status) {
  const uint16_t minute = status.time.hour * 60U + status.time.minute;
  const uint8_t weekday = status.clockOk ? dayOfWeek(status.time) : 0;
  const Mode filterMode = settings.mode[Filter];
  const bool filterScheduled = status.clockOk && scheduleActive(settings.schedule[Filter], weekday, minute);
  if (filterMode != Auto) {
    status.output[Filter] = {filterMode == On, filterMode == On ? ManualOn : ManualOff};
  } else if (!status.clockOk) {
    status.output[Filter] = {false, ClockFault};
  } else {
    status.output[Filter] = {filterScheduled, filterScheduled ? Scheduled : Idle};
  }

  const Mode solarMode = settings.mode[Solar];
  const bool sensorsOk = status.pool.status == SensorOk && status.collector.status == SensorOk;
  if (!sensorsOk || solarMode != Auto) {
    heatDemand_ = freezeDemand_ = hotDemand_ = false;
    if (!sensorsOk) status.output[Solar] = {false, SensorFault};
    else status.output[Solar] = {solarMode == On, solarMode == On ? ManualOn : ManualOff};
    return;
  }

  const int16_t pool = status.pool.tenths;
  const int16_t collector = status.collector.tenths;
  const int16_t delta = collector - pool;
  heatDemand_ = heatDemand_
      ? pool < settings.temp[Target] && delta > settings.temp[DeltaOff]
      : pool <= settings.temp[Target] - 5 && delta >= settings.temp[DeltaOn];
  freezeDemand_ = freezeDemand_ ? collector < settings.temp[Freeze] + 20
                                : collector <= settings.temp[Freeze];
  hotDemand_ = hotDemand_ ? collector > settings.temp[Hot] - 30
                          : collector >= settings.temp[Hot];

  if (freezeDemand_) status.output[Solar] = {true, AntiFreeze};
  else if (hotDemand_) status.output[Solar] = {true, HotCollector};
  else if (heatDemand_) status.output[Solar] = {true, Heating};
  else if (status.clockOk && scheduleActive(settings.schedule[Solar], weekday, minute)) {
    status.output[Solar] = {true, Scheduled};
  } else {
    status.output[Solar] = {false, Idle};
  }
}
