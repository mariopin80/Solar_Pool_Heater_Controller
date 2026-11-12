/*
 * MPS01 1.1 solar pool heater and filtration controller
 * Original project by Mario Pin (PU2PTU)
 */

#include "Board.h"
#include "Bluetooth.h"
#include "Control.h"
#include "Inputs.h"
#include "Panel.h"
#include "SettingsStore.h"

// The archived LCD font library uses this symbol to load its custom characters.
LiquidCrystal lcd(Pins::LcdRs, Pins::LcdEnable, Pins::LcdD4, Pins::LcdD5, Pins::LcdD6, Pins::LcdD7);

static Panel panel(lcd);
static Settings settings;
static SettingsStore store;
static Inputs inputs;
static PumpControl control;
static Status status;
#if POOLHEATER_ENABLE_BLUETOOTH
static Bluetooth bluetooth;
#endif

void setup() {
  digitalWrite(Pins::SolarRelay, LOW);
  digitalWrite(Pins::FilterRelay, LOW);
  pinMode(Pins::SolarRelay, OUTPUT);
  pinMode(Pins::FilterRelay, OUTPUT);
  status.pool.status = SensorWait;
  status.collector.status = SensorWait;
  store.begin(settings);
  inputs.begin();
  panel.begin(millis());
}

void loop() {
  const uint32_t now = millis();
  inputs.tick(now, settings, status);
  panel.poll(now, settings, status, inputs, store);
  control.update(settings, status);
  digitalWrite(Pins::SolarRelay, status.output[Solar].on ? HIGH : LOW);
  digitalWrite(Pins::FilterRelay, status.output[Filter].on ? HIGH : LOW);
  panel.refresh(now, settings, status, store.saving());
  store.tick(settings);
#if POOLHEATER_ENABLE_BLUETOOTH
  bluetooth.tick(now, settings, status, inputs, store);
#endif
}
