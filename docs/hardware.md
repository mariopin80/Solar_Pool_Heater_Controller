# Hardware and assembly

[Português (Brasil)](hardware.pt-BR.md) · [Project overview](../README.md)

## KiCad project files

| Design | Schematic | PCB |
| --- | --- | --- |
| MPS01 1.0 | [Schematic](../hardware/MPS01/1.0/Hardware%20Aquecedor.sch) | [PCB](../hardware/MPS01/1.0/Hardware%20Aquecedor.kicad_pcb) |
| MPS01 1.0, alternate layout | [Same 1.0 schematic](../hardware/MPS01/1.0/Hardware%20Aquecedor.sch) | [PCB named “v2” in the archive](../hardware/MPS01/1.0/layout-v2/Hardware%20Aquecedor%20v2.kicad_pcb) |
| MPS01 1.1 | [Schematic](../hardware/MPS01/1.1/Hardware%20Aquecedor%201.1.sch) | [PCB with corrected SDA and SCL](../hardware/MPS01/1.1/Hardware%20Aquecedor%201.1.kicad_pcb) |
| MPS02 2.0 | [Schematic](../hardware/MPS02/2.0/Hardware%20Aquecedor%202.0.sch) · [PDF](../hardware/MPS02/2.0/esquema.pdf) | [PCB](../hardware/MPS02/2.0/Hardware%20Aquecedor%202.0.kicad_pcb) |

The design files use the KiCad 5 legacy format. Open the `.pro`, `.sch` and `.kicad_pcb` files from the same revision. The MPS01 schematic uses the project-local `atmega` symbol library. Keep the library, `sym-lib-table` and schematic cache alongside the schematic.

Two original fabrication archives accompany the MPS01 layout named “v2”. Both predate the SDA/SCL correction in 1.1. Generate fabrication files from the PCB for the revision you intend to build. [Archived Gerbers and drill files](../hardware/MPS01/1.0/layout-v2/fabrication)

Use the reference designators and values in the selected schematic when populating the PCB. The 2021 spreadsheet is the original component list from the MPS01 project. [BOM](BOM.xlsx)

## MPS01 1.1 logic connections

The MPS01 1.1 is the firmware target. This mapping applies to firmware `v0.0.6` and later. The earlier prototype sketches use different button, relay and LCD assignments in their declarations.

| Signal | Arduino pin | MPS01 connection |
| --- | --- | --- |
| Menu / Enter | D4 | SW1, active low |
| Next / + | D3 | SW2, active low |
| Back / − | D2 | SW3, active low |
| Heating pump command | D6 | K1 driver, output contacts at J5 |
| Filtration pump command | D5 | K2 driver, output contacts at J6 |
| Pool NTC in firmware | A0 | J3, marked `CLT_TMP` in KiCad |
| Collector NTC in firmware | A1 | J4, marked `PSC_TMP` in KiCad |
| LCD RS | D8 | DS1 pin 4 |
| LCD E | D9 | DS1 pin 6 |
| LCD D4 | D13 | DS1 pin 11 |
| LCD D5 | D12 | DS1 pin 12 |
| LCD D6 | D11 | DS1 pin 13 |
| LCD D7 | D10 | DS1 pin 14 |
| RTC SDA | A4 | DS1307 pin 5, routing on 1.1 |
| RTC SCL | A5 | DS1307 pin 6, routing on 1.1 |
| Software UART RX | A2 / D16 | Bluetooth sketches from `v0.2.2` |
| Software UART TX | A3 / D17 | Bluetooth sketches from `v0.2.2` |

For each NTC input, pin 1 is the measurement node and pin 2 is ground. The MPS01 PCB has a 10 kΩ pull-up resistor for each input. The supplied firmware expects a 10 kΩ NTC with beta 3600 K. Verify which displayed temperature responds to each probe before checking heating operation. In the [original pinout note](original/pinout-arduino.txt), the sensor names match the KiCad nets and the LCD D4 entry has a typo. The table above follows the sketches for both.

The MPS01 1.0 and alternate “v2” layouts route the ATmega328P pins 27 and 28 to SCL and SDA, respectively. This inversion prompted the 1.1 correction. The layout originally named `Hardware Aquecedor v1.1 SDA-SCL OK` routes pin 27 to SDA and pin 28 to SCL. The original history records a wiring correction during tests of the first PCB.

J2 on the MPS01 is the programming UART and carries the ATmega's D0/D1 signals. The software UART in the Bluetooth sketches uses the separate A2/A3 pins listed above. Match logic levels to the serial adapter or module you use.

## MPS02 connectors

| Connector | Schematic function |
| --- | --- |
| J2 | Three push-button inputs and ground |
| J3 | Parallel LCD interface |
| J4 | Programming UART |
| J5 | Pool sensor |
| J6 | Collector sensor |
| J7 | Heating relay contacts |
| J8 | Filtration relay contacts |

MPS02 remained a KiCad design, based on the ESP32-WROOM-32D and DS3231M. Use the 2.0 schematic for that board's signals and component values. The supplied AVR sketch uses the MPS01's ADC scaling, pin map and RTC driver.

## Bench check

To verify the logic on an Arduino Uno, use the signal table with a 16×2 LCD, the buttons, a DS1307 RTC and two NTC dividers. Use indicators in place of pump loads. Verify the LCD, buttons, clock and both temperature readings, then command each output independently from the pump menu. The archived [PCB test sketch](../examples/teste_PCB) uses the MPS01 pin mapping.

The original boards include a mains power input at J1. Keep the mains input and pump loads disconnected during logic checks. Treat the schematic and fabrication archives as design references for the finished installation.
