#pragma once

#include <LiquidCrystal.h>

#include "Buttons.h"
#include "Control.h"
#include "Inputs.h"
#include "SettingsStore.h"

class Panel {
 public:
  explicit Panel(LiquidCrystal &lcd) : lcd_(lcd) {}
  void begin(uint32_t now);
  void poll(uint32_t now, Settings &settings, Status &status, Inputs &inputs, SettingsStore &store);
  void refresh(uint32_t now, const Settings &settings, const Status &status, bool saving);

 private:
  enum class Screen : uint8_t { Home, Detail, Menu, Fields, Edit };
  enum Page : uint8_t { Pumps, Heat, Circulation, Filtration, Clock, Technical, BluetoothPage, PageCount };
  enum class Notice : uint8_t { None, Range, Rtc };

  void handle(KeyEvent key, Settings &settings, Status &status, Inputs &inputs, SettingsStore &store);
  void adjust(int8_t direction);
  bool schedulePage() const { return page_ == Circulation || page_ == Filtration; }
  Pump schedulePump() const { return page_ == Circulation ? Solar : Filter; }
  Parameter parameter() const { return page_ == Heat ? Target : static_cast<Parameter>(DeltaOn + field_); }
  const char *pageLabel() const;
  void startEdit(const Settings &settings, const Status &status);
  Notice save(Settings &settings, Status &status, Inputs &inputs, SettingsStore &store);
  void render(char (&line)[2][16], const Settings &settings, const Status &status, bool saving) const;

  LiquidCrystal &lcd_;
  Button enter_{KeyEvent::Enter};
  Button plus_{KeyEvent::Plus};
  Button minus_{KeyEvent::Minus};
  Screen screen_ = Screen::Home;
  uint8_t page_ = 0;
  uint8_t field_ = 0;
  uint8_t editPart_ = 0;
  int16_t value_ = 0;
  DateTime editTime_{};
  Schedule editSchedule_{};
  Notice notice_ = Notice::None;
  uint32_t lastInput_ = 0;
  uint32_t lastDraw_ = 0;
  bool dirty_ = true;
  bool firstFrame_ = true;
  char drawn_[2][16];
};
