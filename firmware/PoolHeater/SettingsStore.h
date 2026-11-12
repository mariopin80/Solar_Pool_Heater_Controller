#pragma once

#include "Control.h"

class SettingsStore {
 public:
  void begin(Settings &settings);
  void requestSave() { pending_ = true; }
  void tick(const Settings &settings);
  bool saving() const { return pending_ || writing_; }

 private:
  static constexpr uint8_t RecordSize = 31;
  uint8_t bytes_[RecordSize];
  uint8_t activeSlot_ = 1;
  uint8_t generation_ = 0;
  uint8_t step_ = 0;
  bool writing_ = false;
  bool pending_ = false;
};
