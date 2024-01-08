#ifndef __USER_SETTINGS_H__
#define __USER_SETTINGS_H__

/* This file contains all the user configurable settings for the Battery-Emulator software */
/* To switch between batteries/inverters, uncomment a line to enable, comment out to disable. */
/* There are also some options for battery limits and extra functionality */

/* Select battery used */
//#define BMW_I3_BATTERY
//#define CHADEMO_BATTERY
//#define IMIEV_CZERO_ION_BATTERY
//#define KIA_HYUNDAI_64_BATTERY
#define NISSAN_LEAF_BATTERY
//#define RENAULT_ZOE_BATTERY
//#define TESLA_MODEL_3_BATTERY
//#define TEST_FAKE_BATTERY

/* Select inverter communication protocol. See Wiki for which to use with your inverter: https://github.com/dalathegreat/BYD-Battery-Emulator-For-Gen24/wiki */
//#define BYD_CAN          //Enable this line to emulate a "BYD Battery-Box Premium HVS" over CAN Bus
#define BYD_MODBUS       //Enable this line to emulate a "BYD 11kWh HVM battery" over Modbus RTU
//#define LUNA2000_MODBUS  //Enable this line to emulate a "Luna2000 battery" over Modbus RTU
//#define PYLON_CAN        //Enable this line to emulate a "Pylontech battery" over CAN bus
//#define SMA_CAN          //Enable this line to emulate a "BYD Battery-Box H 8.9kWh, 7 mod" over CAN bus
//#define SOFAR_CAN        //Enable this line to emulate a "Sofar Energy Storage Inverter High Voltage BMS General Protocol (Extended Frame)" over CAN bus
//#define SOLAX_CAN        //Enable this line to emulate a "SolaX Triple Power LFP" over CAN bus

/* Battery settings */
#define BATTERY_WH_MAX \
  30000  //Battery size in Wh (Maximum value for most inverters is 65000 [65kWh], you can use larger batteries but do not set value over 65000!
#define MAXPERCENTAGE \
  800  //80.0% , Max percentage the battery will charge to (App will show 100% once this value is reached)
#define MINPERCENTAGE \
  200  //20.0% , Min percentage the battery will discharge to (App will show 0% once this value is reached)
#define MAXCHARGEAMP \
  300  //30.0A , BYD CAN specific setting, Max charge speed in Amp (Some inverters needs to be artificially limited)
#define MAXDISCHARGEAMP \
  300  //30.0A , BYD CAN specific setting, Max discharge speed in Amp (Some inverters needs to be artificially limited)
//define INTERLOCK_REQUIRED //Nissan LEAF specific setting, if enabled requires both high voltage conenctors to be seated before starting

/* Other options */
//#define DEBUG_VIA_USB  //Enable this line to have the USB port output serial diagnostic data while program runs
//#define CONTACTOR_CONTROL         //Enable this line to have pins 25,32,33 handle automatic precharge/contactor+/contactor- closing sequence
//#define PWM_CONTACTOR_CONTROL     //Enable this line to use PWM logic for contactors, which lower power consumption and heat generation
//#define DUAL_CAN                  //Enable this line to activate an isolated secondary CAN Bus using add-on MCP2515 controller (Needed for FoxESS inverters)
//#define SERIAL_LINK_RECEIVER      //Enable this line to receive battery data over RS485 pins from another Lilygo (This LilyGo interfaces with inverter)
//#define SERIAL_LINK_TRANSMITTER   //Enable this line to send battery data over RS485 pins to another Lilygo (This LilyGo interfaces with battery)

// High level connectivity settings below. See USER_SETTINGS.cpp for detailed settings.

// Enabling any define below enables Wifi functionality. See USER_SETTINGS.cpp for the Wifi settings.
#define USE_WEBSERVER             //Enable this line to run the webserver and enable OTA updates.
#define USE_MQTT                  //Enable this line to enable MQTT functionality. See USER_SETTINGS.cpp for the MQTT settings.

// Various Wifi specific defines, placed here to remove the need for messier code and issues with optimizations/linking.
//#define ENABLE_AP                 //Enable this line to run Wifi in AP mode (only broadcasting the LilyGO access point SSID).
#define ENABLE_STA                //Enable this line to run Wifi in STA mode (connected to your home network).

#define MQTT_SUBSCRIPTIONS    {"my/topic/abc", "my/other/topic"}
#define MQTT_SERVER           "192.168.xxx.yyy"
#define MQTT_PORT             1883

// ---- Derived defines below ----

#if defined(USE_WEBSERVER) || defined(USE_MQTT)
  #define USE_WIFI
#endif

#if defined(ENABLE_AP) && defined(ENABLE_STA)
  #define WIFI_MODE WIFI_AP_STA
#elif defined(ENABLE_AP)
  #define WIFI_MODE WIFI_AP
#elif defined(ENABLE_STA)
  #define WIFI_MODE WIFI_STA
#else
  #define WIFI_MODE WIFI_OFF // Just in case
#endif

#endif
