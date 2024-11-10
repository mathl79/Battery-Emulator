#ifndef __HW_ESP32_S3_DEVKIT_H__
#define __HW_ESP32_S3_DEVKIT_H__

// Pins 35,36,37 are reserved if the module has OctalSPI PSRAM
// Board boot-up time
#define BOOTUP_TIME 1000  // Time in ms it takes before system is considered fully started up

// Core assignment
#define CORE_FUNCTION_CORE 1
#define MODBUS_CORE 0
#define WIFI_CORE 0

// NATIVE CAN settings. select desired CAN library for the ESP32 TWAI Module
#define CAN_0_TYPE LIB_ACAN_ESP32  // 1:ESP32CAN, 2:ACAN_ESP32

// CAN1 PIN mappings, do not change these unless you are adding on extra hardware to the PCB
#define CAN_TX_PIN GPIO_NUM_27
#define CAN_RX_PIN GPIO_NUM_26
#define CAN_SE_PIN 23

// RS485
#define PIN_5V_EN 16
#define RS485_EN_PIN 17  // 17 /RE
#define RS485_TX_PIN 22  // 21
#define RS485_RX_PIN 21  // 22
#define RS485_SE_PIN 19  // 22 /SHDN

// CAN over SPI2(HSPI) below.
// SPI2 has fixed Pin mapping but higher performance
#define MCP2515_SCK 14   // SCK input of MCP2515
#define MCP2515_MOSI 13  // SDI input of MCP2515
#define MCP2515_MISO 12  // SDO output of MCP2515 | input only, without pullup/down resistors
#define MCP2515_CS 15    // CS input of MCP2515
#define MCP2515_INT 11   // INT output of MCP2515 | input only, without pullup/down resistors

// CAN2 over SPI3(VSPI) defines below
//SPI3 can be muxed to any pins
#define MCP2515_2_SCK SCK    // SCK input of MCP2515
#define MCP2515_2_MOSI MOSI  // SDI input of MCP2515
#define MCP2515_2_MISO MISO  // SDO output of MCP2515 | input only, without pullup/down resistors
#define MCP2515_2_CS SS      // CS input of MCP2515
#define MCP2515_2_INT 11     // INT output of MCP2515   input only, without pullup/down resistors

// CAN_FD defines
// CAN over SPI2(VSPI) below.
// SPI2 has fixed Pin mapping but higher performance
#define MCP2517_SCK 14  // SCK input of MCP2517
#define MCP2517_SDI 13  // SDI input of MCP2517
#define MCP2517_SDO 12  // SDO output of MCP2517
#define MCP2517_CS 15   // CS input of MCP2517
#define MCP2517_INT 11  // INT output of MCP2517

#define MCP2517_2_SCK 5   // SCK input of MCP2517
#define MCP2517_2_SDI 18  // SDI input of MCP2517
#define MCP2517_2_SDO 19  // SDO output of MCP2517
#define MCP2517_2_CS 23   // CS input of MCP2517
#define MCP2517_2_INT 11  // INT output of MCP2517

#if CONFIG_IDF_TARGET_ESP32S2 || CONFIG_IDF_TARGET_ESP32S3
#define VSPI FSPI
#endif

// CHAdeMO support pin dependencies
#define CHADEMO_PIN_2 2
#define CHADEMO_PIN_10 5
#define CHADEMO_PIN_7 30
#define CHADEMO_PIN_4 4
#define CHADEMO_LOCK 17

// Contactor handling
#define POSITIVE_CONTACTOR_PIN 32
#define NEGATIVE_CONTACTOR_PIN 33
#define PRECHARGE_PIN 25

// SMA CAN contactor pins
#define INVERTER_CONTACTOR_ENABLE_PIN 5

// LED
#define LED_PIN 4
#define LED_MAX_BRIGHTNESS 40

// Equipment stop pin
#define EQUIPMENT_STOP_PIN 7

/* ----- Error checks below, don't change (can't be moved to separate file) ----- */
#ifndef HW_CONFIGURED
#define HW_CONFIGURED
#else
#error Multiple HW defined! Please select a single HW
#endif

#ifdef CHADEMO_BATTERY
#endif

#ifdef BMW_I3_BATTERY
#ifdef CONTACTOR_CONTROL
#error GPIO PIN 25 cannot be used for both BMWi3 Wakeup and contactor control. Disable CONTACTOR_CONTROL
#endif
#endif

#endif
