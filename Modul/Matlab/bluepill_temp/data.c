#include "ch.h"
#include "hal.h"
#include "gfx.h"

#include "chprintf.h"
#include "stdint.h"

#include "data.h"

uint16_t senTemp, senHumid;

/**
 * @brief   data point array for display.
 */
point vdata[N_DATA];

/**
 * @brief   set data array to zero.
 *
 */
static void data_zeroing(void){
    uint16_t i;

    for(i=0;i<N_DATA;i++){
       vdata[i].x = i;
       vdata[i].y = 0;
    }
}

/**
 * @brief   set data shifting by 1.
 * @pre     @p LEFT_TO_RIGHT must defined.
 *
 */
static void data_shifting(void){
    uint16_t i;

#if LEFT_TO_RIGHT
    for(i=0;i<N_DATA-1;i++){
        vdata[i].y = vdata[i+1].y;
    }
#else
    for(i=N_DATA-1;i>0;i--){
        vdata[i].y = vdata[i-1].y;
    }
#endif
}

static THD_WORKING_AREA(waData, 512);
static THD_FUNCTION(thdData, arg) {

    (void)arg;

    chRegSetThreadName("data update");
    while (true) {
        data_shifting();
        
#if LEFT_TO_RIGHT
        vdata[N_DATA-1].y = DATA_SCALE * senTemp;
#else
        vdata[0].y = DATA_SCALE * senTemp;
#endif

        chThdSleepMilliseconds(1000);
    }
}

void data_init(void){
    data_zeroing();
    chThdCreateStatic(waData, sizeof(waData), NORMALPRIO, thdData, NULL);
}