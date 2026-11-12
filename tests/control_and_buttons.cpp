#include <assert.h>
#include <stdint.h>

#include "Buttons.h"
#include "Control.h"

static Settings configured() {
  Settings settings{};
  for (uint8_t i = 0; i < ParameterCount; ++i) {
    settings.temp[i] = limits(static_cast<Parameter>(i)).initial;
  }
  return settings;
}

static void testButtons() {
  Button enter(KeyEvent::Enter);
  enter.begin(false, 0);
  assert(enter.update(true, 1, false) == KeyEvent::None);
  assert(enter.update(false, 7, false) == KeyEvent::None);
  assert(enter.update(true, 11, false) == KeyEvent::None);
  assert(enter.update(true, 35, false) == KeyEvent::None);
  assert(enter.update(false, 75, false) == KeyEvent::None);
  assert(enter.update(true, 79, false) == KeyEvent::None);
  assert(enter.update(false, 83, false) == KeyEvent::None);
  assert(enter.update(false, 107, false) == KeyEvent::Enter);
  assert(enter.update(false, 108, false) == KeyEvent::None);

  enter.update(true, 200, false);
  enter.update(true, 224, false);
  assert(enter.update(true, 923, false) == KeyEvent::None);
  assert(enter.update(true, 924, false) == KeyEvent::Back);
  assert(enter.update(true, 1600, false) == KeyEvent::None);
  enter.update(false, 1601, false);
  assert(enter.update(false, 1625, false) == KeyEvent::None);

  Button plus(KeyEvent::Plus);
  plus.begin(true, 0);
  assert(plus.update(true, 2000, true) == KeyEvent::None);
  plus.update(false, 2100, true);
  plus.update(false, 2124, true);
  plus.update(true, 2200, false);
  assert(plus.update(true, 2224, false) == KeyEvent::Plus);
  assert(plus.update(true, 3000, true) == KeyEvent::None);
  plus.update(false, 3100, true);
  plus.update(false, 3124, true);
  plus.update(true, 3200, true);
  assert(plus.update(true, 3224, true) == KeyEvent::Plus);
  assert(plus.update(true, 3663, true) == KeyEvent::None);
  assert(plus.update(true, 3664, true) == KeyEvent::Plus);
  assert(plus.update(true, 3773, true) == KeyEvent::None);
  assert(plus.update(true, 3774, true) == KeyEvent::Plus);
  plus.cancelRepeat();
  assert(plus.update(true, 5000, true) == KeyEvent::None);

  Button minus(KeyEvent::Minus);
  minus.begin(false, UINT32_MAX - 20);
  minus.update(true, UINT32_MAX - 10, false);
  assert(minus.update(true, 12, false) == KeyEvent::None);
  assert(minus.update(true, 13, false) == KeyEvent::Minus);
}

static void testCalendarAndSchedules() {
  assert(dayOfWeek({0, 1, 1, 0, 0, 0}) == 7);
  assert(dayOfWeek({26, 11, 12, 0, 0, 0}) == 5);
  assert(dayOfWeek({24, 2, 29, 0, 0, 0}) == 5);
  assert(!validDateTime({25, 2, 29, 0, 0, 0}));
  assert(validDateTime({24, 2, 29, 23, 59, 59}));
  assert(!validDateTime({24, 4, 31, 0, 0, 0}));

  const Schedule friday = {6, 22 * 60, 2 * 60};
  assert(!scheduleActive(friday, 6, 22 * 60 - 1));
  assert(scheduleActive(friday, 6, 22 * 60));
  assert(scheduleActive(friday, 7, 0));
  assert(scheduleActive(friday, 7, 119));
  assert(!scheduleActive(friday, 7, 120));
  assert(!scheduleActive(friday, 1, 90));
  assert(scheduleActive({8, 1320, 120}, 2, 90)); // Sunday into Monday.
  assert(!scheduleActive({8, 1320, 120}, 3, 90));
  assert(scheduleActive({9, 1320, 120}, 7, 90)); // Friday into Saturday.
  assert(scheduleActive({7, 1320, 120}, 1, 90)); // Saturday into Sunday.
  assert(!scheduleActive({0, 120, 120}, 1, 120));
}

static void testControl() {
  Settings settings = configured();
  Status status{};
  status.clockOk = true;
  status.time = {26, 11, 13, 23, 0, 0}; // Friday.
  status.pool = {230, SensorOk};
  status.collector = {360, SensorOk};
  PumpControl control;
  settings.schedule[Filter] = {6, 22 * 60, 2 * 60};
  control.update(settings, status);
  assert(status.output[Solar].reason == Heating && status.output[Solar].on);
  assert(status.output[Filter].reason == Scheduled && status.output[Filter].on);

  status.collector.tenths = 300;
  status.time = {26, 11, 14, 1, 59, 59};
  control.update(settings, status);
  assert(status.output[Solar].on && status.output[Filter].on);

  status.time = {26, 11, 14, 2, 0, 0};
  status.collector.tenths = 280;
  control.update(settings, status);
  assert(!status.output[Solar].on && !status.output[Filter].on);

  status.collector.tenths = 39;
  control.update(settings, status);
  assert(status.output[Solar].reason == AntiFreeze);
  status.collector.tenths = 59;
  control.update(settings, status);
  assert(status.output[Solar].reason == AntiFreeze);
  status.collector.tenths = 60;
  control.update(settings, status);
  assert(!status.output[Solar].on);

  status.pool.tenths = 270;
  status.collector.tenths = 651;
  control.update(settings, status);
  assert(status.output[Solar].reason == HotCollector && status.output[Solar].on);
  status.collector.tenths = 620;
  control.update(settings, status);
  assert(!status.output[Solar].on);

  settings.mode[Solar] = On;
  settings.mode[Filter] = On;
  status.collector.status = SensorOpen;
  status.clockOk = false;
  control.update(settings, status);
  assert(status.output[Solar].reason == SensorFault && !status.output[Solar].on);
  assert(status.output[Filter].reason == ManualOn && status.output[Filter].on);

  settings.mode[Filter] = Auto;
  control.update(settings, status);
  assert(status.output[Filter].reason == ClockFault && !status.output[Filter].on);

  status.collector = {420, SensorOk};
  status.pool = {220, SensorOk};
  settings.mode[Solar] = Auto;
  control.update(settings, status);
  assert(status.output[Solar].reason == Heating && status.output[Solar].on);
  assert(!status.output[Filter].on);

  settings.temp[DeltaOff] = settings.temp[DeltaOn];
  assert(!validTemperatures(settings));
}

int main() {
  testButtons();
  testCalendarAndSchedules();
  testControl();
}
