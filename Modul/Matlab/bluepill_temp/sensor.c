#include "ch.h"
#include "hal.h"
#include "gfx.h"

#include "chprintf.h"
#include "stdint.h"

#include "data.h"
#include "sensor.h"

/************ Fake Thread ************/

#define addr_fake 0b1001100

static uint8_t rx_data[2];
static i2cflags_t errors = 0;

/* This is main function. */
void request_fake(void){
  msg_t status = MSG_OK;
  systime_t tmo = MS2ST(4);

  i2cAcquireBus(&I2CD1);
  status = i2cMasterReceiveTimeout(&I2CD1, addr_fake, rx_data, 2, tmo);
  i2cReleaseBus(&I2CD1);

  if (status == MSG_RESET){
    errors = i2cGetErrors(&I2CD1);
    osalDbgCheck(I2C_ACK_FAILURE == errors);
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

/************ Actual Sensor ************/

#define addr_sensor 0x40

/* buffers */
static uint8_t sensor_rx_data[8];
static uint8_t sensor_tx_data[8];

void HTU21DStart(void){
  msg_t status = MSG_OK;
  systime_t tmo = MS2ST(4);
  
  /* sending */
  i2cAcquireBus(&I2CD1);
  status = i2cMasterTransmitTimeout(&I2CD1, addr_sensor,sensor_tx_data, 4, sensor_rx_data, 0, tmo);
  i2cReleaseBus(&I2CD1);

  osalDbgCheck(MSG_OK == status);
}

void HTU21DGetVal(float *result){
  msg_t status = MSG_OK;
  systime_t tmo = MS2ST(4);

  size_t i = 0;
  int16_t tmp;

  i2cAcquireBus(&I2CD1);
  status = i2cMasterTransmitTimeout(&I2CD1, addr_sensor,sensor_tx_data, 1, sensor_rx_data, 6, tmo);
  i2cReleaseBus(&I2CD1);

  osalDbgCheck(MSG_OK == status);

  for (i=0; i<3; i++){
    tmp = sensor_rx_data[i*2] + (sensor_rx_data[i*2+1] << 8);
    result[i] = tmp;
    result[i] /= 16384; /* convert raw value to G */
  }
}

/************ Actual I2C ************/

/*
 * I2C1 config.
 */
static const I2CConfig i2cfg1 = {
    OPMODE_I2C,
    400000,
    FAST_DUTY_CYCLE_2,
};

void sensor_init(void){
   i2cStart(&I2CD1, &i2cfg1);

    /* Create not responding thread. */
   chThdCreateStatic(PollFakeThreadWA,sizeof(PollFakeThreadWA),NORMALPRIO,PollFakeThread,NULL);
}