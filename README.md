## FliX and FliX PiHat - DitroniX Power Energy Monitors Firmware

Development Test and Bring-up Code - WORK-IN-PROGRESS 

Updated 15th June 2025

Dave Williams, DitroniX 2019-2025 (ditronix.net)

## **FLiX Development Code Variants:**

### FliX

 - **IPEM IoT Power Energy Monitor**

	- Features include IPEM ESP32 ATM90E32 ATM90E36 16bit ADC 24C64 EEPROM 3Phase 3+1 CT-Clamps Current Voltage Frequency Power Factor GPIO I2C OLED SMPS D1 USB
	- Variants
	    -   IPEM32E-M90E32-INT \| ESP32-WROOM-32E ATM90E32 AT24C64
	    -   IPEM32UE-M90E32-EXT \| ESP32-WROOM-32UE ATM90E32 AT24C64
	    -   IPEM32E-M90E36-INT \| ESP32-WROOM-32E ATM90E36 AT24C64
	    -   IPEM32UE-M90E36-EXT \| ESP32-WROOM-32UE ATM90E36 AT24C64

 - **IPEC IoT Power Energy Controller**

	- Features include IPEC ESP32 ATM90E32 16bit ADC MCP4728 DAC 24C64 EEPROM 3Phase 3 CT-Clamps Current Voltage Frequency Power Factor GPIO I2C OLED SMPS D1 USB.
	-  Variants
	    -   IPEC32E-M90E32-INT \| ESP32-WROOM-32E ATM90E32 MSP4728 AT24C64
	    -   IPEC32UE-M90E32-EXT \| ESP32-WROOM-32UE ATM90E32 AT24C64

 - **IPEX-1 IoT Power Energy Controller Expansion**

	- Variants
	    -   IPEX1-ACS758-ADS1115 \| ACS758 ADS1115 PCA9685 

### FliX PiHat

- **IPEM PiHat** 
	- with ATM90E36 with ESP32, or ESP32-C6 (ESPuno Pi Zero), Interposer
- **IPEM PiHat Lite** 
	- with ATM90E36 with ESP32, or ESP32-C6 (ESPuno Pi Zero), Interposer
- **IPEM (also Supports)** 
	- IPEM32E-M90E36-INT \| ESP32-WROOM-32E ATM90E36 AT24C64
	- IPEM32UE-M90E36-EXT \| ESP32-WROOM-32UE ATM90E36 AT24C64

## SDK Boards

 - The **[IPEM](https://github.com/DitroniX/IPEM-IoT-Power-Energy-Monitor)** and **[IPEC](https://github.com/DitroniX/IPEC-IoT-Power-Energy-Controller)** Development Code contains a number of features, which may be either used purely for development, a basis for your own firmware, or with features enabled (via software switches), provide a complete firmware solution, publishing to the outside World.

 - The **[IPEM PiHat](https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor)** and **[IPEM PiHat Lite](https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor)** boards are directed towards the Raspberry Pi series 
	 - Due to the ease of interfacing and in order to exercise and fully test these, I took a version of FLiX and made a number of changes in order to drive these newer boards via an ESP32/ESP32-C6 Interposer. 

This firmware has evolved over time and although originally was purely for bring-up testing, it has expanded into much more. It has developed way past its original bring-up task and is now quite comprehensive.  It is though, still work in progress and free to be adapted and used.

This test code is OPEN SOURCE and formatted for easier viewing. It may be freely used, or modified as needed. You may use as is, use for bring-up development, simply use the bits you like! final use and for full IoT publishing. It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

## **FLiX Updates**
  - 250615 - Updated ESPAsyncWebServer due to library changes.
	 -  Removed: me-no-dev/ESP Async WebServer @ ^1.2.3
	 -  Added: esp32async/ESPAsyncWebServer@^3.7.8
	 -  Disabled PWM.  Requires updating
	 -  Version: 250112 to 250615
  - 250112 - Tweaks
  - 250111 - Main  Release.  
	 -  Supports ATM90E32
	 -  Supports ATM90E36
	 -  Major housekeeping
	 -  Register and function updates for ATM90E36
	 -  Various Bug fixes
	 -  Japan Voltage Support
	 -  Voltage and Current Harmonics
  - 231129 - Beta Release Primarily for the ATM09E32 with basic ATM90E36 support.

## **FLiX PiHat Updates**
  - 250615 - Beta version being tested prior to upload
  - 250601 - Beta Release being tested on updated ESPuno Pi Zero boards
  - 250407 - Internal preparation for **FLiX PiHat** (For IPEM PiHat and  IPEM PiHat Lite boards)
	 -  Supports only ATM90E36
	 -  Supports IPEM PiHats via ESP32 Interposer
	 -  Beta Release to GitHub delayed due to wanting to test on the preproduction ESPuno Pi Zero



**Board Selection**

With the family addition of the [IPEC](https://github.com/DitroniX/IPEC-IoT-Power-Energy-Controller) board and [IPEX](https://github.com/DitroniX/IPEX-IoT-Power-Energy-Controller-Expansion-Board) Expansion, the original firmware has moved away from just [IPEM](https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor) into an integrated development branch - with auto board detect. This will allow for future expansion and system integration.

The **FliX** firmware currently supports the below board variants:

-   **IPEM IoT Power Energy Monitor**
    -   IPEM32E-M90E32-INT \| ESP32-WROOM-32E ATM90E32 AT24C64
    -   IPEM32UE-M90E32-EXT \| ESP32-WROOM-32UE ATM90E32 AT24C64
    -   IPEM32E-M90E36-INT \| ESP32-WROOM-32E ATM90E36 AT24C64
    -   IPEM32UE-M90E36-EXT \| ESP32-WROOM-32UE ATM90E36 AT24C64
-   **IPEC IoT Power Energy Controller**
    -   IPEC32E-M90E32-INT \| ESP32-WROOM-32E ATM90E32 MSP4728 AT24C64
    -   IPEC32UE-M90E32-EXT \| ESP32-WROOM-32UE ATM90E32 AT24C64
-   **IPEX-1 IoT Power Energy Controller Expansion**
    -   IPEX1-ACS758-ADS1115 \| ACS758 ADS1115 PCA9685

The **FliX PiHat** beta firmware currently supports the below board variants:

   -   **[IPEM PiHat](https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor)** ATM90E36 via ESP32 Interposer.  WIP: ADC, DAC, RTC, Stacking.
   -   **[IPEM PiHat Lite](https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor)** ATM90E36 via ESP32 Interposer.  WIP: ADC, DAC, RTC, Stacking.

**Continual Development**

Due to the nature of this firmware, all variants of FLiX remain under development and is subject to change, improvements and additions.

During any development, the firmware is carefully tested on the range of supported boards. However, should you notice a gremlin, please feel free to let us know!

**Acknowledgements**

Base 90E32/36 register formulation is based on the original excellent ground work from Tisham Dhar, whatnick \| ATM90E32 ATM90E36 Energy Monitor Core. This then being adapted over time where needed.

VSCode / Platform IO base, E32/E36 Registers/Code Merged, Adapted, Updated, Software Logic/Routines, Bring Up Firmware, Comprehensive Functions and Wi-Fi integration such as OTA, Domoticz Integration etc. by Date Williams.

## **Further Information**

Additional information, and other technical details on this project, maybe found in the related repository pages.

**Repository Folders**

 - **Code** *(Code examples for Arduino  IDE and PlatformIO)*
 -  **Datasheets and Information** *(Component Datasheets, Schematics, Board Layouts, Photos, Technical Documentation)*
 - **Certification** *(Related Repository Project or Part, Certification Information)*

**Repository Tabs**

 - **Wiki** *(Related Repository Wiki pages and Technical User Information)*
 - **Discussions** *(Related Repository User Discussion Forum)*
 - **Issues** *(Related Repository Technical Issues and Fixes)*

***

We value our Customers, Users of our designs and STEM Communities, all over the World . Should you have any other questions, or feedback to share to others, please feel free to:

* Visit the related [Project](https://github.com/DitroniX?tab=repositories) *plus the related* **Discussions** and **Wiki** Pages.  See tab in each separate repository.
* **Project Community Information** can be found at https://www.hackster.io/DitroniX
* [DitroniX.net Website - Contact Us](https://ditronix.net/contact/)
* **Twitter**: [https://twitter.com/DitroniX](https://twitter.com/DitroniX)
* [Supporting the STEM Projects - BuyMeACoffee](https://www.buymeacoffee.com/DitroniX)
*  **LinkedIN**: [https://www.linkedin.com/in/g8puo/](https://www.linkedin.com/in/g8puo/)

***Dave Williams, Maidstone, UK.***

Electronics Engineer | Software Developer | R&D Support | RF Engineering | Product Certification and Testing | STEM Ambassador

## STEM

**Supporting [STEM Learning](https://www.stem.org.uk/)**

Life is one long exciting learning curve, help others by setting the seed to knowledge.

![DitroniX Supporting STEM](https://hackster.imgix.net/uploads/attachments/1606838/stem_ambassador_-_100_volunteer_badge_edxfxlrfbc1_bjdqharfoe1_xbqi2KUcri.png?auto=compress%2Cformat&w=540&fit=max)



