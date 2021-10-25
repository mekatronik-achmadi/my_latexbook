#include "ch.h"
#include "hal.h"

#include "sensor.h"

#define I2CPORT I2CD3

static i2cflags_t errors = 0;

/************ Actual I2C Sensor ************/

#define addr_sensor 0x40

/* buffers */
static uint8_t sensor_rx_data[8];
static uint8_t sensor_tx_data[8];

void HTU21DStart(void){
  systime_t tmo = MS2ST(10);

  sensor_tx_data[0] = 0xFF;
  
  /* sending */
  i2cAcquireBus(&I2CPORT);
  i2cMasterTransmitTimeout(&I2CPORT, addr_sensor,sensor_tx_data, 1, sensor_rx_data, 0, tmo);
  i2cReleaseBus(&I2CPORT);
}

float HTU21DGetVal(void){
  uint16_t HTU21D_ADC_Raw;
  float HTU21D_Temperature;

  systime_t tmo = MS2ST(10);

  sensor_tx_data[0] = 0xE3;

  i2cAcquireBus(&I2CPORT);
  i2cMasterTransmitTimeout(&I2CPORT, addr_sensor,sensor_tx_data, 1, sensor_rx_data, 2, tmo);
  i2cReleaseBus(&I2CPORT);

  HTU21D_ADC_Raw = ((uint16_t)(sensor_rx_data[0] << 8) | (sensor_rx_data[1]));
  HTU21D_Temperature = (float)(HTU21D_ADC_Raw * 175.72 / 65536.00) - 46.85;

  chThdSleepMilliseconds(50);

  return HTU21D_Temperature;
}

uint8_t HTU21DTest(void){
  msg_t status = MSG_OK;
  systime_t tmo = MS2ST(4);

  sensor_tx_data[0] = 0xE3;

  i2cAcquireBus(&I2CPORT);
  status = i2cMasterTransmitTimeout(&I2CPORT, addr_sensor,sensor_tx_data, 1, sensor_rx_data, 2, tmo);
  i2cReleaseBus(&I2CPORT);

  if (status != MSG_OK){
      errors = i2cGetErrors(&I2CPORT);
  }

  return errors;
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
  i2cStart(&I2CPORT, &i2cfg);
  chThdSleepMilliseconds(50);
  HTU21DStart();
}