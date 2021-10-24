#include "ch.h"
#include "hal.h"
#include "gfx.h"

#include "chprintf.h"
#include "i2c_lld.h"
#include "pal_lld.h"
#include "stdint.h"

#include "data.h"
#include "sensor.h"

#define addr_sensor 0x40

/* buffers */
static uint8_t sensor_rx_data[8];
static uint8_t sensor_tx_data[8];

void HTU21DStart(void){
  systime_t tmo = MS2ST(4);

  sensor_tx_data[0] = 0xFF;
  
  /* sending */
  i2cAcquireBus(&I2CD1);
  i2cMasterTransmitTimeout(&I2CD1, addr_sensor,sensor_tx_data, 1, sensor_rx_data, 0, tmo);
  i2cReleaseBus(&I2CD1);
}

uint16_t HTU21DGetVal(void){
  systime_t tmo = MS2ST(4);

  sensor_tx_data[0] = 0xE3;

  i2cAcquireBus(&I2CD1);
  i2cMasterTransmitTimeout(&I2CD1, addr_sensor,sensor_tx_data, 1, sensor_rx_data, 2, tmo);
  i2cReleaseBus(&I2CD1);

  return (sensor_rx_data[0]<<8) | sensor_rx_data[1];
}

uint8_t HTU21DTest(void){
  msg_t status = MSG_OK;
  systime_t tmo = MS2ST(4);

  sensor_tx_data[0] = 0xE3;

  i2cAcquireBus(&I2CD1);
  status = i2cMasterTransmitTimeout(&I2CD1, addr_sensor,sensor_tx_data, 1, sensor_rx_data, 2, tmo);
  i2cReleaseBus(&I2CD1);

  return status;
}

/************ Actual I2C ************/

/*
 * I2C1 config.
 */
static const I2CConfig i2cfg = {
    OPMODE_I2C,
    400000,
    FAST_DUTY_CYCLE_2,
};

void sensor_init(void){
  palSetPadMode(GPIOB,6,PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
  palSetPadMode(GPIOB,7,PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
  i2cStart(&I2CD1, &i2cfg);
  HTU21DStart();
}