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
 * @brief FreeRTOS taskfunction
 *
 * @param[in] *pvParameters: Optional parameter pointer
 * 
 * @return void
 */
void wifi_taskfunction(void* pvParameter);

#endif
