#ifndef __WIFI_H__
#define __WIFI_H__

extern const char* ssid;
extern const char* password;
extern const char* ssidAP;
extern const char* passwordAP;

/**
 * @brief Initialization function for Wifi
 *
 * @param[in] void
 * 
 * @return void
 */
void init_wireless(void);

/**
 * @brief Returns the WiFi connections status
 *
 * @param[in] void
 * 
 * @return bool: true = connected, false = disconnected
 */
bool wifi_is_connected(void);

#endif
