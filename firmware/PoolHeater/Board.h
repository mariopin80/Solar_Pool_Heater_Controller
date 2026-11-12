#pragma once

#include <Arduino.h>

#define POOLHEATER_VERSION "0.4.0-beta"

// Set to 0 to build without SoftwareSerial or the Bluetooth protocol.
#ifndef POOLHEATER_ENABLE_BLUETOOTH
#define POOLHEATER_ENABLE_BLUETOOTH 1
#endif

// Set to 1 for terminals that use the single-byte commands from v0.3.0_BT.
#ifndef POOLHEATER_ENABLE_LEGACY_BT
#define POOLHEATER_ENABLE_LEGACY_BT 0
#endif

namespace Pins {
constexpr uint8_t Enter = 4;
constexpr uint8_t Plus = 3;
constexpr uint8_t Minus = 2;
constexpr uint8_t SolarRelay = 6;
constexpr uint8_t FilterRelay = 5;
constexpr uint8_t PoolNtc = A0;
constexpr uint8_t CollectorNtc = A1;
constexpr uint8_t BluetoothRx = A2;
constexpr uint8_t BluetoothTx = A3;
constexpr uint8_t LcdRs = 8;
constexpr uint8_t LcdEnable = 9;
constexpr uint8_t LcdD4 = 13;
constexpr uint8_t LcdD5 = 12;
constexpr uint8_t LcdD6 = 11;
constexpr uint8_t LcdD7 = 10;
}
