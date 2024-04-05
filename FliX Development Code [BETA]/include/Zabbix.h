/*
  Dave Williams, DitroniX 2019-2023 (ditronix.net)
  Full header information in README

  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  Further information, details and examples can be found on our website wiki pages ditronix.net/wiki and also github.com/DitroniX
*/

// NOTE: THIS CODE IS UNDER DEVELOPMENT

// Integration with Zabbix, Agent, Local and Cloud, is WIP

// Libraries
#include <Arduino.h>

// ****************  VARIABLES / DEFINES / STATIC / STRUCTURES ****************

// Enable Publishing
boolean EnableZabbix = false; // Change to true, to enable Loop reading and sending data to Zabbix.  Default false.

// ######### FUNCTIONS #########

// Initialise Zabbix
void InitialiseZabbix()
{
  if (EnableZabbix == true && WiFi.status() == WL_CONNECTED)
  {
    // Preable WIP
    Serial.println("Initialised Zabbix");
    Serial.println("Zabbix Enabled - Register Values Will be Published");
  }
  else
  {
    Serial.println("Zabbix Publishing Disabled");
  }

} // void InitialiseZabbix()