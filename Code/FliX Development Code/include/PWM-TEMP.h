// /*
//   Dave Williams, DitroniX 2019-2025 (ditronix.net)
//   Full header information in README

//   This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
//   It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

//   Further information, details and examples can be found on our website wiki pages ditronix.net/wiki and also github.com/DitroniX
// */

// // NOTE: THIS CODE IS UNDER DEVELOPMENT FOR THE IPEC/IPEX BRANCH. DAVE WILLIAMS AUGUST 2023

// // Libraries
// #include <Arduino.h>
// #include <PCA9685.h> // Used for IPEX PWM (https://github.com/RobTillaart/PCA9685_RT)

// // ****************  VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

// // ESP32 PWM 1 Channel 16-bit PWM Driver
// #define PWM_IPEM_GPIO 17 // IPEM Use.  Purely for IPEM PWM Testing.  Define PWM GPIO (Default GPIO 17 = Existing USR_GP17_TX_PWM).
// #define PWM_IPEC_GPIO 25 // IPEC Use.  Define PWM GPIO (Default GPIO 25).

// // PCA9685 IPEX-1 16-Channel 12-bit PWM Driver
// PCA9685 PCA(0x40);

// // ****************  VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

// // Development and testing Use.  EnablePWMTestOutput will over-ride EnablePWMLocal and EnablePWMRemote
// boolean EnablePWMTestOutput = true; // Enable/TurnOn Continuous PWM Cycle Test.  Will Bypass Actual Readings. Default(false)
// int PWM_TestOutput = 0;             // Base Test Routine Output (If EnablePWMTestOutput is True.  Options 0-3. Default 0)

// // Variables USER and External (Power Up Default)
// boolean EnablePWMLocal = false;  // Enable/TurnOn PWM Local. Default(false) Soft Switch for Local Direct Control /PWM-On /PWM-Off
// boolean EnablePWMRemote = false; // Enable/Allow PWM Remote Power Control. Default(false) Soft Switch for Remote Control /PWM-Remote

// // Constants Power USER - These values work in hand with Input Power and PWM Voltage Output Ranges / Mapping
// float PWM_MinimumPowerThreshold = 5; // Minimum Power Threshold (in Watts), Before Outputting PWM.  Also used for Noise and Jitter Control. (Default 5)
// float PWM_MaximumPowerLimit = 4000;  // Maximum CT Power Range DAC_MinimumPowerThreshold to x (in Watts). Upper Limit of Measured Power for Scaling (Default 4000)

// // Constants PWM USER - These values work in hand with Input Power and PWM Duty Cycle Output Ranges / Mapping
// float PWM_OutputRangeMinimum = 0.0;    // Duty Cycle Range Minimum (in %) Before Outputting from DAC. (Default 0.0 - Minimum 0)
// float PWM_OutputRangeMaximum = 100.00; // Duty Cycle Range Maximum (in %) of Outputting from DAC. (Default is 100.00 - Maximum 100.00)

// // Constants PWM ESP32
// const int PWM32_ChannelOut = 0;     // Output Channel 0-15
// const int PWM32_FrequencyHz = 1000; // PWM Default Frequency (Default 1000).  PWM Frequency Range 10Hz to 40MHz.
// const int PWM32_ResolutionBit = 10; // PWM bit Range 1-16 bits (Default 10) 8bit = 256-1 | 10bit = 1024-1 | 12bit = 4096-1 | 14bit = 16384-1 | 16bit = 65536-1.

// // Constants PWM PCA9685 IPEX-1 USER
// const int PWM_PCA_ChannelOut = 0; // Output Channel 0-15
// const int Frequency = 1000;       // Frequency Hz

// // Variables PWM Internal
// int PWM_DutyCycle;
// float PWM_LastBasePower;
// int PWM_MaximumResolution; // 8bit = 256-1 | 10bit = 1024-1 | 12bit = 4096-1 | 14bit = 16384-1 | 16bit = 65536-1.
// int PWM_MaxDutyCycle;      // PWM Maximum Duty Cycle Based on PWM32_ResolutionBit and PWM_ResolutionBit

// // Variables PWM External
// int PWMPowerOutput;       // PWM Power Output Value
// int PWMPowerPercentage;   // PWM Power Output Percentage
// float PWMRemotePower = 0; // Remote Default Base Power Level (Default 0)
// float PWMLocalPower = 0;  // Local Default Base Power Level (Default 0)

// // Constants Power
// float PWM_MinimumDutyCycle = 0; // PWM Minimum Duty Cycle (Default 0)
// int PWM_FrequencyHz = 1000;     // PWM Default Frequency (Default 1000).  PWM Frequency Range 10Hz to 40MHz.
// int PWM_ResolutionBit = 14;     // PWM bit Range 1-16 bits (Default 14)
// int PWM_Channel = 0;            // PWM Channels 0-15 (Default 0)

// // **************** FUNCTIONS AND ROUTINES ****************

// // Initialise IPEM/IPEC ESP32 PWM
// void Initialise_ESP32_PWM(int PWM_GPIO)
// {
//     // PWM Integration Status
//     if (EnablePWMLocal == false && EnablePWMRemote == false && EnablePWMTestOutput == false)
//     {
//         Serial.println("PWM (ESP32) Output is Disabled\n");
//     }
//     else
//     {
//         ledcSetup(PWM_Channel, PWM32_FrequencyHz, PWM32_ResolutionBit);
//         ledcAttachPin(PWM_GPIO, PWM32_ChannelOut);
//         PWM_MaxDutyCycle = (int)(pow(2, PWM32_ResolutionBit) - 1); // 8bit = 256-1 | 10bit = 1024-1 | 12bit = 4096-1 | 14bit = 16384-1 | 16bit = 65536-1.
//         ledcWrite(PWM_Channel, 0);

//         Serial.println("PWM (ESP32) Initialised\n");

//         if (EnablePWMLocal == true)
//             Serial.println("PWM (ESP32) Output is Enabled from PWMLocal");

//         if (EnablePWMRemote == true)
//             Serial.println("PWM (ESP32) Output is Enabled from PWMRemote");

//         if (EnablePWMTestOutput == true)
//             Serial.println("PWM (ESP32) Output is Enabled from PWM Test Output");

//         // Configuration Info
//         Serial.printf("PWM (ESP32) GPIO Port:\t\t\t%0d\n", PWM_GPIO);
//         Serial.printf("PWM (ESP32) Port Channel:\t\t%0d\n", PWM32_ChannelOut);
//         Serial.printf("PWM (ESP32) Frequency Hz:\t\t%d\n", PWM32_FrequencyHz);
//         Serial.printf("PWM (ESP32) Maximum Power Limit:\t%04.2f\n", PWM_MaximumPowerLimit);
//         Serial.printf("PWM (ESP32) Resolution Bit:\t\t%d\n", PWM32_ResolutionBit);
//         Serial.printf("PWM (ESP32) Maximum Duty Cycle:\t\t%d\n", PWM_MaxDutyCycle);
//         Serial.println("");
//     }

// } // Initialise_ESP32_PWM

// // Initialise IPEX PCA9685 PWM
// void Initialise_PCA9685_PWM()
// {
//     if (!PCA.begin())
//     {
//         Serial.println("Failed to find IPEX-1 PCA9685 PWM Device.  Retrying..");
//         while (1)
//         {
//             delay(10);
//         }
//     }

//     // PWM Integration Status
//     if (EnablePWMLocal == false && EnablePWMRemote == false && EnablePWMTestOutput == false)
//     {
//         Serial.println("PWM (PCA9685) Output is Disabled");
//     }
//     else
//     {
//         Serial.println("PWM (PCA9685) Initialised\n");

//         if (EnablePWMLocal == true)
//             Serial.println("PWM (PCA9685) Output is Enabled from PWMLocal");

//         if (EnablePWMRemote == true)
//             Serial.println("PWM (PCA9685) Output is Enabled from PWMRemote");

//         if (EnablePWMTestOutput == true)
//             Serial.println("PWM (PCA9685) Output is Enabled from PWM Test Output");

//         // Configuration Info
//         Serial.printf("PWM (PCA9685) Maximum Power Limit:\t%0f\n", PWM_MaximumPowerLimit);
//         Serial.printf("PWM (PCA9685) Resolution Bit:\t\t%d\n", PWM_ResolutionBit);

//     }

//     Serial.println("Channel Count: " + String(PCA.channelCount()));
//     Serial.print("Get Mode 1: 0x");
//     Serial.println(PCA.getMode1(), HEX); // Default AUTOINCR + ALLCALL
//     Serial.print("Get Mode 2: 0x");
//     Serial.println(PCA.getMode2(), HEX); // Default TOTEMPOLE

//     Serial.println("Default Frequency: " + String(PCA.getFrequency())); // Default 200
//     PCA.setFrequency(Frequency);                                        // Set to Defined Frequency
//     Serial.println("Set Frequency: " + String(PCA.getFrequency()));
//     Serial.println("Actual Frequency: " + String(PCA.getFrequency(false)));

//     // Test
//     // PCA.setPWM(PWM_PCA_ChannelOut, 2048);
//     // PCA.setPWM(PWM_PCA_ChannelOut + 1, 2048);
//     // PCA.digitalWrite(PWM_PCA_ChannelOut, HIGH);
//     // PCA.digitalWrite(PWM_PCA_ChannelOut + 1, HIGH);
//     delay(1000);

// } // Initialise_PCA9685_PWM

// // PWM Output Based on Input Base Power (With Defaults).
// void PWM_Write(float InputBasePower)
// {
//     if (PWM_LastBasePower != InputBasePower)
//     {
//         // Store Last Reading and Calculate PWM_LastBasePower
//         PWM_LastBasePower = InputBasePower;

//         // Calculate PWM Duty Cycle
//         // PWM_DutyCycle = (InputBasePower / PWM_ScalingFactor);

//         // Set Max Duty Cycle limit
//         if (PWM_DutyCycle >= PWM_MaximumResolution)
//             PWM_DutyCycle = PWM_MaximumResolution;

//         // Set Min Duty Cycle limit.  If Zero then Ignore Lower Limit as this is PWM Off.
//         if (PWM_DutyCycle <= PWM_MinimumDutyCycle && PWM_DutyCycle > 0)
//             PWM_DutyCycle = 0;

//         // Update PWM Port
//         // ledcWrite(PWM_Channel, PWM_DutyCycle);

//         // Display Value
//         if (PWM_DutyCycle > 0)
//         {
//             Serial.print("Updated PWM Power: " + String(PWM_LastBasePower) + "\t\t");
//             Serial.print("Duty Cycle: " + String(PWM_DutyCycle) + "\t\t");
//             PWMPowerPercentage = map(PWM_DutyCycle, PWM_MinimumDutyCycle, PWM_MaximumResolution, 0, 100); // Scaled example 0-4kW = 0-100% = 1023
//             Serial.println(String(PWMPowerPercentage) + " %");
//         }
//         else
//         {
//             Serial.println("Updated PWM Power Duty Cycle: \tPWM Off");
//         }
//     }

// } // PWM_Write

// // Output PWM Value Based on Input Power. DutyCycle Approx Values: 256=1kW, 512=2kW, 769=3kW and 1023=4kW
// void PWM_Power(float InputBasePower = 0)
// {
//     // Check Maximum Limits.  0 to Ignore Limit.
//     if (InputBasePower >= PWM_MaximumPowerLimit)
//         InputBasePower = PWM_MaximumPowerLimit;

//     // Check Valid Limits / Calculate.  Also ensure no Negative Powers
//     if (InputBasePower >= PWM_MinimumPowerThreshold)
//     {
//         // DAC_WritePower(InputBasePower);
//     }
//     else
//     { // Turn PWM Off if Zero or Below PWM_MinimumPowerThreshold
//       // DAC_WritePower(0);
//     }

//     // Configuration Conflict Issue - Turn Both Off
//     if (EnablePWMLocal == true && EnablePWMRemote == true)
//     {
//         Serial.print("PWM Configuration Issue - Forcing Off");
//         // DAC_WritePower(0);
//         EnablePWMLocal = false;
//         EnablePWMRemote = false;
//         EnablePWMTestOutput = false;
//     }

// } // PWM_Power

// // Output Full PWM Duty / Power Cycle - Test Use Only
// void PWM_Test()
// {
//     int BasePower = 0;

//     Serial.println("Output Full PWM Duty / Power Cycle ");

//     /* Increasing an LED brightness with PWM */
//     for (BasePower = 0; BasePower <= PWM_MaximumPowerLimit; BasePower++)
//     {
//         // DAC_WritePower(BasePower);
//         PCA.setPWM(PWM_PCA_ChannelOut, BasePower);
//     }
//     /* Decreasing an LED brightness with PWM */
//     for (BasePower = PWM_MaximumPowerLimit; BasePower >= 0; BasePower--)
//     {
//         // DAC_WritePower(BasePower);
//         PCA.setPWM(PWM_PCA_ChannelOut, BasePower);
//     }
// } // PWM_Test

// // PWM32 PWM Ramping Cycle
// void PWM32_RampingCycle()
// {
//     Serial.println("PWM32 PWM Ramping Cycle");

//     /* Increasing the PWM Output */
//     for (PWM_DutyCycle = 0; PWM_DutyCycle <= PWM_MaxDutyCycle; PWM_DutyCycle++)
//     {
//         ledcWrite(PWM_Channel, PWM_DutyCycle);
//         delay(2);
//     }
//     /* Decreasing the PWM Output */
//     for (PWM_DutyCycle = PWM_MaxDutyCycle; PWM_DutyCycle >= 0; PWM_DutyCycle--)
//     {
//         ledcWrite(PWM_Channel, PWM_DutyCycle);
//         delay(2);
//     }
// } // PWM32_RampingCycle