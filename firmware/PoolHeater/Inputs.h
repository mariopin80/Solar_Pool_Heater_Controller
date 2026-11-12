#pragma once

#include "Control.h"

class Inputs {
 public:
  void begin();
  void tick(uint32_t now, const Settings &settings, Status &status);
  bool setClock(const DateTime &time, Status &status);

 private:
  uint32_t lastSample_ = 0;
  uint32_t lastClock_ = 0;
  uint8_t missedClockReads_ = 0;
  uint8_t validSamples_[PumpCount]{};
};
