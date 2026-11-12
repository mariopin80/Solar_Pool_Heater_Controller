#pragma once

#include <stdint.h>

enum class KeyEvent : uint8_t { None, Enter, Back, Plus, Minus };

class Button {
 public:
  explicit Button(KeyEvent press) : press_(press) {}
  void begin(bool down, uint32_t now);
  KeyEvent update(bool down, uint32_t now, bool repeat);
  void cancelRepeat() { repeatArmed_ = false; }

 private:
  const KeyEvent press_;
  bool rawDown_ = false;
  bool stableDown_ = false;
  bool longSent_ = false;
  bool repeatArmed_ = false;
  uint32_t changedAt_ = 0;
  uint32_t actedAt_ = 0;
  uint16_t repeatDelay_ = 0;
};
