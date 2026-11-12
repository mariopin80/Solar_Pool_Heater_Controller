#pragma once

#include "Board.h"

#if POOLHEATER_ENABLE_BLUETOOTH
#include <SoftwareSerial.h>

#include "Control.h"
#include "Inputs.h"
#include "SettingsStore.h"

class Bluetooth {
 public:
  void tick(uint32_t now, Settings &settings, Status &status, Inputs &inputs, SettingsStore &store);

 private:
  void accept(char byte, uint32_t now, Settings &settings, Status &status, Inputs &inputs, SettingsStore &store);
  void dispatch(Settings &settings, Status &status, Inputs &inputs, SettingsStore &store);
#if POOLHEATER_ENABLE_LEGACY_BT
  void legacy(char byte, Settings &settings, const Status &status, SettingsStore &store);
#endif

  void reply(uint16_t id, const __FlashStringHelper *text);
  char *startField(uint8_t length);
  void field(int16_t value);
  void field(const __FlashStringHelper *value);
  void temperature(const Temperature &reading);
  void clock(const Status &status);
  void statusReply(uint16_t id, const Settings &settings, const Status &status, bool saving);
  void settingsReply(uint16_t id, const Settings &settings);

  SoftwareSerial serial_{Pins::BluetoothRx, Pins::BluetoothTx};
  char request_[48];
  uint8_t length_ = 0;
  uint8_t transmit_ = 0;
  uint32_t lastByte_ = 0;
  bool enabled_ = false;
  bool framed_ = false;
  bool overflow_ = false;
  bool trailingCr_ = false;
  bool framedSession_ = false;
  char response_[104]{};
};
#endif
