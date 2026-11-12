# Bluetooth UART protocol v1

[Operação do Bluetooth (PT-BR)](firmware.pt-BR.md#bluetooth) · [Firmware guide](firmware.md#bluetooth)

The MPS01 1.1 uses the external serial module on A2 (controller RX) and A3 (controller TX) at **9600 baud, 8N1**. Enable the interface in the local `BLUETOOTH` menu. The setting is saved in EEPROM. Disabling it closes the firmware UART listener and clears partial requests. The external radio manages its power and pairing. The app transport will depend on the installed module's Bluetooth profile. The UART protocol is the same for any module that passes the bytes through.

## Framing

Send one request at a time and wait for its response before sending the next. A request starts with `@`, has a decimal ID between 1 and 32767, and ends with LF (CRLF is accepted). The body after `@` and before CR/LF can contain up to 47 printable ASCII characters. Space separates fields. Command names are uppercase. The firmware's inter-byte timeout is 500 ms.

Responses use LF and echo the request ID. `@0 ERR ...` describes a transport or framing error that cannot be assigned to a particular request. A new `@` starts a new frame. Use a client timeout of about one second and poll `STATUS` for live values and output states. Use the ID to associate each response with its request.

```text
@1 INFO
@1 OK INFO 1 0.4.0-beta MPS01-1.1
@2 MODE 1 1
@2 OK PENDING
@3 SET 2 150
@3 ERR RANGE
```

`OK PENDING` means the RAM setting was accepted and EEPROM has work pending. A subsequent `STATUS` with `saving=0` indicates that the settings commit finished. `CLOCK` writes the RTC and confirms a read-back. Use `STATUS` to see the actual controller output, which can be off with mode `ON` if the solar sensors are faulty. Relay states are controller outputs. Flow feedback would require additional hardware.

## Commands

| Request after ID | Function |
| --- | --- |
| `INFO` | Protocol version, firmware version and board |
| `STATUS` | Temperatures and sensor diagnoses, pump modes and outputs, clock, EEPROM state |
| `GET` | Temperature settings, both schedules and the local Bluetooth flag |
| `MODE <pump> <mode>` | Set pump mode. Pumps `0` solar and `1` filter. Modes `0` AUTO, `1` ON and `2` OFF. |
| `SET <parameter> <tenths>` | Change one temperature setting in tenths of a degree Celsius. |
| `SCHED <pump> <day> <start> <end>` | Set an entire schedule. Times are minutes since midnight (0–1439). |
| `CLOCK <YYYYMMDD> <HHMMSS>` | Set local DS1307 time, years 2000–2099. The firmware calculates the weekday from the date. |

Day values are `0` every day, `1` Sunday through `7` Saturday, `8` weekends and `9` weekdays. An overnight interval belongs to its start day. Equal times disable the interval.

| Parameter ID | Meaning | Range in tenths |
| --- | --- | --- |
| 0 | Pool target | 100 to 400 |
| 1 | Differential to start | 20 to 250 |
| 2 | Differential to stop | 20 to 250 |
| 3 | Pool sensor offset | −50 to 50 |
| 4 | Collector sensor offset | −50 to 50 |
| 5 | Collector freeze threshold | 0 to 70 |
| 6 | Hot collector threshold | 500 to 900 |

The stop differential must be below the start differential. When changing both, submit the two values in the order that keeps the intermediate configuration valid.

## Response fields

```text
@<id> OK INFO <protocol> <version> <board>
@<id> OK STATUS <poolDiag> <poolTemp> <collectorDiag> <collectorTemp> <solarMode> <solarOutput> <solarReason> <filterMode> <filterOutput> <filterReason> <rtcOk> <YYYYMMDD> <HHMMSS> <saving>
@<id> OK GET <target> <deltaOn> <deltaOff> <poolOffset> <collectorOffset> <freeze> <hot> <solarDay> <solarStart> <solarEnd> <filterDay> <filterStart> <filterEnd> <bluetooth>
@<id> OK
@<id> OK PENDING
@<id> ERR <code>
```

- Temperatures use signed tenths of a degree Celsius. Invalid temperatures are `-`. Clock data is `- -` if the RTC is invalid. Flags and outputs use `0` or `1`.
- Sensor diagnoses are `0` valid, `1` waiting for a stable startup reading, `2` short, `3` open and `4` out of range. After a fault, the original fault diagnosis remains until the required valid samples arrive.
- Output reasons are `0` idle, `1` manual on, `2` manual off, `3` solar differential, `4` schedule, `5` antifreeze, `6` hot collector, `7` sensor fault and `8` clock fault.
- Errors are `ID` invalid request ID, `COMMAND` unknown command, `ARG` missing or invalid arguments, `RANGE` invalid setting, `RTC` write/read-back failure, `FRAME` invalid or oversized frame, `TIMEOUT` incomplete frame and `OVERRUN` serial receive overflow.

`POOLHEATER_ENABLE_BLUETOOTH=0` in [Board.h](../firmware/PoolHeater/Board.h) removes the transport and its panel menu from the build. For testing older serial terminals, `POOLHEATER_ENABLE_LEGACY_BT=1` also accepts commands `1`–`7` from `v0.3.0_BT`. Once the first `@` arrives, that UART session accepts framed commands only. Toggle the panel setting to reset the session. The future app should use protocol v1. Access to the UART is controlled by the external module's pairing settings.
