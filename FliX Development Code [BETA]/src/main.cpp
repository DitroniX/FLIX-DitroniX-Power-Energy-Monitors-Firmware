/*
  Dave Williams, DitroniX 2019-2023 (ditronix.net)
  Full header information in README

  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  Further information, details and examples can be found on our website wiki pages ditronix.net/wiki and also github.com/DitroniX
*/

// Libraries
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <driver/adc.h>
#include <ATM90E3x.h>
#include <Hardware.h>
#include <WiFi-OTA.h>
#include <Domoticz.h>
#include <MQTT.h>
#include <Zabbix.h>

// USER VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS -> Moved to IPEM_Hardware

// **************** FUNCTIONS AND ROUTINES ****************

// Return Register Values from the ATM90E32, or ATM90E36, - and Display
void DisplayRegisters(boolean DisplayFull = true)
{
  // PWM DutyCycle Output Pending Power Value. Test Usage: PWM_Power(2000)
  if (EnablePWMLocal == true && EnablePWMRemote == false && EnablePWMTestOutput == false)
  {
    PWM_Power(ActivePowerImportCT1); // Import use for Testing Only
                                     //  PWM_Power(ActivePowerExportCT1);
  }
  if (EnablePWMLocal == false && EnablePWMRemote == true && EnablePWMTestOutput == false)
  {
    PWM_Power(PWMRemotePower);
  }

  // DAC Voltage Output Pending Power Value. Test Usage: DAC_Power(2000)
  if (EnableDACLocal == true && EnableDACRemote == false && EnableDACTestOutput == false && EnableIPEM == false)
  {
    if (ActivePowerExportCT1 >= DAC_PowerThreshold)
    {
      // DAC_WritePower(ActivePowerImportCT1); // Import use for Testing Only
      DAC_WritePower(ActivePowerExportCT1);
    }
    else
      DAC_SetOff();
  }

  if (EnableDACLocal == false && EnableDACRemote == true && EnableDACTestOutput == false && EnableIPEM == false)
  {
    DAC_WritePower(DACRemotePower);
  }

  // if (DisplayFull == false) // Display Expanded Information
  //   Serial.println("\nDisplay Output (DisplayRegisters false), Set to Minimised");

  // Display Board Configuration
  if (EnableDisplayBoardConfiguration == true && DisplayFull == true)
    DisplayBoardConfiguration();

  // **************** VOLTAGE ****************

  // Get Mains Voltages
  LineVoltage1 = NoiseFilterSquelch(eic.GetLineVoltage1(), 1);
  LineVoltage2 = NoiseFilterSquelch(eic.GetLineVoltage2(), 1);
  LineVoltage3 = NoiseFilterSquelch(eic.GetLineVoltage3(), 1);
  LineVoltageAverage = 0;
  LineVoltageTotal = 0;

// Calculate Voltage
#if ATM_SINGLEVOLTAGE == true && ATM_SPLITPHASE == true
  Serial.println("* SOFTWARE CONFIGURATION ERROR *\n* You cannot have ATM_SINGLEVOLTAGE and ATM_SPLITPHASE, both Enabled.\n");
#else
#if ATM_SPLITPHASE == true
  LineVoltageTotal = (LineVoltage1 + LineVoltage3) / 2; // Split Single Phase configured, so only 120V per leg
#else
  LineVoltageAverage = (LineVoltage1 + LineVoltage2 + LineVoltage3) / 3; // Voltage should be around 110V, or 220-240, at the AC transformer primary.
#endif
#endif

  if (DisplayFull == true) // Display Expanded Information
  {

    // Mains RMS Voltage
    PrintUnderline("Mains RMS Voltage");

#if ATM_SINGLEVOLTAGE == false

    Serial.println("Voltage 1: " + String(LineVoltage1) + " V");

#if ATM_SPLITPHASE == false
    Serial.println("Voltage 2: " + String(LineVoltage2) + " V");
#endif

    Serial.println("Voltage 3: " + String(LineVoltage3) + " V");

#if ATM_SPLITPHASE == true
    PrintSeparator("Total Split Voltage: " + String(LineVoltageTotal) + " V (V1~X~V3)");
#else
    PrintSeparator("Average Voltage: " + String(LineVoltageAverage) + " V (V1~V2~V3)");
#endif

#else
    PrintSeparator("Voltage 1: " + String(LineVoltage1) + " V (Single Line Voltage Selected)");
#endif
  }

  // **************** CURRENT ****************

  // Get Total Current.  Ignore CT2 if Split Phase
  LineCurrentCT1 = NoiseFilterSquelch(eic.GetLineCurrentCT1());
#if ATM_SPLITPHASE == false
  LineCurrentCT2 = NoiseFilterSquelch(eic.GetLineCurrentCT2());
#else
  LineCurrentCT2 = 0;
#endif
  LineCurrentCT3 = NoiseFilterSquelch(eic.GetLineCurrentCT3());

  // Using ESP32 ADC for CT4 Current Input - if (EnableIPEM == true)

#if ATM90DEVICE == ATM90E32_DEVICE || CT4_CONFIG == CT4_ESP
  if (EnableIPEM == true)
    ReadCT4Current();
#if CT4_ENABLED == true
  if (EnableIPEM == true)
    LineCurrentTotal = NoiseFilterSquelch(LineCurrentCT1 + LineCurrentCT2 + LineCurrentCT3 + LineCurrentCT4);
#else
  LineCurrentTotal = NoiseFilterSquelch(LineCurrentCT1 + LineCurrentCT2 + LineCurrentCT3);
#endif
#else
  LineCurrentTotal = NoiseFilterSquelch(LineCurrentCT1 + LineCurrentCT2 + LineCurrentCT3);
#endif

// E36 Using I4N Input for Current
#if ATM90DEVICE == ATM90E36_DEVICE && CT4_CONFIG == CT4_ATM
  if (EnableIPEM == true)
  {
    LineCurrentCTN = NoiseFilterSquelch(eic.GetLineCurrentCTN());
    LineCurrentTotal = NoiseFilterSquelch(LineCurrentCT1 + LineCurrentCT2 + LineCurrentCT3);
  }
#endif

  if (DisplayFull == true) // Display Expanded Information
  {
    Serial.println("");

    // Mains RMS Current
    PrintUnderline("Mains RMS Current");
    Serial.println("Current CT1: " + String(LineCurrentCT1) + " A");

#if ATM_SPLITPHASE == false
    Serial.println("Current CT2: " + String(LineCurrentCT2) + " A");
#endif

    Serial.println("Current CT3: " + String(LineCurrentCT3) + " A");

#if ATM90DEVICE == ATM90E32_DEVICE && CT4_ENABLED == true || CT4_CONFIG == CT4_ESP && CT4_ENABLED == true
    if (EnableIPEM == true)
      Serial.println("Current CT4: " + String(LineCurrentCT4) + " A (ESP ADC1 CH7)");
#endif

#if ATM90DEVICE == ATM90E36_DEVICE && CT4_CONFIG == CT4_ATM
    if (EnableIPEM == true)
      Serial.println("Current CTN: " + String(LineCurrentCTN) + " A");
#endif

#if ATM_SPLITPHASE == true
    Serial.println("Actual Total Current: " + String(LineCurrentTotal) + " A (CT1~X~CT3)");
#else
#if CT4_ENABLED == true
    if (EnableIPEM == true)
      PrintSeparator("Actual Total Current: " + String(LineCurrentTotal) + " A (CT1~CT2~CT3~CT4)");
#else
    PrintSeparator("Actual Total Current: " + String(LineCurrentTotal) + " A (CT1~CT2~CT3)");
#endif
#endif

    Serial.println("");
  }

  // **************** POWER ****************

  // Calculated Power CT2ased on V*I
#if ATM_SINGLEVOLTAGE == true // Single Mains Voltage for all Current Measurements
  CalculatedPowerCT1 = LineVoltage1 * LineCurrentCT1;
  CalculatedPowerCT2 = LineVoltage1 * LineCurrentCT2;
  CalculatedPowerCT3 = LineVoltage1 * LineCurrentCT3;

#if ATM90DEVICE == ATM90E36_DEVICE
  if (EnableIPEM == true)
    CalculatedPowerCT4 = LineVoltage1 * LineCurrentCT4;
#endif

  if (DisplayFull == true) // Display Expanded Information
  {
    PrintUnderline("Calculated RMS Power");
    Serial.println("Power V1*I1: " + String(CalculatedPowerCT1) + " W");
    Serial.println("Power V1*I2: " + String(CalculatedPowerCT2) + " W");
    Serial.println("Power V1*I3: " + String(CalculatedPowerCT3) + " W");

#if ATM90DEVICE == ATM90E36_DEVICE && CT4_ENABLED == true
    if (EnableIPEM == true)
      Serial.println("Power V1*I4: " + String(CalculatedPowerCT4) + " W");
#endif
  }
#else // Seperate Mains Voltages for Current Measurements
  CalculatedPowerCT1 = LineVoltage1 * LineCurrentCT1;
  CalculatedPowerCT2 = LineVoltage2 * LineCurrentCT2;
  CalculatedPowerCT3 = LineVoltage3 * LineCurrentCT3;

#if ATM90DEVICE == ATM90E36_DEVICE
  if (EnableIPEM == true)
    CalculatedPowerCT4 = LineVoltage1 * LineCurrentCT4; // ESP32 ADC1 CH7 using V1
#endif

  if (DisplayFull == true) // Display Expanded Information
  {
    PrintUnderline("Calculated RMS Power");
    Serial.println("Power V1*I1: " + String(CalculatedPowerCT1) + " W");
    Serial.println("Power V2*I2: " + String(CalculatedPowerCT2) + " W");
    Serial.println("Power V3*I3: " + String(CalculatedPowerCT3) + " W");
  }
#if CT4_ENABLED == true && ATM90DEVICE == ATM90E36_DEVICE
  if (DisplayFull == true && EnableIPEM == true) // Display Expanded Information
  {
    Serial.println("Power V1*I4: " + String(CalculatedPowerCT4) + " W");
  }
#endif
#endif

// Calculate Total Watts
#if ATM_SPLITPHASE == true // USA 120+120
  CalculatedTotalPower = (LineVoltage1 * LineCurrentCT1) + (LineVoltage3 * LineCurrentCT3);

  if (DisplayFull == true) // Display Expanded Information
    PrintSeparator("Calculated Total Power: " + String(CalculatedTotalPower) + " W (CT1~X~CT3)");
#else // World
#if CT4_CONFIG == CT4_ESP && CT4_ENABLED == true
  if (EnableIPEM == true)
    CalculatedTotalPower = (LineVoltage1 * LineCurrentCT1) + (LineVoltage2 * LineCurrentCT2) + (LineVoltage3 * LineCurrentCT3) + (LineVoltage1 * LineCurrentCT4);

  if (DisplayFull == true) // Display Expanded Information
    PrintSeparator("Calculated Total Power: " + String(CalculatedTotalPower) + " W (CT1~CT2~CT3~CT4)");
#else
  CalculatedTotalPower = (LineVoltage1 * LineCurrentCT1) + (LineVoltage2 * LineCurrentCT2) + (LineVoltage3 * LineCurrentCT3);

  if (DisplayFull == true) // Display Expanded Information
    PrintSeparator("Calculated Total Power: " + String(CalculatedTotalPower) + " W (CT1~CT2~CT3)");
#endif
#endif

  if (DisplayFull == true) // Display Expanded Information
    Serial.println("");

  // Active Power.  Extra Import/Export values included to provide added detail for Home Automation logging
  String ActiveFlag = "";

  if (DisplayFull == true) // Display Expanded Information
    PrintUnderline("Active Power (Absorbed or Used by the Load)");

  // Active Power CT1 - Always a Postive Number
  ActivePowerCT1 = NoiseFilterSquelch(eic.GetActivePowerCT1(), 0.2);
  ActivePowerImportCT1 = 0;
  ActivePowerExportCT1 = 0;
  ActiveFlag = "";

  if (ActivePowerCT1 > 0)
  {
    ActivePowerImportCT1 = ActivePowerCT1;
    ActiveFlag = "(Import)";
  }

  if (ActivePowerCT1 < 0)
  {
    ActivePowerExportCT1 = -ActivePowerCT1;
    ActiveFlag = "(Export)";
  }

  if (DisplayFull == true) // Display Expanded Information
    Serial.println("Active Power CT1: " + String(ActivePowerCT1) + " W \t" + ActiveFlag);

  // Active Power CT2 - Always a Postive Number
  ActivePowerCT2 = NoiseFilterSquelch(eic.GetActivePowerCT2(), 0.2);
  ActivePowerImportCT2 = 0;
  ActivePowerExportCT2 = 0;
  ActiveFlag = "";

  if (ActivePowerCT2 > 0)
  {
    ActivePowerImportCT2 = ActivePowerCT2;
    ActiveFlag = "(Import)";
  }

  if (ActivePowerCT2 < 0)
  {
    ActivePowerExportCT2 = -ActivePowerCT2;
    ActiveFlag = "(Export)";
  }
  if (DisplayFull == true) // Display Expanded Information
    Serial.println("Active Power CT2: " + String(ActivePowerCT2) + " W \t" + ActiveFlag);

  // Active Power CT3 - Always a Postive Number
  ActivePowerCT3 = NoiseFilterSquelch(eic.GetActivePowerCT3(), 0.2);
  ActivePowerImportCT3 = 0;
  ActivePowerExportCT3 = 0;
  ActiveFlag = "";

  if (ActivePowerCT3 > 0)
  {
    ActivePowerImportCT3 = ActivePowerCT3;
    ActiveFlag = "(Import)";
  }

  if (ActivePowerCT3 < 0)
  {
    ActivePowerExportCT3 = -ActivePowerCT3;
    ActiveFlag = "(Export)";
  }

  if (DisplayFull == true) // Display Expanded Information
    Serial.println("Active Power CT3: " + String(ActivePowerCT3) + " W \t" + ActiveFlag);

  // Total Active Power C@T
  TotalActivePower = NoiseFilterSquelch(eic.GetTotalActivePower(), 0.2);
  ActiveFlag = "";

  TotalActivePowerImport = ((TotalActivePower > 0) ? TotalActivePower : 0);
  TotalActivePowerExport = ((TotalActivePower < 0) ? -TotalActivePower : 0);
  ActiveFlag = ((TotalActivePower > 0) ? "(Import)" : ((TotalActivePower < 0) ? "(Export)" : "(ZERO)"));

  CalculatedTotalActivePower = (ActivePowerCT1 + ActivePowerCT2 + ActivePowerCT3);

  if (DisplayFull == true) // Display Expanded Information
  {
    PrintSeparator("Total Active Power: " + String(TotalActivePower) + " W \t" + ActiveFlag);
    PrintSeparator("Calculated Total Active Power: " + String(CalculatedTotalActivePower) + " W (CT1~CT2~CT3)");
    Serial.println("");
  }

  // Re-Active Power
  ReactivePowerCT1 = NoiseFilterSquelch(eic.GetReactivePowerCT1());
  ReactivePowerCT2 = NoiseFilterSquelch(eic.GetReactivePowerCT2());
  ReactivePowerCT3 = NoiseFilterSquelch(eic.GetReactivePowerCT3());
  TotalReactivePower = NoiseFilterSquelch(eic.GetTotalReactivePower());
  CalculatedTotalReactivePower = (ReactivePowerCT1 + ReactivePowerCT2 + ReactivePowerCT3);

  if (DisplayFull == true) // Display Expanded Information
  {
    PrintUnderline("Re-Active Power");
    Serial.println("ReActive Power CT1: " + String(ReactivePowerCT1) + " VAR");
    Serial.println("ReActive Power CT2: " + String(ReactivePowerCT2) + " VAR");
    Serial.println("ReActive Power CT3: " + String(ReactivePowerCT3) + " VAR");
    PrintSeparator("Total ReActive Power: " + String(TotalReactivePower) + " VAR (CT1~CT2~CT3)");

    PrintSeparator("Calculated Total Reactive Power: " + String(CalculatedTotalReactivePower) + " W (CT1~CT2~CT3)");
    Serial.println("");
  }

  // Apparent Power Flowing - Voltage and Current (V * I)
  ApparentPowerCT1 = NoiseFilterSquelch(eic.GetApparentPowerCT1());
  ApparentPowerCT2 = NoiseFilterSquelch(eic.GetApparentPowerCT2());
  ApparentPowerCT3 = NoiseFilterSquelch(eic.GetApparentPowerCT3());
  TotalApparentPower = NoiseFilterSquelch(eic.GetTotalApparentPower());
  CalculatedTotalApparentPower = (ApparentPowerCT1 + ApparentPowerCT2 + ApparentPowerCT3);

  if (DisplayFull == true) // Display Expanded Information
  {
    PrintUnderline("Apparent Power (Total Amount of Power Flowing from Source to Load)");
    Serial.println("Apparent Power CT1: " + String(ApparentPowerCT1) + " VA");
    Serial.println("Apparent Power CT2: " + String(ApparentPowerCT2) + " VA");
    Serial.println("Apparent Power CT3: " + String(ApparentPowerCT3) + " VA");
    PrintSeparator("Total Apparent Power: " + String(TotalApparentPower) + " VA (CT1~CT2~CT3)");

    PrintSeparator("Calculated Total Apparent Power: " + String(CalculatedTotalApparentPower) + " W (CT1~CT2~CT3)");
    Serial.println("\n");
  }

#if ATM90DEVICE == ATM90E32_DEVICE
  if (DisplayFull == true) // Display Expanded Information
    PrintUnderline("Other Power Information");

  // Total Fundamental Power
  TotalActiveFundPower = NoiseFilterSquelch(eic.GetTotalActiveFundPower());
  if (DisplayFull == true) // Display Expanded Information
    Serial.println("Total Fundamental Power: " + String(TotalActiveFundPower) + " pH(t)\n");

  // Total Harmonic Power
  TotalActiveHarPower = NoiseFilterSquelch(eic.GetTotalActiveHarPower());
  if (DisplayFull == true) // Display Expanded Information
    Serial.println("Total Harmonic Power: " + String(TotalActiveHarPower) + " ");

#endif

  if (DisplayFull == true)
    Serial.println("");

  // **************** OTHER ****************

  // Power Factor
  PowerFactorCT1 = NoiseFilterSquelch(eic.GetPowerFactorCT1(), 0.01, false);
  PowerFactorCT2 = NoiseFilterSquelch(eic.GetPowerFactorCT2(), 0.01, false);
  PowerFactorCT3 = NoiseFilterSquelch(eic.GetPowerFactorCT3(), 0.01, false);
  TotalPowerFactor = NoiseFilterSquelch(eic.GetTotalPowerFactor(), 0, false);

  if (DisplayFull == true) // Display Expanded Information
  {
    PrintUnderline("Power Factor");
    Serial.println("Power Factor CT1: " + String(PowerFactorCT1) + " PF");
    Serial.println("Power Factor CT2: " + String(PowerFactorCT2) + " PF");
    Serial.println("Power Factor CT3: " + String(PowerFactorCT3) + " PF");
    PrintSeparator("Total Power Factor: " + String(TotalPowerFactor) + " PF");
    Serial.println("");
  }

  // Phase Angle
  PhaseAngleCT1 = NoiseFilterSquelch(eic.GetPhaseCT1(), 0, true, 180);
  PhaseAngleCT2 = NoiseFilterSquelch(eic.GetPhaseCT2(), 0, true, 180);
  PhaseAngleCT3 = NoiseFilterSquelch(eic.GetPhaseCT3(), 0, true, 180);

  if (DisplayFull == true) // Display Expanded Information
  {
    PrintUnderline("Phase Angle");
    Serial.println("Phase Angle CT1: " + String(PhaseAngleCT1));
    Serial.println("Phase Angle CT2: " + String(PhaseAngleCT2));
    Serial.println("Phase Angle CT3: " + String(PhaseAngleCT3));
    Serial.println("");
  }

  if (DisplayFull == true) // Display Expanded Information
    PrintUnderline("Other Information");

  // Chip Temperature
  ChipTemperature = NoiseFilterSquelch(eic.GetTemperature());

  if (DisplayFull == true) // Display Expanded Information
    Serial.println("Chip Temperature: " + String(ChipTemperature) + " °C\n");

  // Line Frequency
  LineFrequency = NoiseFilterSquelch(eic.GetFrequency());

  if (DisplayFull == true) // Display Expanded Information
    Serial.println("Mains Frequency: " + String(LineFrequency) + " Hz\n");

  // Read PCB NTC Temperature
  if (DisplayFull == true && EnableIPEM == true)
  {
    ReadPCBTemperature(); // Read PCB NTC Temperature
    Serial.println("");
  }

  // Read PCB DCV_IN Voltage
  if (DisplayFull == true)
    ReadADCVoltage(); // Read AC>DC Input Voltage
}

// Display WiFI Status OLED
void DisplayOLEDWiFiStatus()
{
  // Firmware Version / Board Location - Display on OLED
  if (OLED_Enabled == true && EnableOLEDLoop == true)

  {

    // WiFi Connection Status - Display on OLED
    oled.clear();
    OLEDPrint(AppAcronym, 2, 0);
    OLEDPrint(LocationName, 2, 2);
    oled.update();
    delay(2000);

    oled.clear();
    OLEDPrint("Wi-Fi AP", 2, 0);
    if (WiFi.status() == WL_CONNECTED)
    {
      OLEDPrint("SSID:" + String(WiFi.SSID()), 1, 2);
      OLEDPrint(String(WiFi.RSSI()) + "dBm " + RSSI_Info(WiFi.RSSI()), 1, 3);
    }
    else
    {
      OLEDPrint("Not Connected", 1, 2);
      if (DisableWiFi == true)
      {
        OLEDPrint("Wi-Fi Force Disabled", 1, 3);
      }
    }

    oled.update();
    delay(2000);

    if (DisableWiFi == false && WiFi.status() == WL_CONNECTED)
    {
      oled.clear();
      OLEDPrint("Wi-Fi IP", 2, 0);
      if (WiFi.status() == WL_CONNECTED)
      {
        OLEDPrint(WiFi.localIP().toString().c_str(), 1, 2);
        OLEDPrint("Host:" + String(WiFi.getHostname()), 1, 3);
      }

      oled.update();
      delay(2000);
    }
  }
} // DisplayOLEDWiFiStatus

// **************** SETUP ****************
void setup()
{

  // Stabalise
  delay(250);

  // Initialise UART
  Serial.begin(115200, SERIAL_8N1); // 115200
  // Serial.begin();
  while (!Serial)
    ;
  Serial.println("");

  Serial.println("FliX - Integrated Firmware for DitroniX Power Energy Monitor SDK Boards\n");

  // Board Port Configuration
  ConfigureBoard();

  // Display Wi-Fi Options
  Serial.println("");
  PrintUnderline("Wi-Fi Options");

  // Initialise WiFi and WebServer/OTA
  if (DisableWiFi == false)
  {
    InitialiseWiFi();
    InitialiseWebServer();
    InitialiseMQTT();
    InitialiseDomoticz();
    // InitialiseThingSpeak();
    InitialiseZabbix();
  }
  else
  {
    Serial.println("Wi-Fi Force Disabled - No Publishing");
  }

  // Display Software Options
  Serial.println("");
  PrintUnderline("Software Options");

  // Check DCV_IN
  CheckDCVINVoltage();

  // DisplayOLEDWiFiStatus
  DisplayOLEDWiFiStatus();

// ****************  Initialise the ATM90E3x & Pass related calibrations to its library ****************

// LineFreq = lineFreq, PGAGain = pgagain, VoltageGainX = ugain, CurrentGainCT1 = igainA, CurrentGainCT2 = igainB, CurrentGainCT3 = igainC, CurrentGainCTN = igainN
#if ATM90DEVICE == ATM90E32_DEVICE && ATM_SPLITPHASE == true // Not Fully Tested.
// the 2nd (B) current channel is not used with the split phase meter
#if ATM_SINGLEVOLTAGE == true
  eic.begin(LineFreq, PGAGain, VoltageGain1, 0, 0, CurrentGainCT1, 0, CurrentGainCT2);
#else
  eic.begin(LineFreq, PGAGain, VoltageGain1, VoltageGain2, VoltageGain3, CurrentGainCT1, 0, CurrentGainCT2);
#endif
#endif

#if ATM90DEVICE == ATM90E32_DEVICE && ATM_SPLITPHASE == false
#if ATM_SINGLEVOLTAGE == true
  // eic.begin(LineFreq, PGAGain, VoltageGain1, 0, 0, CurrentGainCT1, CurrentGainCT2, CurrentGainCT3);
  eic.begin(LineFreq, PGAGain, VoltageGain1, VoltageGain1, VoltageGain1, CurrentGainCT1, CurrentGainCT2, CurrentGainCT3);
#else
  eic.begin(LineFreq, PGAGain, VoltageGain1, VoltageGain2, VoltageGain3, CurrentGainCT1, CurrentGainCT2, CurrentGainCT3);
#endif
#endif

#if ATM90DEVICE == ATM90E36_DEVICE && ATM_SPLITPHASE == false
#if ATM_SINGLEVOLTAGE == true
  // eic.begin(LineFreq, PGAGain, VoltageGain1, 0, 0, CurrentGainCT1, CurrentGainCT2, CurrentGainCT3, CurrentGainCTN);
  eic.begin(LineFreq, PGAGain, VoltageGain1, VoltageGain1, VoltageGain1, CurrentGainCT1, CurrentGainCT2, CurrentGainCT3, CurrentGainCTN);
#else
  eic.begin(LineFreq, PGAGain, VoltageGain1, VoltageGain2, VoltageGain3, CurrentGainCT1, CurrentGainCT2, CurrentGainCT3, CurrentGainCTN);
#endif
#endif

  Serial.println("\n" + AppAcronym + " Hardware Setup and Power-Up Test - Board Initialized");

  delay(1000);

  Serial.println("");

  DisplayRegisters(); // Display once

} // Setup

// **************** LOOP ****************
void loop() // Future - ISRs To Be Added
{

  String sDIR = "";

  // Basic Handler for WebServer
  CheckOTA();

  // Force Continuous Test PWM Cycle Loop. Force OFF EnablePWMLocal EnablePWMRemote
  if (EnablePWMTestOutput == true && EnableIPEM == false)
  {
    EnablePWMLocal = false;
    EnablePWMRemote = false;

    switch (PWM_TestOutput)
    {
    case 0: // PWM32 Fixed Outputs for Calibration
    {
      PWM32_Calibrate();
      break;
    }
    case 1: // PWM32 PWM Ramping Cycle
    {
      PWM32_RampingCycle();
      break;
    }

    case 2:
    {
      // PWM32_RampingCycle();
      break;
    }

    case 3: // Fixed Ramped Power Outputs for Calibration
    {
      PWM_CalibrateStepPowerRamp();
      break;
    }
    }
  }

  // DAC TEST - Force Continuous Test DAC Sinewave Cycle Loop etc. Force OFF EnableDACLocal EnableDACRemote
  if (EnableDACTestOutput == true && EnableIPEM == false)
  {
    EnableDACLocal = false;
    EnableDACRemote = false;

    switch (DAC_TestOutputOption)
    {
    case 0: // Fixed Outputs for Calibration
    {
      DAC_Calibrate(0);
      break;
    }
    case 1: // Fixed Ramped Outputs for Calibration
    {
      DAC_CalibrateStepRamp(0);
      break;
    }
    case 2: // Ramped Outputs for Testing
    {
      DAC_CalibrateSlowRamp(0);
      break;
    }
    case 3: // Fixed Ramped Power Outputs for Calibration
    {
      DAC_CalibrateStepPowerRamp(0);
      break;
    }
    }
  }

  // Simply DisplayRegisters on Loop if Enabled
  if (EnableBasicLoop == true)
  {
    DisplayRegisters();
    Serial.println("- - - / / - - -\n");
  }

  // Simple test for Loop to bypass EnableBasicLoop if User Button Pressed for ~ 1 Second.  Ignore if ESP32 DAC used.
  if (digitalRead(User_Button) == LOW && EnableDACTestOutput == false && EnablePWMLocal == false && EnableDACRemote == false)
  {
    DisplayRegisters();
    Serial.println("- - - / / - - -\n");
  }

  // Display Values to OLED Display
  if (EnableOLEDLoop == true || OLED_Enabled == true)
  {

    DisplayRegisters(false); // Refresh Values and Display.  Default false = Mute Expanded Info to Serial

    // Update the OLED Display
    oled.clear();
    oled.setScale(2);

    if (LineVoltageAverage > 100 || LineVoltage1 > 100) // Arbitrary Value
    {

      oled.setCursor(0, 2);

      // Reset Counter
      if (OLEDCount >= 3)
        OLEDCount = 0;

      OLEDCount++;

      // Check Active Power and Display on Each Channel
      oled.printf("%d: ", OLEDCount);

      switch (OLEDCount)
      {
      case 1:
        if (ActivePowerImportCT1 > 0)
        {
          oled.printf("%.0f W", ActivePowerImportCT1);
          sDIR = "Impt";
        }
        else if (ActivePowerExportCT1 > 0)
        {
          oled.printf("%.0f W", ActivePowerExportCT1);
          sDIR = "Expt";
        }
        else
        {
          oled.printf("0 W");
          sDIR = "Zero";
        }
        break;

      case 2:
        if (ActivePowerImportCT2 > 0)
        {
          oled.printf("%.0f W", ActivePowerImportCT2);
          sDIR = "Impt";
        }
        else if (ActivePowerExportCT2 > 0)
        {
          oled.printf("%.0f W", ActivePowerExportCT2);
          sDIR = "Expt";
        }
        else
        {
          oled.printf("0 W");
          sDIR = "Zero";
        }
        break;

      case 3:
        if (ActivePowerImportCT3 > 0)
        {
          oled.printf("%.0f W", ActivePowerImportCT3);
          sDIR = "Impt";
        }
        else if (ActivePowerExportCT3 > 0)
        {
          oled.printf("%.0f W", ActivePowerExportCT3);
          sDIR = "Expt";
        }
        else
        {
          oled.printf("0 W");
          sDIR = "Zero";
        }
        break;
      }

      // Header
      oled.setCursor(0, 0);
      oled.print(LineVoltage1, 0);
      oled.println(" V " + sDIR);
    }
    else
    {
      // Houston, We may have a probem
      oled.clear();
      OLEDPrint("Please Chk", 2, 0);
      OLEDPrint("Line Volts", 2, 2);
      oled.update();

      delay(1500);

      // DisplayOLEDWiFiStatus
      DisplayOLEDWiFiStatus();
    }

    // Write to OLED
    oled.update();
  }

  // Publish Values to Domoticz (Set WiFi and Indexes)
  if (EnableDomoticz == true && WiFi.status() == WL_CONNECTED)
  {
    DisplayRegisters(false); // Refresh Values and Display.  Default false = Mute Expanded Info to Serial
    PublishDomoticzValues(); // Publish Values to Domoticz
  }

  // Publish Values to MQTT (Set WiFi and Indexes)
  if (EnableMQTT == true && WiFi.status() == WL_CONNECTED)
  {
    DisplayRegisters(false); // Refresh Values and Display.  Default false = Mute Expanded Info to Serial
    PublishMQTTValues();     // Publish Values to MQTT
  }

  // // Publish Values to ThingSpeak (Set WiFi and Indexes)
  // if (EnableThingSpeak == true && WiFi.status() == WL_CONNECTED)
  // {
  //   DisplayRegisters(false);  // Refresh Values and Display.  Default false = Mute Expanded Info to Serial
  //   UpdateThingSpeakValues(); // Publish Values to ThingSpeak
  // }

  // Heatbeat LED
  digitalWrite(LED_Blue, LOW);
  delay(50);
  digitalWrite(LED_Blue, HIGH);

  // Loop Delay
  delay(LoopDelay * 1000);
} // loop
