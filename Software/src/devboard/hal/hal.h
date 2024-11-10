#ifndef _HAL_H_
#define _HAL_H_

#include "../../../USER_SETTINGS.h"

#if defined(HW_LILYGO)
#include "hw_lilygo.h"
#elif defined(HW_STARK)
#include "hw_stark.h"
#elif defined(HW_ESP32_S3_DEVKIT)
#include "hw_ESP32_S3_DEVKIT.h"
#elif defined(HW_SJB_V1)
#include "hw_sjb_v1.h"
#endif

#define LIB_ESP32CAN 1
#define LIB_ACAN_ESP32 2

#endif
