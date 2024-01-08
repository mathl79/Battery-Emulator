#include <Arduino.h>
#include "USER_SETTINGS.h"

#ifdef USE_WIFI

// MQTT
// For more detailed settings, see mqtt.h
#ifdef USE_MQTT
const char* mqtt_user = "REDACTED";
const char* mqtt_password = "REDACTED";
#endif // USE_MQTT

const char* ssid = "REDACTED";          // maximum of 63 characters;
const char* password = "REDACTED";  // minimum of 8 characters;
const char* ssidAP = "Battery Emulator";              // maximum of 63 characters;
const char* passwordAP = "123456789";  // minimum of 8 characters; set to NULL if you want the access point to be open

#endif