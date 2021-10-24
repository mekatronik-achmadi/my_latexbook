#include "ch.h"
#include "hal.h"
#include "gfx.h"

#include "chprintf.h"
#include "i2c.h"
#include "i2c_lld.h"
#include "pal_lld.h"
#include "stdint.h"

#include "data.h"
#include "sensor.h"

#define I2CPORT I2CD2

/************ Fake I2C Request ************/

#define addr 0b1001100

static uint8_t rx_data[2];
static i2cflags_t errors = 0;

/* This is main function. */
void request_fake(void){
  msg_t status = MSG_OK;
  systime_t tmo = MS2ST(10);

  i2cAcquireBus(&I2CPORT);
  status = i2cMasterReceiveTimeout(&I2CPORT, addr, rx_data, 2, tmo);
  i2cReleaseBus(&I2CPORT);

  if (status == MSG_RESET){
    errors = i2cGetErrors(&I2CPORT);
  }
}

/*
 * Fake polling thread.
 */
static THD_WORKING_AREA(PollFakeThreadWA, 256);
static THD_FUNCTION(PollFakeThread, arg) {

  (void)arg;

  chRegSetThreadName("PollFake");
  while (true) {
    osalThreadSleepMilliseconds(16);
    request_fake();
  }
}

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

uint16_t HTU21DGetVal(void){
  systime_t tmo = MS2ST(10);

  sensor_tx_data[0] = 0xE3;

  i2cAcquireBus(&I2CPORT);
  i2cMasterTransmitTimeout(&I2CPORT, addr_sensor,sensor_tx_data, 1, sensor_rx_data, 2, tmo);
  i2cReleaseBus(&I2CPORT);

  return (sensor_rx_data[0]<<8) | sensor_rx_data[1];
}

uint8_t HTU21DTest(void){
  msg_t status = MSG_OK;
  systime_t tmo = MS2ST(4);

  sensor_tx_data[0] = 0xE3;

  i2cAcquireBus(&I2CPORT);
  status = i2cMasterTransmitTimeout(&I2CPORT, addr_sensor,sensor_tx_data, 1, sensor_rx_data, 2, tmo);
  i2cReleaseBus(&I2CPORT);

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

  palSetPadMode(GPIOB,10,PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
  palSetPadMode(GPIOB,11,PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
  i2cStart(&I2CPORT, &i2cfg);

  chThdSleepMilliseconds(10);

  chThdCreateStatic(PollFakeThreadWA,sizeof(PollFakeThreadWA),NORMALPRIO,PollFakeThread,NULL);

  HTU21DStart();
}