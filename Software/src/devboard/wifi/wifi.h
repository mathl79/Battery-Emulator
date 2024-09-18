#ifndef WIFI_H
#define WIFI_H

#include <WiFi.h>
#include <string>
#include "../../include.h"

extern std::string ssid;
extern std::string password;
extern const uint8_t wifi_channel;
extern const char* ssidAP;
extern const char* passwordAP;

void init_WiFi();
void wifi_monitor();
static void connectToWiFi();
static void FullReconnectToWiFi();
static void onWifiConnect(WiFiEvent_t event, WiFiEventInfo_t info);
static void onWifiDisconnect(WiFiEvent_t event, WiFiEventInfo_t info);
static void onWifiGotIP(WiFiEvent_t event, WiFiEventInfo_t info);

#ifdef WIFIAP
void init_WiFi_AP();
#endif  // WIFIAP

#ifdef MDNSRESPONDER
// Initialise mDNS
void init_mDNS();
#endif  // MDNSRESPONDER

#endif
