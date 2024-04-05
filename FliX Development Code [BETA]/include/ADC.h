/*
  Dave Williams, DitroniX 2019-2023 (ditronix.net)
  Full header information in README

  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  Further information, details and examples can be found on our website wiki pages ditronix.net/wiki and also github.com/DitroniX
*/

// NOTE: THIS CODE IS UNDER DEVELOPMENT FOR THE IPEC/IPEX BRANCH. DAVE WILLIAMS November 2023

// Libraries
#include <Arduino.h>
#include <Adafruit_ADS1X15.h>  //https://github.com/adafruit/Adafruit_ADS1X15/blob/master/examples/singleended/singleended.ino

// ****************  VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

Adafruit_ADS1115 ipex1_adc; // 16bit ADC

#define IPEX1_ADS1115 0x49 // Default IPEX-1 ADS1115 Address

// WORK IN POREGRESS

// Initialise IPEX ADS1115 ADC (Default Address 0x49)
void Initialise_ADS1115_ADC()
{

  if (!ipex1_adc.begin(IPEX1_ADS1115))
  {
    Serial.println("Failed to initialize IPEX1 ADS1115");
    while (1)
    {
      delay(10);
    }
  }
  else
  {
    Serial.println("ADC (ADS1115) Initialised\n");

    int16_t adc0, adc1, adc2, adc3;
    float volts0, volts1, volts2, volts3;

    adc0 = ipex1_adc.readADC_SingleEnded(0);
    adc1 = ipex1_adc.readADC_SingleEnded(1);
    adc2 = ipex1_adc.readADC_SingleEnded(2);
    adc3 = ipex1_adc.readADC_SingleEnded(3);

    volts0 = ipex1_adc.computeVolts(adc0);
    volts1 = ipex1_adc.computeVolts(adc1);
    volts2 = ipex1_adc.computeVolts(adc2);
    volts3 = ipex1_adc.computeVolts(adc3);

    Serial.print("AIN0: ");
    Serial.print(adc0);
    Serial.print("  ");
    Serial.print(volts0);
    Serial.println("V");
    Serial.print("AIN1: ");
    Serial.print(adc1);
    Serial.print("  ");
    Serial.print(volts1);
    Serial.println("V");
    Serial.print("AIN2: ");
    Serial.print(adc2);
    Serial.print("  ");
    Serial.print(volts2);
    Serial.println("V");
    Serial.print("AIN3: ");
    Serial.print(adc3);
    Serial.print("  ");
    Serial.print(volts3);
    Serial.println("V");
  }
}
