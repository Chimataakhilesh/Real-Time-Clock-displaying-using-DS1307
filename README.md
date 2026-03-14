# Real-Time Clock (RTC) using DS1307 and LPC2129

This project reads the current time from a DS1307 RTC module over I2C and displays hours, minutes, and seconds on an HD44780-compatible LCD using an NXP LPC2129 microcontroller.

## Features

- Reads time (hours, minutes, seconds) from DS1307 via I2C
- Displays time on 16x2 or 20x4 character LCD
- Uses LPC2129 microcontroller (ARM7TDMI-S)
- Simple, easy-to-follow hardware wiring and C source code

## Hardware Required

- LPC2129 microcontroller development board (or compatible LPC21xx)
- DS1307 RTC module (with backup battery)
- 16x2 (or 20x4) HD44780-compatible LCD
- Pull-up resistors for I2C (typically 4.7kΩ)
- Connecting wires and breadboard / PCB
- 5V power supply (or as required by your modules)

## Wiring / Connections

Example connections (adjust according to your board pinout):

- DS1307 VCC -> 5V (or 3.3V if your module supports it)
- DS1307 GND -> GND
- DS1307 SDA -> LPC2129 I2C SDA pin (e.g., P0.x)
- DS1307 SCL -> LPC2129 I2C SCL pin (e.g., P0.y)
- LCD VSS -> GND
- LCD VDD -> 5V
- LCD V0 -> Potentiometer (for contrast)
- LCD RS -> LPC2129 GPIO
- LCD RW -> GND (for write only)
- LCD E -> LPC2129 GPIO
- LCD D4..D7 -> LPC2129 GPIOs (for 4-bit mode)

Also ensure SDA and SCL lines have pull-up resistors (4.7kΩ recommended).

## Software

- Language: C
- Toolchain: ARM GCC / Keil MDK (or your preferred LPC21xx toolchain)

### Key implementation notes

- DS1307 communicates using I2C at 0x68 (7-bit address). The code reads the time registers and converts BCD to decimal as required.
- The LCD is used in 4-bit mode to save GPIO pins. Ensure initialization follows HD44780 timing requirements.
- If using different pins, update the pin definitions in the source files.

## Build and Flash

1. Import the provided C source files into your LPC21xx project in your preferred IDE (Keil, IAR, or makefile-based GCC project).
2. Configure the CPU clock and peripheral clocks according to your hardware.
3. Build the project.
4. Flash the resulting binary to the LPC2129 using your programmer (e.g., JTAG, ISP, or CDL depending on your board).

## Usage

- Power the board and RTC module. If the RTC battery is present and already set, the DS1307 will keep time.
- The program polls the RTC and updates the LCD with the current HH:MM:SS.
- To set the RTC time, either use a separate utility/programmer or modify the firmware to write to the DS1307 time registers.

## Troubleshooting

- Nothing displayed on LCD:
  - Check LCD contrast (V0 pot).
  - Verify LCD wiring (RS, E, D4..D7).
  - Confirm RW is tied to GND for write-only mode.

- Time not updating / wrong time:
  - Verify I2C wiring and pull-ups.
  - Check DS1307 battery is present and charged.
  - Use a logic analyzer or scope to verify I2C transactions.

- Compilation errors:
  - Make sure pin definitions and CPU clock settings match your board.
  - Ensure the correct include paths and peripheral libraries are added.

## References

- DS1307 datasheet: https://www.maximintegrated.com/en/products/digital/real-time-clocks/DS1307.html
- HD44780 LCD datasheet and timing reference
- NXP LPC2129 user manual

## Author

Chimataakhilesh
