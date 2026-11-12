# Firmware setup and operation

[Português (Brasil)](firmware.pt-BR.md) · [Project overview](../README.md)

## Build for MPS01 1.1

1. Download the source ZIP of the desired [release](https://github.com/mariopin80/Aquecedor_piscina/releases) or check out its Git tag. The sketch is in `firmware/PoolHeater/PoolHeater.ino`.
2. In Arduino IDE, install the Arduino AVR Boards package and the LiquidCrystal library. Copy the [BigNums2x2 and RTC folders](../libraries) to the sketchbook's `libraries` directory. EEPROM, SoftwareSerial and Wire are provided by the AVR core.
3. Open the sketch and choose **Arduino Uno** for the ATmega328P at 16 MHz. Use the serial port and upload procedure for your bootloader. For a blank AVR, the board needs to be programmed with an AVR programmer before serial upload can work.

The equivalent Arduino CLI build from the repository root is

```sh
arduino-cli core update-index
arduino-cli core install arduino:avr
arduino-cli lib install LiquidCrystal
arduino-cli compile --fqbn arduino:avr:uno --libraries libraries firmware/PoolHeater
```

All archived versions belong to the MPS01 1.1 firmware lineage. Check the sketch declarations for the early prototype pin mapping. [Hardware guide](hardware.md)

## First boot

The historical sketches read settings directly from EEPROM. On a new MCU, initialize it once with pump loads disconnected. The commented block marked `USAR SOMENTE na montagem inicial` in `setup()` contains the original starting values. Enable it in a local copy for the initialization upload. Starting at `v0.2.0`, the circulation schedule also needs bytes 24, 26, 34, 36, 44 and 46 initialized. Add these writes to the same temporary block for that initial boot.

```cpp
EEPROM.update(24, 0);
EEPROM.update(26, 0);
EEPROM.update(34, 0);
EEPROM.update(36, 0);
EEPROM.update(44, 0);
EEPROM.update(46, 0);
```

Then upload the original sketch again so subsequent boots retain the stored settings. Check the RTC time, date and weekday in the menu. An initialized on/off pair of 00:00 and 00:00 gives an empty schedule interval.

## Front panel

The menu flow below follows `v0.2.2` and `v0.3.0_BT`. Labels on the LCD are in Portuguese.

| Screen | What to set |
| --- | --- |
| Home | The large number is the pool temperature. Press **+** for both temperature readings. Press **Enter** for the settings sequence. |
| `ESTADO BOMBAS` | Press **+** to enter pump modes. Press **Enter** to edit and confirm each pump in turn. Select `AUTO`, `LIGA` (on) or `DESL` (off) with **+** and **−**. |
| `AJUSTE AQUECEDOR` | Press **+** for `TEMP PISCINA`, then set the circulation day and on/off times under `C DIA`. |
| `AJUSTE FILTRO` | Press **+** to set the filtration day and on/off times under `PROG.1`. |
| `AJUSTE DATA/HORA` | Press **+** for time, date and weekday. |
| `CONFIG TECNICA` | Press **+** for the differential thresholds, the two sensor offsets and the anti-ice and high-temperature thresholds. |

At a settings heading, **Enter** advances to the next heading and **−** returns home. Within a setting, use **Enter** to edit or confirm and **+**/**−** to change the selected value. For schedules, `TOD` means every day, `FDS` weekends and `UTL` weekdays. Use an on time earlier than the off time on the same day. The code compares both times within a single day.

In `AUTO`, the heating pump follows the differential temperature demand, collector temperature limits and circulation schedule. The filter follows its own schedule. Manual `LIGA` and `DESL` directly command the output and bypass the automatic decisions.

## Bluetooth experiment

`v0.2.2` initializes the software UART. `v0.3.0_BT` adds single-character commands at 9600 baud.

| Character | Command |
| --- | --- |
| `1` / `2` / `3` | Heating pump auto / on / off |
| `4` / `5` / `6` | Filter pump auto / on / off |
| `7` | Return the pool and collector temperatures |

Commands `4` to `6` update the filter mode in RAM, then store the **heating** mode at the filter's EEPROM address. Set the filter mode on the front panel to save it correctly across a power cycle. The release preserves the original Bluetooth implementation for reference.

## Build verification

The archived sketches were compiled for Arduino Uno with Arduino CLI 1.6.0, Arduino AVR Boards 1.8.8 and LiquidCrystal 1.0.7. Versions `v0.0.2` through `v0.3.0_BT` and the PCB test sketch compiled. The original `v0.0.1` fails because the DS1307 declaration is missing its RTC include and `segundo` is undeclared. This check covers compilation.
