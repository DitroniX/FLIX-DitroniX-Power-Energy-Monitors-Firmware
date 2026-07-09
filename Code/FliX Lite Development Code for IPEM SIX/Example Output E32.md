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

IPEM SIX IoT Power Energy Monitor Controller

IPEM SIX Register Status and Startup Report
ESP32-C5 Serial ID: 83FFFE75DC3C
FLiX Lite for IPEM SIX - Firmware Version: 260709
Board Location: Test

Wi-Fi Options
──────────────

Software Options
─────────────────
Connecting to the ATM90E32
====================================
ATM90E32 Connected - OK

IPEM SIX Hardware Setup and Power-Up Test - Board Initialized

IPEM SIX IoT Power Energy Monitor Controller

IPEM SIX Register Status and Startup Report
ESP32-C5 Serial ID: 83FFFE75DC3C
FLiX Lite for IPEM SIX - Firmware Version: 260709
Location: Test

Hardware Configuration for ATM90E32
────────────────────────────────────
AC Voltage Inputs:      Single Input V1 will be used for Current Phase Calculations
Split AC Voltage:       Dual  or Split Voltage Input Disabled
CT Current Clamps:      Configured for 1, 2, 3 Phase

[Status Values]
System Status:          S0:0x370                S1:0x8000
Meter Status:           E0:0x300                E1:0x0

Dual ATM90E32 - Only ONE is tested
───────────────────────────────────
Note that only ONE of the ATM90E32AS circuits is tested in this bring up application.

This confirms calibration and SPI communications

Mains RMS Voltage
──────────────────
- - - - - - - - - - - - - - - - - - - - - - - - - - - 
Voltage 1: 241.69 V (Single Line Voltage Selected)

Mains RMS Current
──────────────────
Current CT1: 1.28 A
Current CT2: 0.00 A
Current CT3: 0.00 A
- - - - - - - - - - - - - - - - - - - - - - - 
Actual Total Current: 1.28 A (CT1~CT2~CT3)

Calculated RMS Power
─────────────────────
Power V1*I1: 309.36 W   0.31 kW
Power V1*I2: 0.00 W     0.00 kW
Power V1*I3: 0.00 W     0.00 kW
- - - - - - - - - - - - - - - - - - - - - - - - - 
Calculated Total Power: 309.36 W (CT1~CT2~CT3)

Active Power (Absorbed or Used by the Load)
────────────────────────────────────────────
Active Power CT1: 307.95 W      (Import)
Active Power CT2: 0.00 W 
Active Power CT3: 0.00 W 
- - - - - - - - - - - - - - - - - - - - - 
Total Active Power: 307.96 W    (Import)
- - - - - - - - - - - - - - - - - - - - - - - - - - - - 
Calculated Total Active Power: 307.95 W (CT1~CT2~CT3)

Re-Active Power
────────────────
ReActive Power CT1: 18.11 VAR
ReActive Power CT2: 0.00 VAR
ReActive Power CT3: 0.04 VAR
- - - - - - - - - - - - - - - - - - - - - - - - 
Total ReActive Power: 18.14 VAR (CT1~CT2~CT3)
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
Calculated Total Reactive Power: 18.15 W (CT1~CT2~CT3)

Apparent Power (Total Amount of Power Flowing from Source to Load)
───────────────────────────────────────────────────────────────────
Apparent Power CT1: 308.40 VA
Apparent Power CT2: 0.44 VA
Apparent Power CT3: 0.44 VA
- - - - - - - - - - - - - - - - - - - - - - - - 
Total Apparent Power: 308.82 VA (CT1~CT2~CT3)
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
Calculated Total Apparent Power: 309.28 VA (CT1~CT2~CT3)


Other Power Information
────────────────────────
Total Fundamental Power: 307.57 pH(t)

Total Harmonic Power: 0.37 
Power Factor
─────────────
Power Factor CT1: 1.00 PF
Power Factor CT2: 0.00 PF
Power Factor CT3: 0.06 PF
- - - - - - - - - - - - - - - 
Total Power Factor: 1.00 PF

Phase Angle
────────────
Phase Angle CT1: 3.30
Phase Angle CT2: 0.00
Phase Angle CT3: 0.00

Other Information
──────────────────
Chip Temperature: 33.00 °C

Mains Frequency: 50.02 Hz