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
 * Hex 0x68 (104)        DS3231SN Accurate RTC
 I2C Bus Scan Complete

IPEM Plus R&D IoT Power Energy Monitor Controller

IPEM Plus R&D Register Status and Startup Report
ESP32-C5 Serial ID: 83FFFE75DC3C
FLiX Lite for IPEM Plus - Firmware Version: 260527
Board Location: Test

Wi-Fi Options
──────────────

Software Options
─────────────────
Connecting to the ATM90E36
====================================
ATM90E36 Connected - OK

IPEM Plus R&D Hardware Setup and Power-Up Test - Board Initialized

IPEM Plus R&D IoT Power Energy Monitor Controller

IPEM Plus R&D Register Status and Startup Report
ESP32-C5 Serial ID: 83FFFE75DC3C
FLiX Lite for IPEM Plus - Firmware Version: 260527
Location: Test

Hardware Configuration for ATM90E36
────────────────────────────────────
AC Voltage Inputs:      Single Input V1 will be used for Current Phase Calculations
Split AC Voltage:       Dual  or Split Voltage Input Disabled
CT Current Clamps:      Configured for 1, 2, 3 Phase

[Status Values]
System Status:          S0:0xC0         S1:0xC
Meter Status:           E0:0x5          E1:0x0

Mains RMS Voltage
──────────────────
- - - - - - - - - - - - - - - - - - - - - - - - - - - 
Voltage 1: 243.74 V (Single Line Voltage Selected)

Mains RMS Current
──────────────────
Current CT1: 1.37 A
Current CT2: 0.00 A
Current CT3: 0.00 A
Current CTN: 1.37 A
- - - - - - - - - - - - - - - - - - - - - - - 
Actual Total Current: 1.37 A (CT1~CT2~CT3)

Calculated RMS Power
─────────────────────
Power V1*I1: 333.92 W   0.33 kW
Power V1*I2: 0.00 W     0.00 kW
Power V1*I3: 0.00 W     0.00 kW
Power V1*I4: 0.00 W
- - - - - - - - - - - - - - - - - - - - - - - - - 
Calculated Total Power: 333.92 W (CT1~CT2~CT3)

Active Power (Absorbed or Used by the Load)
────────────────────────────────────────────
Active Power CT1: -0.34 kW      (Export)
Active Power CT2: 0.00 kW 
Active Power CT3: 0.00 kW 
- - - - - - - - - - - - - - - - - - - - - 
Total Active Power: -0.34 kW    (Export)
- - - - - - - - - - - - - - - - - - - - - - - - - - - - 
Calculated Total Active Power: -0.34 W (CT1~CT2~CT3)

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
Apparent Power CT1: 0.33 VA
Apparent Power CT2: 0.00 VA
Apparent Power CT3: 0.00 VA
- - - - - - - - - - - - - - - - - - - - - - - 
Total Apparent Power: 0.33 VA (CT1~CT2~CT3)
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
Calculated Total Apparent Power: 0.33 VA (CT1~CT2~CT3)


Power Factor
─────────────
Power Factor CT1: 0.00 PF
Power Factor CT2: 0.00 PF
Power Factor CT3: 0.03 PF
- - - - - - - - - - - - - - - 
Total Power Factor: 0.00 PF

Phase Angle
────────────
Phase Angle CT1: 0.00
Phase Angle CT2: 95.00
Phase Angle CT3: 3.40

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
Chip Temperature: 25.00 °C

Mains Frequency: 50.13 Hz
