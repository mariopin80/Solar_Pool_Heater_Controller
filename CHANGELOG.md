# Firmware changelog

[Português (Brasil)](CHANGELOG.pt-BR.md) · [Project overview](README.md)

The 13 snapshots belong to the MPS01 1.1 firmware. Version identifiers follow the original folder names. Dates come from the original notes or sketch headers. Changes were checked against adjacent sketches.

[Original notes](docs/original/historico-de-revisao.txt)

## v0.4.0-beta

- Replaces blocking menu delays with debounced button events, long-press back/cancel and repeat while editing.
- Adds independent control demands, probe and RTC diagnostics, and schedules that cross midnight.
- Migrates valid legacy EEPROM settings to two checksummed records and fixes the Bluetooth filter-mode persistence error.
- Adds Bluetooth UART protocol v1, a local enable/disable setting and a compile-time option to remove it.
- Compiled for Arduino Uno. Pending verification on the physical MPS01 1.1.

## v0.3.0_BT · 2021-11-12

- Adds serial commands `1`–`6` for both pumps and `7` for the two temperature readings. Shortens menu delays.
- Known issue: filter commands `4`–`6` write the heater mode to the filter's EEPROM address. The front panel writes the filter mode correctly.
- The `_BT` suffix comes from the original folder. The header and boot screen show `0.3.0`.

## v0.2.2 · 2021-10-21

- Initializes a 9600 baud software UART on A2/A3 for a serial Bluetooth module.
- Uses a shared minutes-since-midnight value for both schedules.

## v0.2.1b

- Averages 50 ADC samples per sensor, blinks `ICE` and `OVH`, and corrects the differential shutoff comparison.
- The original folder identifies the `b` revision. The header and boot screen still show `0.2.1`.

## v0.2.1 · 2021-10-15

- Adds adjustable anti-ice and overtemperature thresholds in EEPROM, with `ICE` and `OVH` indicators.
- Retains heating and circulation demand between updates and adds return margins around the collector limits.

## v0.2.0 · 2021-10-08

- Adds a separate schedule for heating-loop circulation and combines it with temperature demand in automatic mode.
- Starts the RTC on each boot and changes the fixed collector overtemperature threshold to 65 °C.

## v0.1.1 · 2021-06-24

- Adds early daily circulation menu states and names the LCD pin constants. The circulation menu reuses the two filter schedule slots.
- The original notes mention RTC drift compensation. The seconds adjustment in the supplied sketch is commented out.
- The source header and boot screen still show `0.1.0`.

## v0.1.0 · 2021-06-22

- Original MVP milestone. Adds independent automatic, forced-on and forced-off modes for the heater and filter pumps and persists them in EEPROM.

## v0.0.6 · 2021-06-21

- Reassigns the buttons, relay outputs and LCD pins and applies the filter schedule to the output.
- Converts both sensor channels as NTC dividers using the PCB's resistor arrangement.
- The original notes record early tests with the first PCB and a wiring workaround for reversed RTC SDA/SCL. The MPS01 1.1 layout corrects that routing.

## v0.0.5 · 2021-05-28

- Adds dedicated hour, date and weekday editing and the initial filtration schedule menus with EEPROM storage.

## v0.0.4 · 2021-05-27

- Integrates the DS1307 RTC and the first date and time settings.
- Reuses adjustment routines across menu screens.

## v0.0.3 · 2021-05-27

- Adds separate calibration offsets for the pool and collector readings, editable in the technical menu and stored in EEPROM.

## v0.0.2 · 2021-05-25

- First minimally functional heater control, with independent differential start and stop thresholds and fixed collector temperature limits.
- Adds the NTC conversion for the pool channel and retains a linear conversion for the collector channel.

## v0.0.1 · 2021-05-13

- Initial LCD interface, temperature display, pump outputs and EEPROM settings.
- The sketch references DS1307 without including RTC.h and uses an undeclared `segundo` variable.
