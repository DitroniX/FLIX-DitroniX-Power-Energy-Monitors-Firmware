 Dave Williams, DitroniX 2019-2023 (ditronix.net)

NOTE: This original IPEM/IPEC firmware has been renamed to FliX and resides in https://github.com/DitroniX/FLIX-DitroniX-Power-Energy-Monitors-Firmware
  
**Development Code - WORK-IN-PROGRESS - NOT COMPLETE!!!**
Updated 29th November 2023

This firmware (using PlatformIO), has evolved over time and although originally was purely for bring-up testing, it has expanded into much more.  As such, and with the family addition of the IPEC board and IPEX, this firmware has moved away from just IPEM into an integrated development branch - with auto board detect.  This will allow for future expansion.

Due to the nature of this firmware, **FliX** remains under development and Is subject to change, improvements and additions.

**Board Families Supported**

The **FliX** firmware currently supports the below boards:

-   **IPEM IoT Power Energy Monitor**
	- Features include IPEM ESP32 ATM90E32 ATM90E36 16bit ADC 24C64 EEPROM 3Phase 3+1 CT-Clamps Current Voltage Frequency Power Factor GPIO I2C OLED SMPS D1 USB
	- Variants
	    -   IPEM32E-M90E32-INT \| ESP32-WROOM-32E ATM90E32 AT24C64
	    -   IPEM32UE-M90E32-EXT \| ESP32-WROOM-32UE ATM90E32 AT24C64
	    -   IPEM32E-M90E36-INT \| ESP32-WROOM-32E ATM90E36 AT24C64
	    -   IPEM32UE-M90E36-EXT \| ESP32-WROOM-32UE ATM90E36 AT24C64

-   **IPEC IoT Power Energy Controller**
	- Features include IPEC ESP32 ATM90E32 16bit ADC MCP4728 DAC 24C64 EEPROM 3Phase 3 CT-Clamps Current Voltage Frequency Power Factor GPIO I2C OLED SMPS D1 USB.
	-  Variants
	    -   IPEC32E-M90E32-INT \| ESP32-WROOM-32E ATM90E32 MSP4728 AT24C64
	    -   IPEC32UE-M90E32-EXT \| ESP32-WROOM-32UE ATM90E32 AT24C64

-   **IPEX-1 IoT Power Energy Controller Expansion**
	- Variants
	    -   IPEX1-ACS758-ADS1115 \| ACS758 ADS1115 PCA9685

The firmware code can be used to test the boards, development and experimental use, or final use.- all depending on the options enabled/disabled.

**Purpose of Code**

The purpose of this test code is to cycle through the various main functions of the boards, as part of board bring up testing

This software has expanded way past it's original bring-up task and is now quite comprehensive. It can now be, as is, used for both bring-up, final use and publishing. Else, simply use the bits you like!

A number of software switches are used, throughout. The defaults are listed below. You should be able to just compile this current version to an IPEM ATM90E32, or IPEX ATM90E32, and see some valid results in the serial monitor / OLED.

**ATM Overview**
Two version of the ATM90 Series are used.  ATM90E32 and ATM90E36.

Board Bring Up Test - ATM90E3x Test Routines (Output sent to the Serial Print - ONLY ON BOOT! Press RESET or HOLD USR Button to REFRESH)

**Acknowledgements**

Base 90E32/36 register formulation is based on the original excellent ground work from Tisham Dhar, whatnick \| ATM90E32 ATM90E36 Energy Monitor Core. This then being adapted over time where needed.

VSCode / Platform IO base, E32/E36 Registers/Code Merged, Adapted, Updated, Software Logic/Routines, Bring Up Firmware, Comprehensive Functions and Wi-Fi integration such as OTA, Domoticz Integration etc. by Date Williams

**CONFIGURATION** (Setup for bring-up testing of the board)

This version of firmware code is by default, configured for:

- AUTO Configuration of BOARD_FAMILY
- ATM90E32 (ATM90DEVICE ATM90E32_DEVICE) CT4
- Configured to ESP32 ADC (CT4_CONFIG CT4_ESP - Auto Disabled for IPEC)
- CT4 Input - Enabled (CT4_ENABLED true)
- DAC Output. IPEC MCP4728 Port (EnableDACLocal false EnableDACRemote false EnableDACTestOutput false)
- PWM Output (Test Use) on Default GPIO Port GP17 (EnablePWMLocal false EnablePWMRemote false EnablePWMTestOutput false)
- Multi-Voltage Input (ATM_SINGLEVOLTAGE true)
- Split-Phase USA - Disabled (ATM_SPLITPHASE false)
- Display of Board Configuration (EnableDisplayBoardConfiguration true)
- Loop Refreshing Terminal Output (EnableBasicLoop false) - Display Info ONCE uppon Reset.
- Value Outputs are filtered through a Sofware Noise Filter / Comparator / Squelch (EnableNoiseFilterSquelch true)
- OLED 0.96" Display SSD1306 128x32. (EnableOLEDLoop true)
- Board Location and Firmware Version to OLED and Serial Monitor
- Wi-Fi (DisableWiFi false)    Requires SSID/PWD to auto enable
- MQTT Publishing - Disabled (EnableMQTT false)
- Domoticz Publishing - Disabled (EnableDomoticz false)
- ThingSpeak Publishing - Disabled (EnableMQTT false)
- Zabbix Publishing - Disabled (EnableThingSpeak false)
- IP Address Defaults to DHCP. Static IP Address Configuration in WiFi-OTA.h

**CALIBRATION** (This should be minimal - based on the below)

This version of firmware has been setup for ATM90E32 and CT4 to ESP32 ADC.

- Current Clamp default example settings are based on SCT-013-000 100A/50mA.
- Voltages default example settings are based on Single/Three Phase Voltage Inputs from a Greenbrook DAT01A (TC TR7) Transformer, set to 12V AC.
- Current Clamps CT1, CT2 and CT3 are connected to the ATM90E3x. Calibration requirements should be minimal and board ready to use.
- AC Voltage Inputs V1, V2 and V3 are connected to the ATM90E3x. Calibration requirements should be minimal and board ready to use.
- Current Clamp CT4 is connected to the ESP32 ADC1 CH7. Software EmonLib calibratrion may be required.(Auto Disabled for IPEC)
- You can update ATM90Ex calibration (if required), in IPEM_Hardware.h
- You can update board ATM Configurations in ATM90E3x.h
- You can update CT4 calibration in iPEM_Hardware.h - See EmonLib. (Auto Disabled for IPEC)

**WiFi and OTA Updates**

- Setup WiFi
- Configure Multi-WiFi SSID/PWD
-  Setup Optional Static IP address and Gateway (DHCP or Static)
- Setup Preferred Hostname
- Setup Serial Device over IP (Used for OTA)
- Display WiFI Signal Meter
- Web Server Information Page and Push OTA Updater
-  Web Listener
- PWM Switches added: /pwm-local, /pwm-remote, /pwm-on, /pwm-off, /pwm-test
- DAC Switches added: /dac-local, /dac-remote, /dac-on, /dac-off, /dac-test
- Seperate switches dac-remote and pwm-remote, allow you to remotely send a fixed value to pwm / dac output. Ideal for scenes etc. Remote  turns off or over-rides CT for pwm/dac.

**DOMOTICZ**

- Setup connection to Domoticz Home Automation
- Configure Required Values to Publish to Domoticz Hardware Device Indexes
- When Publising to Domoticz - Mute Detailed Output to Serial (Loop)

**MQTT**

- Setup connection to MQTT Broker / Home Automation
- Configure Required Values to Publish to MQTT Broker

**ThingSpeak**

- Example Publish (play data), can be found on https://thingspeak.com/channels/2179490
- Setup easy connection to ThingSpeak Cloud Base Server / Home Automation
	- FREE Cloud Account
	- View on Phone/Web/Tablet/Desktop
	- Configure Required Values to Publish to ThingSpeak

**Zabbix**  (Currently WIP)

- Integration with Zabbix, Agent, Local and Cloud
- Configure Required Values to Publish to Zabbix

**PWM Duty Cycle Output** FOR THE IPEC BRANCH

- PWM (On Default GPIO 17), which will track Power Usage (from Default Variable ActivePowerExportCT1)
- Output Updated on Each DisplayRegisters Loop (Only if Value Changed)
- WebServer /pwm-local, /pwm-remote, /pwm-on, /pwm-off, /pwm-test. See https://github.com/DitroniX/IPEM-IoT-Power-Energy-Monitor/wiki/WebServer-Commands
- Ability to Enable and Disable PWM Local Readings
- Ability to Enable and Disable PWM Remote Readings
- Ability to Enable and Disable PWM Test Mode
- Ability to Set Fixed Power from Remote Value, or Leave to Dynamic CT Power Values (WIP)
- Continuous PWM Cycle Test Mode Loop

**DAC Voltage Output** FOR THE IPEC BRANCH

- Fixed Voltage Output from DAC, tracking Power Usage (from Default Variable ActivePowerExportCT1)
- Output Updated on Each DisplayRegisters Loop (Only if Value Changed)
- WebServer /dac-local, /dac-remote, /dac-on, /dac-off, /dac-test. See https://github.com/DitroniX/IPEM-IoT-Power-Energy-Monitor/wiki/WebServer-Commands
- Ability to Enable and Disable DAC Local Readings
- Ability to Enable and Disable DAC Remote Readings
- Ability to Enable and Disable DAC Test Mode
- Ability to Set Fixed DAC Output from Remote Value, or Leave to Dynamic CT Power Values (WIP)
- DAC Sinewave Test Mode Loop (Default 10 Hz)
- DAC Stepped Voltages Test Mode Loop (Slow Staircase)

Enjoy! Dave Williams, DitroniX.net

**Remember!**

- Set the BOARD to ESP32, 'WEMOS D1 MINI ESP32' DEV Module (or similar).
- You may set the BAUD rate to 921600 to speed up flashing.
- The SDK board does NOT need external power to flash. It will take Power from the USB 5V.
- You can safely connect both USB Power and PSU AC In, at the sme time (Makes development much easier).

**Other Notes**

In the default state, upon first power up and during reset, the Green LED may be partially lit. Once programmed and the GPIO defined, the Green LED will go off after power up.

This test code is OPEN SOURCE and formatted for easier viewing. Although is is not intended for real world use, it may be freely used, or modified as needed.

It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

**Wiki and Code Examples**

Further information, details and code examples can be found on our wiki pages on github.com/DitroniX

- https://github.com/DitroniX
 - https://github.com/DitroniX/IPEM-IoT-Power-Energy-Monitor
 - https://github.com/DitroniX/IPEC-IoT-Power-Energy-Controller
 - https://github.com/DitroniX/IPEX-IoT-Power-Energy-Controller-Expansion-Board
 - https://github.com/DitroniX/EPEM-Ethernet-Power-Energy-Monitor
