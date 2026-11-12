#include "Buttons.h"

constexpr uint16_t DebounceMs = 24;
constexpr uint16_t BackMs = 700;
constexpr uint16_t FirstRepeatMs = 440;
constexpr uint16_t RepeatMs = 110;

void Button::begin(bool down, uint32_t now) {
  rawDown_ = stableDown_ = down;
  changedAt_ = actedAt_ = now;
  // A key already held at startup must be released before it can act.
  longSent_ = down;
  repeatArmed_ = false;
}

KeyEvent Button::update(bool down, uint32_t now, bool repeat) {
  if (down != rawDown_) {
    rawDown_ = down;
    changedAt_ = now;
  }
  if (!repeat) repeatArmed_ = false;
  if (rawDown_ != stableDown_ && now - changedAt_ >= DebounceMs) {
    stableDown_ = rawDown_;
    if (!stableDown_) {
      if (press_ == KeyEvent::Enter && !longSent_) return KeyEvent::Enter;
      return KeyEvent::None;
    }
    actedAt_ = now;
    longSent_ = false;
    repeatArmed_ = repeat && press_ != KeyEvent::Enter;
    repeatDelay_ = FirstRepeatMs;
    if (press_ != KeyEvent::Enter) return press_;
  }
  if (!rawDown_ || !stableDown_) return KeyEvent::None;
  if (press_ == KeyEvent::Enter && !longSent_ && now - actedAt_ >= BackMs) {
    longSent_ = true;
    return KeyEvent::Back;
  }
  if (repeatArmed_ && now - actedAt_ >= repeatDelay_) {
    actedAt_ = now;
    repeatDelay_ = RepeatMs;
    return press_;
  }
  return KeyEvent::None;
}
