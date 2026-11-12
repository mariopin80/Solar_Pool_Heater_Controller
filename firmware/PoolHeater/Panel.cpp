#include "Panel.h"

#include <BigNums2x2.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include <string.h>

#include "Board.h"

namespace {
constexpr uint16_t RefreshMs = 200;
constexpr uint16_t InactivityMs = 30000;
constexpr uint8_t FieldCount[] = {2, 1, 1, 1, 1, 6, 1};

struct Text {
  char *line;
  uint8_t pos = 0;

  explicit Text(char *cells) : line(cells) {}
  void add(char c) { if (pos < 16) line[pos++] = c; }
  void add(const char *text) { while (*text && pos < 16) add(*text++); }
  void flash(PGM_P text) {
    for (char c = pgm_read_byte(text); c && pos < 16; c = pgm_read_byte(++text)) add(c);
  }
  void number(int16_t value) {
    char buffer[7];
    add(itoa(value, buffer, 10));
  }
  void two(uint8_t value) {
    add('0' + value / 10);
    add('0' + value % 10);
  }
  void time(uint16_t minute) {
    two(minute / 60);
    add(':');
    two(minute % 60);
  }
  void temperature(int16_t value) {
    if (value < 0) add('-');
    const uint16_t magnitude = abs(value);
    number(magnitude / 10);
    add('.');
    add('0' + magnitude % 10);
    add(static_cast<char>(223));
    add('C');
  }
};

PGM_P parameterLabel(Parameter parameter) {
  switch (parameter) {
    case Target:          return PSTR("TEMP. PISCINA");
    case DeltaOn:         return PSTR("DIFERENCIAL ON");
    case DeltaOff:        return PSTR("DIFERENCIAL OFF");
    case PoolOffset:      return PSTR("OFFSET PISCINA");
    case CollectorOffset: return PSTR("OFFSET COLETOR");
    case Freeze:          return PSTR("ANTICONGELAMENTO");
    default:              return PSTR("COLETOR QUENTE");
  }
}

PGM_P modeLabel(Mode mode) {
  switch (mode) {
    case On: return PSTR("LIGA");
    case Off: return PSTR("DESL");
    default: return PSTR("AUTO");
  }
}

PGM_P reasonLabel(Reason reason) {
  switch (reason) {
    case ManualOn:     return PSTR("MANUAL");
    case ManualOff:    return PSTR("DESL");
    case Heating:      return PSTR("SOLAR");
    case Scheduled:    return PSTR("AGENDA");
    case AntiFreeze:   return PSTR("GELO");
    case HotCollector: return PSTR("QUENTE");
    case SensorFault:  return PSTR("SONDA");
    case ClockFault:   return PSTR("RTC");
    default:           return PSTR("ESPERA");
  }
}

const char DayLabels[][4] PROGMEM = {
    "TOD", "DOM", "SEG", "TER", "QUA", "QUI", "SEX", "SAB", "FDS", "UTL"
};

void showSensor(Text &text, const Temperature &sensor) {
  switch (sensor.status) {
    case SensorOk:    text.temperature(sensor.tenths); break;
    case SensorShort: text.flash(PSTR("CURTO")); break;
    case SensorOpen:  text.flash(PSTR("ABERTA")); break;
    case SensorRange: text.flash(PSTR("FAIXA")); break;
    default:          text.flash(PSTR("AGUARDE")); break;
  }
}

// Trek glyph indices from BigNums2x2, in row order for the buffered LCD frame.
const uint8_t DisplayDigits[10][4] PROGMEM = {
    {5, 255, 7, 6}, {0, 1, 2, 7}, {0, 3, 4, 2}, {0, 3, 2, 3}, {1, 1, 0, 5},
    {4, 0, 2, 3}, {5, 0, 4, 3}, {0, 3, ' ', 1}, {4, 3, 4, 3}, {4, 3, 2, 6}
};

void bigDigit(char (&line)[2][16], uint8_t column, uint8_t digit) {
  for (uint8_t row = 0; row < 2; ++row) {
    for (uint8_t col = 0; col < 2; ++col) {
      line[row][column + col] = pgm_read_byte(&DisplayDigits[digit][row * 2 + col]);
    }
  }
}
}

const char *Panel::pageLabel() const {
  switch (page_) {
    case Pumps:       return PSTR("BOMBAS");
    case Heat:        return PSTR("AQUECIMENTO");
    case Circulation: return PSTR("CIRCULACAO");
    case Filtration:  return PSTR("FILTRAGEM");
    case Clock:       return PSTR("RELOGIO");
    case Technical:   return PSTR("AJUSTES TECNICOS");
    default:          return PSTR("BLUETOOTH");
  }
}

void Panel::begin(uint32_t now) {
  pinMode(Pins::Enter, INPUT_PULLUP);
  pinMode(Pins::Plus, INPUT_PULLUP);
  pinMode(Pins::Minus, INPUT_PULLUP);
  enter_.begin(digitalRead(Pins::Enter) == LOW, now);
  plus_.begin(digitalRead(Pins::Plus) == LOW, now);
  minus_.begin(digitalRead(Pins::Minus) == LOW, now);
  lcd_.begin(16, 2);
  // The archived font library installs the HD44780 characters after lcd.begin().
  static BigNums2x2 font(TREK);
  lcd_.setCursor(0, 0);
  lastInput_ = lastDraw_ = now;
}

void Panel::poll(uint32_t now, Settings &settings, Status &status, Inputs &inputs, SettingsStore &store) {
  const bool repeat = screen_ == Screen::Edit && page_ != Pumps && page_ != BluetoothPage;
  const KeyEvent enter = enter_.update(digitalRead(Pins::Enter) == LOW, now, false);
  const KeyEvent plus = plus_.update(digitalRead(Pins::Plus) == LOW, now, repeat);
  const KeyEvent minus = minus_.update(digitalRead(Pins::Minus) == LOW, now, repeat);
  const KeyEvent key = enter != KeyEvent::None ? enter : (plus != KeyEvent::None ? plus : minus);
  if (key != KeyEvent::None) {
    lastInput_ = now;
    notice_ = Notice::None;
    if (key == KeyEvent::Enter || key == KeyEvent::Back) {
      plus_.cancelRepeat();
      minus_.cancelRepeat();
    }
    handle(key, settings, status, inputs, store);
    dirty_ = true;
  } else if (screen_ != Screen::Home && now - lastInput_ >= InactivityMs) {
    screen_ = Screen::Home;
    notice_ = Notice::None;
    dirty_ = true;
  }
}

void Panel::handle(KeyEvent key, Settings &settings, Status &status, Inputs &inputs, SettingsStore &store) {
  const bool forward = key == KeyEvent::Plus;
  if (key == KeyEvent::Back) {
    if (screen_ == Screen::Edit) screen_ = Screen::Fields;
    else if (screen_ == Screen::Fields) screen_ = Screen::Menu;
    else screen_ = Screen::Home;
    return;
  }

  switch (screen_) {
    case Screen::Home:
      if (key == KeyEvent::Enter) { page_ = Pumps; screen_ = Screen::Menu; }
      else screen_ = Screen::Detail;
      break;
    case Screen::Detail:
      if (key == KeyEvent::Enter) { page_ = Pumps; screen_ = Screen::Menu; }
      else screen_ = Screen::Home;
      break;
    case Screen::Menu:
      if (key == KeyEvent::Enter) { field_ = 0; screen_ = Screen::Fields; }
      else {
        constexpr uint8_t pages = POOLHEATER_ENABLE_BLUETOOTH ? PageCount : BluetoothPage;
        page_ = (page_ + (forward ? 1 : pages - 1)) % pages;
      }
      break;
    case Screen::Fields:
      if (key == KeyEvent::Enter) startEdit(settings, status);
      else field_ = (field_ + (forward ? 1 : FieldCount[page_] - 1)) % FieldCount[page_];
      break;
    case Screen::Edit:
      if (key == KeyEvent::Enter) {
        if ((page_ == Clock || schedulePage()) && editPart_ < 4) ++editPart_;
        else {
          notice_ = save(settings, status, inputs, store);
          if (notice_ == Notice::None) screen_ = Screen::Fields;
        }
      } else {
        adjust(forward ? 1 : -1);
      }
      break;
  }
}

void Panel::startEdit(const Settings &settings, const Status &status) {
  editPart_ = 0;
  if (page_ == Pumps) value_ = settings.mode[field_];
  else if (page_ == BluetoothPage) value_ = settings.bluetooth;
  else if (schedulePage()) editSchedule_ = settings.schedule[schedulePump()];
  else if (page_ == Clock) {
    editTime_ = validDateTime(status.time) ? status.time : DateTime{0, 1, 1, 0, 0, 0};
  } else {
    value_ = settings.temp[parameter()];
  }
  screen_ = Screen::Edit;
}

void Panel::adjust(int8_t direction) {
  if (page_ == Clock) {
    uint8_t *parts[] = {&editTime_.day, &editTime_.month, &editTime_.year, &editTime_.hour, &editTime_.minute};
    const int16_t minimum = editPart_ < 2 ? 1 : 0;
    const int16_t maximum[] = {daysInMonth(editTime_.year, editTime_.month), 12, 99, 23, 59};
    uint8_t &part = *parts[editPart_];
    const int16_t proposed = part + direction;
    part = proposed > maximum[editPart_] ? minimum : (proposed < minimum ? maximum[editPart_] : proposed);
    const uint8_t lastDay = daysInMonth(editTime_.year, editTime_.month);
    if (editTime_.day > lastDay) editTime_.day = lastDay;
  } else if (page_ == Pumps) {
    value_ = (value_ + direction + 3) % 3;
  } else if (page_ == BluetoothPage) {
    value_ = direction > 0;
  } else if (schedulePage()) {
    if (editPart_ == 0) {
      editSchedule_.day = (editSchedule_.day + direction + 10) % 10;
    } else {
      uint16_t &time = editPart_ <= 2 ? editSchedule_.start : editSchedule_.end;
      if (editPart_ == 1 || editPart_ == 3) time = (time + 1440 + direction * 60) % 1440;
      else time = time / 60 * 60 + (time % 60 + 60 + direction) % 60;
    }
  } else {
    const Limits range = limits(parameter());
    const int16_t proposed = value_ + direction;
    if (proposed >= range.min && proposed <= range.max) value_ = proposed;
  }
}

Panel::Notice Panel::save(Settings &settings, Status &status, Inputs &inputs, SettingsStore &store) {
  if (page_ == Clock) {
    editTime_.second = 0;
    return inputs.setClock(editTime_, status) ? Notice::None : Notice::Rtc;
  }

  if (page_ == Pumps) {
    if (settings.mode[field_] == value_) return Notice::None;
    settings.mode[field_] = static_cast<Mode>(value_);
  } else if (page_ == BluetoothPage) {
    if (settings.bluetooth == (value_ != 0)) return Notice::None;
    settings.bluetooth = value_ != 0;
  } else if (schedulePage()) {
    Schedule &schedule = settings.schedule[schedulePump()];
    if (schedule.day == editSchedule_.day && schedule.start == editSchedule_.start &&
        schedule.end == editSchedule_.end) return Notice::None;
    schedule = editSchedule_;
  } else {
    int16_t &value = settings.temp[parameter()];
    if (value == value_) return Notice::None;
    const int16_t previous = value;
    value = value_;
    if (!validTemperatures(settings)) {
      value = previous;
      return Notice::Range;
    }
  }
  store.requestSave();
  return Notice::None;
}

void Panel::render(char (&line)[2][16], const Settings &settings, const Status &status, bool saving) const {
  Text top(line[0]);
  Text bottom(line[1]);
  if (screen_ == Screen::Home) {
    const int16_t pool = status.pool.tenths;
    if (status.pool.status == SensorOk && pool >= 0 && pool < 1000) {
      if (pool >= 100) bigDigit(line, 0, pool / 100);
      bigDigit(line, 3, (pool / 10) % 10);
      bottom.pos = 5;
      bottom.add('.');
      bottom.add('0' + pool % 10);
      bottom.add(static_cast<char>(223));
      bottom.add('C');
    } else {
      top.flash(PSTR("PSC"));
      showSensor(bottom, status.pool);
    }
    top.pos = 10;
    if (status.clockOk) top.time(status.time.hour * 60U + status.time.minute);
    else top.flash(PSTR("RTC!"));
    bottom.pos = 10;
    bottom.flash(reasonLabel(status.output[Solar].reason));
    if (status.output[Filter].on) line[0][15] = 'F';
    return;
  }

  if (screen_ == Screen::Detail) {
    top.flash(PSTR("PSC "));
    showSensor(top, status.pool);
    bottom.flash(PSTR("CLT "));
    showSensor(bottom, status.collector);
    return;
  }

  if (screen_ == Screen::Menu) {
    top.flash(pageLabel());
    bottom.flash(PSTR("+/-     ENT:ABRE"));
    return;
  }

  const bool editing = screen_ == Screen::Edit;
  if (page_ == Clock) {
    const DateTime &time = editing ? editTime_ : status.time;
    if (editing) {
      switch (editPart_) {
        case 0: top.flash(PSTR("AJUSTE DIA")); break;
        case 1: top.flash(PSTR("AJUSTE MES")); break;
        case 2: top.flash(PSTR("AJUSTE ANO")); break;
        case 3: top.flash(PSTR("AJUSTE HORA")); break;
        case 4: top.flash(PSTR("AJUSTE MINUTO")); break;
      }
    } else {
      top.flash(PSTR("DATA / HORA"));
    }
    if (editing || status.clockOk) {
      bottom.two(time.day); bottom.add('/');
      bottom.two(time.month); bottom.add('/');
      bottom.two(time.year); bottom.add(' ');
      bottom.time(time.hour * 60U + time.minute);
    } else {
      bottom.flash(PSTR("AJUSTE O RTC"));
    }
  } else if (page_ == Pumps) {
    top.flash(field_ == Solar ? PSTR("BOMBA SOLAR") : PSTR("BOMBA FILTRO"));
    bottom.flash(modeLabel(editing ? static_cast<Mode>(value_) : settings.mode[field_]));
    if (!editing) {
      bottom.add(' ');
      bottom.flash(reasonLabel(status.output[field_].reason));
    }
  } else if (page_ == BluetoothPage) {
    top.flash(PSTR("BLUETOOTH"));
    bottom.flash((editing ? value_ != 0 : settings.bluetooth) ? PSTR("ATIVO") : PSTR("INATIVO"));
  } else if (schedulePage()) {
    const Schedule &schedule = editing ? editSchedule_ : settings.schedule[schedulePump()];
    if (editing) {
      top.flash(page_ == Circulation ? PSTR("CIRC") : PSTR("FILTRO"));
      switch (editPart_) {
        case 0: top.flash(PSTR(" DIA")); break;
        case 1: top.flash(PSTR(" LIGA H")); break;
        case 2: top.flash(PSTR(" LIGA M")); break;
        case 3: top.flash(PSTR(" DESL H")); break;
        case 4: top.flash(PSTR(" DESL M")); break;
      }
      if (editPart_ == 0) bottom.flash(DayLabels[schedule.day]);
      else bottom.time(editPart_ <= 2 ? schedule.start : schedule.end);
    } else {
      top.flash(pageLabel());
      bottom.time(schedule.start);
      bottom.add('-');
      bottom.time(schedule.end);
      bottom.add(' ');
      bottom.flash(DayLabels[schedule.day]);
    }
  } else {
    top.flash(parameterLabel(parameter()));
    bottom.temperature(editing ? value_ : settings.temp[parameter()]);
  }

  if (editing) line[1][15] = '*';
  else if (saving) line[1][15] = '~';

  if (notice_ != Notice::None) {
    memset(line[0], ' ', sizeof(line[0]));
    top.pos = 0;
    top.flash(notice_ == Notice::Rtc ? PSTR("FALHA NO RTC") : PSTR("DIF OFF < ON"));
  }
}

void Panel::refresh(uint32_t now, const Settings &settings, const Status &status, bool saving) {
  if (!dirty_ && now - lastDraw_ < RefreshMs) return;
  dirty_ = false;
  lastDraw_ = now;
  char frame[2][16];
  memset(frame, ' ', sizeof(frame));
  render(frame, settings, status, saving);
  for (uint8_t row = 0; row < 2; ++row) {
    for (uint8_t col = 0; col < 16;) {
      if (!firstFrame_ && drawn_[row][col] == frame[row][col]) { ++col; continue; }
      lcd_.setCursor(col, row);
      do {
        drawn_[row][col] = frame[row][col];
        lcd_.write(static_cast<uint8_t>(frame[row][col++]));
      } while (col < 16 && (firstFrame_ || drawn_[row][col] != frame[row][col]));
    }
  }
  firstFrame_ = false;
}
