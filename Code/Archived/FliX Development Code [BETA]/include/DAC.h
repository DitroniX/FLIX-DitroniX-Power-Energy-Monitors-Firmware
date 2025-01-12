/*
  Dave Williams, DitroniX 2019-2023 (ditronix.net)
  Full header information in README

  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  Further information, details and examples can be found on our website ditronix.net, github.com/DitroniX and hackster.io/DitroniX
*/

// NOTE: THIS CODE IS UNDER DEVELOPMENT FOR THE IPEC/IPEX BRANCH. DAVE WILLIAMS AUGUST 2023

// Libraries
#include "Wire.h"
#include <Adafruit_MCP4728.h> // Used for IPEC DAC (https://github.com/adafruit/Adafruit_MCP4728)

// ****************  VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

// IPEC DAC MCP4728 quad channel, 12-bit voltage output Digital-to-Analog Convertor with non-volatile memory
Adafruit_MCP4728 mcp;
#define IPEC_MCP4728 0x60 // Default IPEC MCP4728 Address

// ****************  VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

// EnableDACTestOutput will over-ride EnableDACLocal and EnableDACRemote
boolean EnableDACTestOutput = false; // Enable/TurnOn Continuous DAC Cycle Test.  Will Bypass Actual Readings. Default(false)

// 0 DAC_Calibrate | Fixed Outputs for Calibration
// 1 DAC_CalibrateStepRamp | Fixed Ramped Outputs for Calibration
// 2 DAC_CalibrateSlowRamp | Ramped Outputs for Testing
// 3 DAC_CalibrateStepPowerRamp | Fixed Ramped Power Outputs for Calibration
int DAC_TestOutputOption = 0; // Base Test Routine Output (If EnableDACTestOutput i s True.  Options 0-3. Default 0)

// Variables USER and External - Outputs a DAC Voltage, pending Power Exported.  Do NOT Enable Both Options(Power Up Default)
boolean EnableDACLocal = false;  // Enable/TurnOn DAC Web Local. Default(false) Soft Switch for Local Direct Control /DAC-On /DAC-Off
boolean EnableDACRemote = false; // Enable/Allow DAC Remote Power Control. Default(false) Soft Switch for Remote Control /DAC-Remote

// Constants Power USER - These values work in hand with Input Power and DAC Voltage Output Ranges / Mapping
float DAC_PowerThreshold = 5;    // Minimum Power Threshold (in Watts), Before Outputting to DAC.  Also used for Noise and Jitter Control. (Default 5)
float DAC_PowerUpperLimit = 500; // Maximum CT Power Upper Range Limit DAC_PowerThreshold to x (in Watts). Upper Limit of Measured Power for Scaling (Default 4000)

// Constants DAC Voltage USER - These values work in hand with Input Power and DAC Voltage Output Ranges / Mapping
float DAC_VoltageOutputThreshold = 0.0;  // Voltage Range Threshold (in Volts) Before Outputting from DAC. (Default 0.0 - Minimum 0)
float DAC_VoltageOutputUpperLimit = 3.3; // Maximum Voltage Range Limit (in Volts) of Outputting from DAC. (Default is 3.3 - Maximum 3.3)

// Constants Power Percentage Displayed USER - These Displayed Values Align with Mapped Input Power and DAC Voltage Output Ranges
int DAC_PercentageLower = 0;   // Power Percentage Minimum Displayed (Default 0)
int DAC_PercentageUpper = 100; // Power Percentage Maximum Displayed (Default 100)

// Constants DAC MCP4728
int DAC_ResolutionBit = 12;                                       // DAC Resolution bit (Default 12 for MCP4728)
int DAC_MaximumResolution = (int)(pow(2, DAC_ResolutionBit) - 1); // Auto 8bit = 256-1 | 10bit = 1024-1 | 12bit = 4096-1 | 14bit = 16384-1 | 16bit = 65536-1.

// Variables DAC External - Used for Publishing and Control
float DACPowerOutput;     // Last Power Value Used For DAC
float DACVoltageOutput;   // Last Voltage Value Used For DAC
int DACChannelOutput;     // Last Channel Value Used For DAC
boolean DACOutputOff;     // Last DAC Output Off Base State
int DACPowerPercentage;   // Base Power Percentage
float DACLocalPower = 0;  // Base Local Power Level (Power Up Default 0)
float DACRemotePower = 0; // Base Remote Power Level (Power Up Default 0)

// **************** FUNCTIONS AND ROUTINES ****************

// Initialise MCP4728 DAC
void Initialise_MCP4728_DAC()
{
    // DAC Integration Status
    if (EnableDACLocal == false && EnableDACRemote == false && EnableDACTestOutput == false || EnableDACLocal == true && EnableDACRemote == true)
    {
        Serial.println("DAC (MCP4728) Output is Disabled\n");
        DACOutputOff = true;
        EnableDACLocal = false;
        EnableDACRemote = false;
        EnableDACTestOutput - false;
    }
    else
    {
        if (!mcp.begin(IPEC_MCP4728))
        {
            Serial.println("Failed to find MCP4728 Device.  Retrying..");
            while (1)
            {
                delay(10);
            }
        }

        Serial.println("DAC (MCP4728) Initialised");

        if (EnableDACLocal == true)
            Serial.println("DAC (MCP4728) Output is Enabled from DACLocal");

        if (EnableDACRemote == true)
            Serial.println("DAC (MCP4728) Output is Enabled from DACRemote");

        if (EnableDACTestOutput == true)
            Serial.println("DAC (MCP4728) Output is Enabled from DAC Test Output");

        if (EnableDACLocal == true || EnableDACRemote == true || EnableDACTestOutput == true)
        {
            // Configuration Info
            Serial.printf("DAC Power Minimum Threshold W:\t\t%04.0f\n", DAC_PowerThreshold);
            Serial.printf("DAC Power Maximum Limit W:\t\t%04.0f\n", DAC_PowerUpperLimit);
            Serial.printf("DAC Voltage Output Minimum V:\t\t%04.3f\n", DAC_VoltageOutputThreshold);
            Serial.printf("DAC Voltage Output Limit V:\t\t%04.3f\n", DAC_VoltageOutputUpperLimit);
            Serial.printf("DAC Percentage Display Lower:\t\t%d\n", DAC_PercentageLower);
            Serial.printf("DAC Percentage Display Upper:\t\t%d\n", DAC_PercentageUpper);
            Serial.printf("DAC Resolution Bit:\t\t\t%d\n", DAC_ResolutionBit);
            Serial.printf("DAC Maximum Resolution:\t\t\t%d\n", DAC_MaximumResolution);
            Serial.println("");
        }
    }
} // Initialise_MCP4728_DAC

// Map Floats to Floats
float MapFloat(float x, float in_min, float in_max, float out_min, float out_max) // Input, In_minimum, In_Maximum, Out_minimum, Out_Maximum
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
} // MapFloat

// Update DAC Ouput Registers
void DAC_SetValue(int WriteValue = 0, int DAC_Channel = 0) // WriteValue 0 = OFF, DAC_Channel 0 = All Channels or 1-4
{
    // Output Voltage with Gain Options
    switch (DAC_Channel)
    {
    case 0:
    {
        mcp.setChannelValue(MCP4728_CHANNEL_A, WriteValue);
        mcp.setChannelValue(MCP4728_CHANNEL_B, WriteValue);
        mcp.setChannelValue(MCP4728_CHANNEL_C, WriteValue);
        mcp.setChannelValue(MCP4728_CHANNEL_D, WriteValue);
        break;
    }
    case 1:
    {
        mcp.setChannelValue(MCP4728_CHANNEL_A, WriteValue);
        break;
    }
    case 2:
    {
        mcp.setChannelValue(MCP4728_CHANNEL_B, WriteValue);
        break;
    }
    case 3:
    {
        mcp.setChannelValue(MCP4728_CHANNEL_C, WriteValue);
        break;
    }
    case 4:
    {
        mcp.setChannelValue(MCP4728_CHANNEL_D, WriteValue);
        break;
    }
    }

} // DAC_SetValue

// Set DAC to OFF or Disabled
void DAC_SetOff(int DAC_Channel = 0) // DAC_Channel 0 = All Channels or 1-4
{
    if (DACOutputOff == false)
    {
        DAC_SetValue(0, DAC_Channel);

        // Display Values
        if (DAC_Channel > 0)
        {
            Serial.printf("DAC Output %d: ", DAC_Channel);
        }
        else
        {
            Serial.printf("DAC Outputs ALL: ");
        }

        Serial.println("Off or Disabled\n");

        DACOutputOff = true;
    }
} // DAC_SetOff

// Write Value to DAC Outputs - But Only On Value Change or Zero
void DAC_WriteVoltage(float DAC_OutputVoltage = 0, int DAC_Channel = 0, float DAC_PowerMap = 0) // DAC_OutputVoltage 0 = OFF, DAC_Channel 0 = All Channels or 1-4, DAC_PowerMap
{
    if (DAC_OutputVoltage != DACVoltageOutput || DAC_OutputVoltage == DAC_VoltageOutputThreshold || DAC_Channel != DACChannelOutput)
    {
        // Store Last Change (Not to DAC EEPROM)
        DACVoltageOutput = DAC_OutputVoltage;
        DACChannelOutput = DAC_Channel;

        // Set Max and Min Limits (Top and Tail)
        if (DACVoltageOutput >= DAC_VoltageOutputUpperLimit)
            DACVoltageOutput = DAC_VoltageOutputUpperLimit;

        if (DACVoltageOutput <= DAC_VoltageOutputThreshold)
            DACVoltageOutput = DAC_VoltageOutputThreshold;

        // Calculate Percentages
        DACPowerPercentage = MapFloat(DACVoltageOutput, DAC_VoltageOutputThreshold, DAC_VoltageOutputUpperLimit, DAC_PercentageLower, DAC_PercentageUpper); // Scaled example 0-4kW = 0-100% = 255

        // Calculate Values
        int WriteValue = (DAC_MaximumResolution / DAC_VoltageOutputUpperLimit) * DACVoltageOutput;

        // Update DAC Output Registers
        DACOutputOff = false;
        DAC_SetValue(WriteValue, DAC_Channel);

        // Display Values
        if (DAC_Channel > 0)
        {
            Serial.printf("DAC Output %d: ", DAC_Channel);
        }
        else
        {
            Serial.printf("DAC Outputs ALL: ");
        }

        // Calculate Power Value if Only Voltage Provided
        if (DAC_PowerMap == 0 && DACVoltageOutput != 0)
        {
            DAC_PowerMap = MapFloat(DACVoltageOutput, DAC_VoltageOutputThreshold, DAC_VoltageOutputUpperLimit, DAC_PowerThreshold, DAC_PowerUpperLimit);
        }

        Serial.printf("%04.3f V", DACVoltageOutput);
        Serial.printf("\t# %04d", WriteValue);
        Serial.printf("\t%15.1f W", DAC_PowerMap);
        Serial.printf("\t%3d", DACPowerPercentage);
        Serial.println(" %");
    }

} // DAC_WriteVoltage

// DAC Output Voltage Based on BasePower PreScaled to BaseValue - Typically EXPORTED Power ActivePowerExportCT1, DACLocalPower or DACRemotePower
void DAC_WritePower(float DAC_OutputPower = 0, int DAC_Channel = 0)
{
    if (int(DACPowerOutput) != int(DAC_OutputPower) || DAC_OutputPower == DAC_PowerThreshold)
    {
        // Store Last Change (Not to DAC EEPROM)
        DACPowerOutput = DAC_OutputPower;

        // Set and Store Max and Min Power Window Limits (Top and Tail)
        if (DACPowerOutput >= DAC_PowerUpperLimit)
            DACPowerOutput = DAC_PowerUpperLimit;

        if (DACPowerOutput <= DAC_PowerThreshold)
            DACPowerOutput = DAC_PowerThreshold;

        // Map Power to Voltage and Write
        float Local_Value = MapFloat(DACPowerOutput, DAC_PowerThreshold, DAC_PowerUpperLimit, DAC_VoltageOutputThreshold, DAC_VoltageOutputUpperLimit);
        DAC_WriteVoltage(Local_Value, DAC_Channel, DACPowerOutput);
    }

} // DAC_WritePower

// **************** Calibration Functions ****************

// 0 Fixed Outputs for Calibration
void DAC_Calibrate(int DAC_Channel = 0) // 0 = All Channels or 1-4
{
    // Fix to Required Test Voltage (Default 1.5V)
    float Local_Value = 1.5;

    Serial.println("Fixed Outputs for Calibration");

    DAC_WriteVoltage(Local_Value, DAC_Channel);

    delay(3000);

    // DAC_OutputVoltage = 0; // Fix to Required Test Voltage (Default 0)

    DAC_WriteVoltage(0, DAC_Channel);

} // DAC_Calibrate

// 1 Fixed Ramped Outputs for Calibration
void DAC_CalibrateStepRamp(int DAC_Channel = 0) // 0 = All Channels or 1-4
{
    int Delay_ms = 1000;     // Inter Step Delay in ms (Default 2000 = 2 Seconds)
    float StepVoltage = 0.5; // Inter Step Voltage Change in Volts (Default 0.5 V = 500 mV)

    Serial.println("Fixed Ramped Outputs for Calibration");

    for (float Local_Value = DAC_VoltageOutputThreshold; Local_Value <= (DAC_VoltageOutputUpperLimit + DAC_VoltageOutputThreshold); Local_Value += StepVoltage)
    {
        DAC_WriteVoltage(Local_Value, DAC_Channel);
        delay(Delay_ms);
    }

    Serial.println("");
} // DAC_CalibrateStepRamp

// 2 Ramped Outputs for Testing
void DAC_CalibrateSlowRamp(int DAC_Channel = 0) // 0 = All Channels or 1-4
{
    int Delay_ms = 25;        // Inter Step Delay in ms (Default 50 = 50 Milliseconds)
    float StepVoltage = 0.10; // Inter Step Voltage Change in Volts (Default 0.1 V = 100 mV) 0.001 V = 1 mV

    Serial.println("Ramped Outputs for Testing");

    for (float Local_Value = DAC_VoltageOutputThreshold; Local_Value <= (DAC_VoltageOutputUpperLimit + DAC_VoltageOutputThreshold); Local_Value += StepVoltage)
    {
        DAC_WriteVoltage(Local_Value, DAC_Channel);
        delay(Delay_ms);
    }

    for (float Local_Value = DAC_VoltageOutputUpperLimit; Local_Value >= DAC_VoltageOutputThreshold; Local_Value -= StepVoltage)
    {
        DAC_WriteVoltage(Local_Value, DAC_Channel);
        delay(Delay_ms);
    }

    Serial.println("");
} // DAC_CalibrateSlowRamp

// 3 Fixed Ramped Power Outputs for Calibration
void DAC_CalibrateStepPowerRamp(int DAC_Channel = 0) // 0 = All Channels or 1-4
{
    int Delay_ms = 200;    // Inter Step Delay in ms (Default 200 = 0.2 Seconds)
    float StepPower = 100; // Inter Step Power Change in Watts (Default 100W)

    Serial.println("Fixed Ramped Power Outputs for Calibration");

    for (float Local_Value = 0; Local_Value <= (DAC_PowerUpperLimit + DAC_PowerThreshold); Local_Value += StepPower)
    {
        DAC_WritePower(Local_Value, DAC_Channel);
        delay(Delay_ms);
    }

    Serial.println("");
} // DAC_CalibrateStepPowerRamp