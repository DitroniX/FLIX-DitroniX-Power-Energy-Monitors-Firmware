/*
  Dave Williams, DitroniX 2019-2023 (ditronix.net)
  Full header information in README

  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  Further information, details and examples can be found on our website wiki pages ditronix.net/wiki and also github.com/DitroniX
*/

// NOTE: THIS CODE IS UNDER DEVELOPMENT FOR THE IPEC/IPEX BRANCH. DAVE WILLIAMS AUGUST 2023

// Libraries
#include <Arduino.h>

// ****************  VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

// ESP32 PWM 1 Channel 16-bit PWM Driver
#define PWM_IPEM_GPIO 17 // IPEM Use.  Purely for IPEM PWM Testing.  Define PWM GPIO (Default GPIO 17 = Existing USR_GP17_TX_PWM).
#define PWM_IPEC_GPIO 25 // IPEC Use.  Define PWM GPIO (Default GPIO 25).

// ****************  VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

// Development and testing Use.  EnablePWMTestOutput will over-ride EnablePWMLocal and EnablePWMRemote
boolean EnablePWMTestOutput = true; // Enable/TurnOn Continuous PWM Cycle Test.  Will Bypass Actual Readings. Default(false)
int PWM_TestOutput = 1;             // Base Test Routine Output (If EnablePWMTestOutput is True.  Options 0-3. Default 0)

// Variables USER and External (Power Up Default)
boolean EnablePWMLocal = false;  // Enable/TurnOn PWM Local. Default(false) Soft Switch for Local Direct Control /PWM-On /PWM-Off
boolean EnablePWMRemote = false; // Enable/Allow PWM Remote Power Control. Default(false) Soft Switch for Remote Control /PWM-Remote

// Constants Power USER - These values work in hand with Input Power and PWM Voltage Output Ranges / Mapping
float PWM_PowerThreshold = 5;     // Minimum Power Threshold (in Watts), Before Outputting PWM.  Also used for Noise and Jitter Control. (Default 5)
float PWM_PowerUpperLimit = 4000; // Maximum CT Power Upper Range DAC_MinimumPowerThreshold to x (in Watts). Upper Limit of Measured Power for Scaling (Default 4000)

// Constants PWM Duty Cycle USER - These values work in hand with Input Power and PWM Duty Cycle Output Ranges / Mapping
float PWM_DutyCycleOutputThreshold = 0.0;     // Duty Cycle Range Minimum Before Outputting from DAC. (Default 0.0 - Minimum 0)
float PWM_DutyCycleOutputUpperLimit = 100.00; // // PWM Maximum Duty Cycle Based on PWM32_ResolutionBit and PWM_ResolutionBit (Default is 100.00 - Maximum 100.00)

// Constants Power Percentage USER - These values work in hand with Input Power and DAC PM Output Ranges / Mapping
int PWM_PercentageMinimum = 0;   // Power Percentage Minimum Displayed
int PWM_PercentageMaximum = 100; // Power Percentage Maximum Displayed

// Constants PWM ESP32
const int PWM32_ChannelOut = 0;     // Output Channel 0-15
const int PWM32_FrequencyHz = 1000; // PWM Default Frequency (Default 1000).  PWM Frequency Range 10Hz to 40MHz.
const int PWM32_ResolutionBit = 10; // PWM bit Range 1-16 bits (Default 10) 8bit = 256-1 | 10bit = 1024-1 | 12bit = 4096-1 | 14bit = 16384-1 | 16bit = 65536-1

// Constants PWM PCA9685 IPEX-1 USER
const int PWM_PCA_ChannelOut = 0; // Output Channel 0-15
const int Frequency = 1000;       // Frequency Hz

// Variables PWM Internal
int PWM_MaximumResolution; // 8bit = 256-1 | 10bit = 1024-1 | 12bit = 4096-1 | 14bit = 16384-1 | 16bit = 65536-1.
// int PWM_DutyCycleOutputUpperLimit;      // PWM Maximum Duty Cycle Based on PWM32_ResolutionBit and PWM_ResolutionBit

// Variables PWM External - Used for Publishing and Control
float PWMPowerOutput;     // Last Power Value Used For DAC
float PWMDutyCycleOutput; // Last Duty Cycle Value Used For DAC
int PWMChannelOutput;     // Last Channel Value Used For DAC
boolean PWMOutputOff;     // Last DAC Output Off Base State
int PWMPowerPercentage;   // Base Power Percentage
float PWMLocalPower = 0;  // Base Local Power Level (Power Up Default 0)
float PWMRemotePower = 0; // Base Remote Power Level (Power Up Default 0)

// **************** FUNCTIONS AND ROUTINES ****************

// Initialise IPEM/IPEC ESP32 PWM
void Initialise_ESP32_PWM(int PWM_GPIO)
{
    // PWM Integration Status
    if (EnablePWMLocal == false && EnablePWMRemote == false && EnablePWMTestOutput == false)
    {
        Serial.println("PWM (ESP32) Output is Disabled\n");
    }
    else
    {
        ledcSetup(PWM_PCA_ChannelOut, PWM32_FrequencyHz, PWM32_ResolutionBit);
        ledcAttachPin(PWM_GPIO, PWM32_ChannelOut);
        PWM_DutyCycleOutputUpperLimit = (int)(pow(2, PWM32_ResolutionBit) - 1); // 8bit = 256-1 | 10bit = 1024-1 | 12bit = 4096-1 | 14bit = 16384-1 | 16bit = 65536-1.
        ledcWrite(PWM_PCA_ChannelOut, 0);

        Serial.println("PWM (ESP32) Initialised\n");

        if (EnablePWMLocal == true)
            Serial.println("PWM (ESP32) Output is Enabled from PWMLocal");

        if (EnablePWMRemote == true)
            Serial.println("PWM (ESP32) Output is Enabled from PWMRemote");

        if (EnablePWMTestOutput == true)
            Serial.println("PWM (ESP32) Output is Enabled from PWM Test Output");

        // Configuration Info
        Serial.printf("PWM Power Minimum Threshold W:\t\t%04.0f\n", PWM_PowerThreshold);
        Serial.printf("PWM Power Maximum Limit W:\t\t%04.0f\n", PWM_PowerUpperLimit);
        Serial.printf("PWM Duty Cycle Threshold:\t\t%04.3f\n", PWM_DutyCycleOutputThreshold);
        Serial.printf("PWM Duty Cycle Max Limit V:\t\t%04.3f\n", PWM_DutyCycleOutputUpperLimit);
        Serial.printf("PWM Percentage Display Lower:\t\t%d\n", PWM_PercentageMinimum);
        Serial.printf("PWM Percentage Display Upper:\t\t%d\n", DAC_PercentageUpper);
        Serial.printf("PWM Resolution Bit:\t\t\t%d\n", PWM32_ResolutionBit);
        Serial.printf("PWM Maximum Resolution:\t\t\t%d\n", PWM_MaximumResolution);
        Serial.printf("PWM Frequency Hz:\t\t\t%d\n", PWM32_FrequencyHz);
        Serial.printf("PWM Channel Output:\t\t\t%d\n", PWM_PCA_ChannelOut);
        Serial.printf("PWM Port Output GPIO :\t\t\t%d\n", PWM_GPIO);

        Serial.println("");
    }

} // Initialise_ESP32_PWM

// Initialise IPEX PCA9685 PWM
void Initialise_PCA9685_PWM()
{
} // Initialise_PCA9685_PWM

// PWM Duty Cycle Output Based on Input Base Power - But Only On Value Change or Zero
void PWM_WriteDutyCycle(float PWM_PowerPercentage = 0, float PWM_PowerMap = 0, int PWM_Channel = 0) // PWM_OutputDutyCycle 0 = OFF, PWM_PowerMap, PWM_Channel 0
{
    if (PWM_PowerPercentage != PWMPowerPercentage)
    {
        // Store Last Change
        PWMPowerPercentage = PWM_PowerPercentage;
        PWMPowerOutput = PWM_PowerMap;

        // Set Max Duty Cycle limit
        if (PWMDutyCycleOutput >= PWM_DutyCycleOutputUpperLimit)
            PWMDutyCycleOutput = PWM_DutyCycleOutputUpperLimit;

        // Set Min Duty Cycle limit.  If Zero then Ignore Lower Limit as this is PWM Off.
        if (PWMDutyCycleOutput <= PWM_DutyCycleOutputThreshold && PWMDutyCycleOutput > 0)
            PWMDutyCycleOutput = 0;

        // Calculate Values
        int WriteValue = map(PWM_PowerPercentage, PWM_PercentageMinimum, PWM_PercentageMaximum, PWM_DutyCycleOutputThreshold, PWM_DutyCycleOutputUpperLimit);

        // Update PWM Port
        ledcWrite(PWM_PCA_ChannelOut, WriteValue);

        // Display Value
        if (PWMPowerPercentage > 0)
        {
            Serial.print("Updated PWM Power: " + String(PWM_PowerMap) + "\t\t");
            Serial.print("Duty Cycle: " + String(WriteValue) + "\t\t");
            PWMPowerPercentage = map(PWMPowerPercentage, PWM_PercentageMinimum, PWM_PercentageMaximum, PWM_PowerThreshold, PWM_PowerUpperLimit); // Scaled example 0-4kW = 0-100% = 255
            Serial.println(String(PWMPowerPercentage) + " %");
        }
        else
        {
            Serial.println("Updated PWM Power Duty Cycle: \tPWM Off");
        }
    }

} // PWM_WriteDutyCycle

// Output PWM Value Based on Input Power. DutyCycle Approx Values: 256=1kW, 512=2kW, 769=3kW and 1023=4kW
void PWM_Power(float PWM_PowerOutput = 0, int PWM_Channel = 0)
{

    if (int(PWM_PowerOutput) != int(PWMPowerOutput) || PWM_PowerOutput == PWM_PowerThreshold)
    {
        // Store Last Change
        PWMPowerOutput = PWM_PowerOutput;

        // Set and Store Max and Min Power Window Limits (Top and Tail)
        if (PWMPowerOutput >= PWM_PowerUpperLimit)
            PWMPowerOutput = PWM_PowerUpperLimit;

        if (PWMPowerOutput <= PWM_PowerThreshold)
            PWMPowerOutput = PWM_PowerThreshold;

        // Map Power to PWM and Write
        float Local_Value = map(PWMPowerOutput, PWM_PowerThreshold, PWM_PowerUpperLimit, 0, 100);
        //float Local_Value = map(PWMPowerOutput, PWM_PowerThreshold, PWM_PowerUpperLimit, PWM_DutyCycleOutputThreshold, PWM_DutyCycleOutputUpperLimit);

        Serial.println(Local_Value);
        Serial.println(PWMPowerOutput);

        PWM_WriteDutyCycle(Local_Value, PWMPowerOutput);
    }

} // PWM_Power

// **************** Calibration Functions ****************

// 0 PWM32 Fixed Outputs for Calibration
void PWM32_Calibrate()
{
    int Local_Value = 50; // % Duty Cycle

    Serial.println("PWM32 Fixed Outputs for Calibration");

    PWM_WriteDutyCycle(Local_Value);
    delay(3000);

    PWM_WriteDutyCycle(0);

} // PWM32_Calibrate

// 1 PWM32 PWM Ramping Cycle
void PWM32_RampingCycle()
{
    Serial.println("PWM32 PWM Ramping Cycle");

    /* Increasing the PWM Duty Cycle Output */
    // for (float Local_Value = 0; Local_Value <= 100; Local_Value++)
    for (float Local_Value = PWM_DutyCycleOutputThreshold; Local_Value <= PWM_DutyCycleOutputUpperLimit; Local_Value++)
    {
        PWM_WriteDutyCycle(Local_Value);

Serial.println(Local_Value);

        delay(50);
    }
    /* Decreasing the PWM Duty Cycle Output */
    // for (float Local_Value = 100; Local_Value >= 0; Local_Value--)
    for (float Local_Value = PWM_DutyCycleOutputUpperLimit; Local_Value >= PWM_DutyCycleOutputThreshold; Local_Value--)
    {
        PWM_WriteDutyCycle(Local_Value);

        Serial.println(Local_Value);
        delay(50);
    }
} // PWM32_RampingCycle

// 3 Fixed Ramped Power Outputs for Calibration
void PWM_CalibrateStepPowerRamp()
{
    int Delay_ms = 200;    // Inter Step Delay in ms (Default 200 = 0.2 Seconds)
    float StepPower = 100; // Inter Step Power Change in Watts (Default 100W)

    Serial.println("Fixed Ramped Power Outputs for Calibration");

    for (float Local_Value = 0; Local_Value <= (PWM_PowerUpperLimit + PWM_PowerThreshold); Local_Value += StepPower)
    {
        PWM_Power(Local_Value);
        delay(Delay_ms);
    }

    Serial.println("");
} // PWM_CalibrateStepPowerRamp