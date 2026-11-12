# Firmware setup and operation

[Português (Brasil)](firmware.pt-BR.md) · [Project overview](../README.md)

## Build for MPS01 1.1

1. Download the source ZIP for `v0.4.0-beta` from [Releases](https://github.com/mariopin80/Aquecedor_piscina/releases). Extract the entire ZIP so the sketch and its companion files stay together.
2. Install Arduino AVR Boards 1.8.8 and LiquidCrystal 1.0.7 in Arduino IDE. Copy [BigNums2x2](../libraries/BigNums2x2) into your sketchbook's `libraries` directory. Wire and EEPROM come with the AVR core. The Bluetooth build also uses SoftwareSerial.
3. Open `firmware/PoolHeater/PoolHeater.ino`. Select **Arduino Uno** for the ATmega328P at 16 MHz. Use the upload method for your bootloader or program the AVR through ISP.

To verify compilation from the repository root, run

```sh
arduino-cli compile --fqbn arduino:avr:uno --libraries libraries firmware/PoolHeater
```

For older tags, use the build and EEPROM instructions included with that version. [Historical releases](https://github.com/mariopin80/Aquecedor_piscina/releases)

## First boot and migration

The beta imports valid temperature settings, pump modes and schedules from the historical EEPROM addresses on first boot. Empty or invalid values get defaults. Both pumps start in `DESL` on blank EEPROM. The pool target defaults to 25 °C, with 12 °C and 5 °C differential thresholds. The antifreeze and hot collector thresholds default to 4 °C and 65 °C. A legacy interval whose start was later than its end was inactive in the old software, so migration leaves that interval inactive until edited.

The beta stores future settings in two checksummed records at addresses 80–143. A downgrade recovers the pre-beta settings from addresses 0–67. The beta reads its own settings from the new records. The beta imports the value found at legacy address 52 for the filter mode, so verify it after an upgrade from the Bluetooth version.

Start on the bench with pump loads disconnected. Verify the sensor labels, local date and time and each pump mode before enabling automatic operation. [Hardware guide](hardware.md)

## Panel

| Control | Action |
| --- | --- |
| Short **Enter** | Open a menu or a setting, move to the next part of a time or schedule, or confirm the setting |
| Hold **Enter** for about 0.7 s | Back one level or cancel an unconfirmed edit |
| **+** / **−** | Move between items or change the value being edited |
| Hold **+** / **−** in a numeric or schedule setting | Repeat after about 0.44 s, then every 0.11 s |
| **+** or **−** on the home screen | Toggle the detailed view of the two probes |

The settings screens show `*` while editing and `~` while a save is in progress. After 30 seconds without key activity, it returns home and discards the edit in progress. The home screen shows the pool temperature and the reason for the solar output. `F` in the upper right indicates an active filter output. The details screen displays both probe temperatures or their individual diagnoses.

| Menu | Settings |
| --- | --- |
| `BOMBAS` | Independent `AUTO`, `LIGA` and `DESL` modes |
| `AQUECIMENTO` | Pool temperature target |
| `CIRCULACAO` | Day and on/off times for solar-loop circulation |
| `FILTRAGEM` | Day and on/off times for filtration |
| `RELOGIO` | Day, month, year, hour and minute. Weekday is calculated from the date. |
| `AJUSTES TECNICOS` | Start/stop differentials, two probe offsets, antifreeze and hot collector thresholds |
| `BLUETOOTH` | Enable with **+** or disable with **−** while editing, then confirm with **Enter** |

For either schedule, edit the day, start hour, start minute, stop hour and stop minute, then confirm. `TOD` is every day, `FDS` weekends and `UTL` weekdays. An interval such as Friday 22:00 to 02:00 runs until Saturday 02:00. Equal start and stop times disable the interval. The selection applies to the day on which the interval starts.

## Pump behavior

- In solar `AUTO`, the controller checks independent demands for antifreeze, hot collector circulation, differential heating and the circulation schedule. The display shows the highest-priority active reason in that order.
- The beta retains the historical hot collector action. When the collector reaches the threshold, solar `AUTO` requests circulation, with a 3 °C return margin. Antifreeze uses a 2 °C return margin.
- Either invalid probe blocks the solar relay in every mode. Three valid readings per probe restore operation. Filtration remains independent of the probes.
- An invalid or halted RTC, or two consecutive I²C read failures, pauses timed circulation and filtration. Solar temperature control still follows the probes. Manual filtration is available.
- Confirmed manual `LIGA` and `DESL` modes persist across restarts. Select `AUTO` to resume scheduling and thermal decisions.

## Bluetooth

Enable it from the front panel. The initial setting is off on first upgrade or blank EEPROM. A2 and A3 are the existing module UART at 9600 baud. The future app can query temperatures, relay commands and fault reasons or change modes, schedules, temperature settings and the clock. [Protocol specification](bluetooth.md)

To build without Bluetooth, set `POOLHEATER_ENABLE_BLUETOOTH` to `0` in `Board.h` or pass `-DPOOLHEATER_ENABLE_BLUETOOTH=0` via the Arduino CLI `compiler.cpp.extra_flags` build property. Legacy one-character commands are opt-in through `POOLHEATER_ENABLE_LEGACY_BT=1`.

## Verification

The beta builds for Arduino Uno with Bluetooth enabled, with it compiled out and with the optional legacy commands enabled. Host-side regression tests cover button events, schedules and pump decisions. Run them from the repository root with a C++11 compiler.

```sh
g++ -std=c++11 -Ifirmware/PoolHeater tests/control_and_buttons.cpp \
  firmware/PoolHeater/Buttons.cpp firmware/PoolHeater/Control.cpp -o pool-heater-tests
./pool-heater-tests
```

Verify the LCD, switches, RTC, probes, relay indications and Bluetooth module on the MPS01 1.1 bench before connecting loads.
