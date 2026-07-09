Note:   The load is a resistive ~ 300W @ 245V AC input.  Using 1 x CT Clamps on CT1

Test Example Output is also sent on RS485:

    Mains RMS Voltage 1: 238.71 V AC
    Mains Current CT1: 1.35 A AC
    Hello World - Test


Serial Monitor on the USB Port will provide the below example.

===========

UART 1 Opened (RS485 Port)

FLiX Lite - Integrated Firmware for DitroniX Power Energy Monitor SDK Boards

Scanning and Configuring Board.. Please Wait..

Hardware Options and Auto Configuration
────────────────────────────────────────
Scanning I2C Bus for Devices for Auto Configuration ...
 I2C Possible Device(s) found at Address:
 * Hex 0x49 (73)         ADS1115 16-bit ADC
 * Hex 0x4A (74)         TMP102 Temperature Sensor
 * Hex 0x50 (80)         EEPROM
 * Hex 0x58 (88)         EEPROM
 I2C Bus Scan Complete

IPEM NB-IoT IoT Power Energy Monitor Controller

IPEM NB-IoT Register Status and Startup Report
ESP32-C5 Serial ID: 29FFFEBE4438
FLiX Lite for IPEM NB-IoT - Firmware Version: 260704
Board Location: Test

Wi-Fi Options
──────────────

Software Options
─────────────────
Connecting to the ATM90E36
====================================
ATM90E36 Connected - OK

IPEM NB-IoT Hardware Setup and Power-Up Test - Board Initialized

IPEM NB-IoT IoT Power Energy Monitor Controller

IPEM NB-IoT Register Status and Startup Report
ESP32-C5 Serial ID: 29FFFEBE4438
FLiX Lite for IPEM NB-IoT - Firmware Version: 260704
Location: Test

Hardware Configuration for ATM90E36
────────────────────────────────────
AC Voltage Inputs:      Multi Separated V1 V2 V3 - 3 Phase, or 3 x Single Phase Configuration.
Split AC Voltage:       Dual  or Split Voltage Input Disabled
CT Current Clamps:      Configured for 1, 2, 3 Phase

[Status Values]
System Status:          S0:0xC0         S1:0x0
Meter Status:           E0:0x5          E1:0x0

Mains RMS Voltage
──────────────────
Voltage 1: 243.35 V
Voltage 2: 243.94 V
Voltage 3: 243.83 V
- - - - - - - - - - - - - - - - - - - - 
Average Voltage: 243.71 V (V1~V2~V3)

Mains RMS Current
──────────────────
Current CT1: 1.26 A
Current CT2: 0.00 A
Current CT3: 0.00 A
Current CTN: 1.26 A
- - - - - - - - - - - - - - - - - - - - - - - 
Actual Total Current: 1.26 A (CT1~CT2~CT3)

- - - - - - - - - - - - - - - - - - - - - - - - - 
Calculated Total Power: 306.62 W (CT1~CT2~CT3)

Active Power (Absorbed or Used by the Load)
────────────────────────────────────────────
Active Power CT1: -0.31 kW      (Export)
Active Power CT2: 0.00 kW 
Active Power CT3: 0.00 kW 
- - - - - - - - - - - - - - - - - - - - - 
Total Active Power: -0.31 kW    (Export)
- - - - - - - - - - - - - - - - - - - - - - - - - - - - 
Calculated Total Active Power: -0.31 W (CT1~CT2~CT3)

Re-Active Power
────────────────
ReActive Power CT1: 0.00 VAR
ReActive Power CT2: 0.00 VAR
ReActive Power CT3: 0.00 VAR
- - - - - - - - - - - - - - - - - - - - - - - - 
Total ReActive Power: 0.00 VAR (CT1~CT2~CT3)
- - - - - - - - - - - - - - - - - - - - - - - - - - - - 
Calculated Total Reactive Power: 0.00 W (CT1~CT2~CT3)

Apparent Power (Total Amount of Power Flowing from Source to Load)
───────────────────────────────────────────────────────────────────
Apparent Power CT1: 0.31 VA
Apparent Power CT2: 0.00 VA
Apparent Power CT3: 0.00 VA
- - - - - - - - - - - - - - - - - - - - - - - 
Total Apparent Power: 0.30 VA (CT1~CT2~CT3)
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
Calculated Total Apparent Power: 0.31 VA (CT1~CT2~CT3)


Power Factor
─────────────
Power Factor CT1: 0.00 PF
Power Factor CT2: 0.00 PF
Power Factor CT3: 0.00 PF
- - - - - - - - - - - - - - - 
Total Power Factor: 0.00 PF

Phase Angle
────────────
Phase Angle CT1: 0.00
Phase Angle CT2: 47.70
Phase Angle CT3: 0.00

Voltage Harmonics
──────────────────
Voltage Harmonics CT1: 0.00
Voltage Harmonics CT2: 0.00
Voltage Harmonics CT3: 0.00

Current Harmonics
──────────────────
Current Harmonics CT1: 0.00
Current Harmonics CT2: 0.00
Current Harmonics CT3: 0.00


Other Information
──────────────────
Chip Temperature: 28.00 °C

Mains Frequency: 50.04 Hz