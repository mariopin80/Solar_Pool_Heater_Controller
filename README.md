# Solar Pool Heater Controller

[Português (Brasil)](README.pt-BR.md)

Designed by Mario Pin (PU2PTU). The controller compares water temperatures at the pool and the solar collector and switches the heating pump according to the temperature difference. A separate relay runs the filtration pump on a schedule. Later firmware revisions add manual pump modes, scheduled heating-loop circulation, and a serial Bluetooth interface.

![KiCad rendering of the MPS01 revision 1.1 PCB](docs/mps01-1.1.png)

## Hardware

| Board | Controller and clock | Firmware |
| --- | --- | --- |
| [MPS01 1.0](hardware/MPS01/1.0) | ATmega328P at 16 MHz and DS1307 | Historical PCB. This revision reverses SDA and SCL. |
| [MPS01 1.1](hardware/MPS01/1.1) | ATmega328P at 16 MHz and DS1307 | Target board for the archived AVR firmware. Corrected I²C routing. |
| [MPS02 2.0](hardware/MPS02/2.0) | ESP32-WROOM-32D and DS3231M | KiCad design only. This revision stayed at the design stage. |

The MPS01 1.1 is the target for the 13 historical firmware versions and the 0.4.0 beta. The MPS01 uses two 10 kΩ NTC probes, a parallel 16×2 LCD, three push buttons and separate relays for the heating and filtration pumps. The hardware guide includes the Arduino pinout, connector assignments and the sensor-label discrepancy between the MPS01 schematics and sketches. [Hardware and assembly guide](docs/hardware.md) · [Original parts list](docs/BOM.xlsx)

## Firmware

The `v0.4.0-beta` adds a responsive three-button panel, probe and RTC diagnostics, validated EEPROM settings and an optional Bluetooth UART protocol for an app. The MPS01 1.1 pin mapping is unchanged. Download the complete source archive to compile the beta.

- [Beta installation and operating guide](docs/firmware.md)
- [Bluetooth protocol v1](docs/bluetooth.md)
- [Firmware review and commercial feature comparison (PT-BR)](docs/firmware-review.pt-BR.md)
- [Changes by version](CHANGELOG.md)
- [GitHub releases](https://github.com/mariopin80/Aquecedor_piscina/releases)
- [MPS01 PCB test sketch](examples/teste_PCB)

The historical releases retain their original sketches at `firmware/PoolHeater/PoolHeater.ino`. The beta uses that same Arduino entry point with its companion source files in the sketch folder.
