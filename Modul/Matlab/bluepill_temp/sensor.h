#ifndef _SENSOR_
#define _SENSOR_

#include "sensor.h"
#include <stdint.h>

void HTU21DStart(void);
uint16_t HTU21DGetVal(void);
uint8_t HTU21DTest(void);
void sensor_init(void);

#endif