#include "wifi.h"
#include <WiFi.h>
#include <freertos/FreeRTOS.h>
#include "../../../USER_SETTINGS.h"
#include "../mqtt/mqtt.h"
#include "../webserver/webserver.h"

// Wifi connect time declarations and definition
unsigned long wifi_connect_start_time;
unsigned long wifi_connect_current_time;
const long wifi_connect_timeout = 5000;  // Timeout for WiFi connect in milliseconds

static void wifi_reconnect(void) {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.reconnect();
  }
}

static void init_STA(void) {

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  wifi_connect_start_time = millis();
  wifi_connect_current_time = wifi_connect_start_time;
  while ((wifi_connect_current_time - wifi_connect_start_time) <= wifi_connect_timeout &&
         WiFi.status() != WL_CONNECTED) {  // do this loop for up to 5000ms
    // to break the loop when the connection is not established (wrong ssid or password).
    delay(500);
    Serial.print(".");
    wifi_connect_current_time = millis();
  }
  if (WiFi.status() == WL_CONNECTED) {  // WL_CONNECTED is assigned when connected to a WiFi network
    // Print local IP address and start web server
    Serial.println("");
    Serial.print("Connected to WiFi network: ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.print("Not connected to WiFi network: ");
    Serial.println(ssid);
    Serial.println("Please check WiFi network name and password, and if WiFi network is available.");
  }
}

static void init_AP(void) {
  Serial.print("Creating Access Point: ");
  Serial.println(ssidAP);
  Serial.print("With password: ");
  Serial.println(passwordAP);

  WiFi.softAP(ssidAP, passwordAP);

  IPAddress IP = WiFi.softAPIP();
  Serial.println("Access Point created.");
  Serial.print("IP address: ");
  Serial.println(IP);
}

static void init_wifi(void) {
  WiFi.mode(WIFI_MODE);
#ifdef ENABLE_AP
  init_AP();
#endif
#ifdef ENABLE_STA
  init_STA();
#endif
}

// Exported functions below

void init_wireless(void) {
  xTaskCreate(wifi_taskfunction, "Wifi task", 1024 * 8, NULL, 1, NULL);
}

void wifi_taskfunction(void* pvParameters) {
  init_wifi();
  init_webserver();
  init_mqtt();

  while (true) {
    wifi_reconnect();
    if(WiFi.status() == WL_CONNECTED) {
      webserver_loop();
      mqtt_loop();
    }
    delay(1);
  }
}
