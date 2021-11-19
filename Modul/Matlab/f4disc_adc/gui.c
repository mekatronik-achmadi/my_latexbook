#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "ch.h"
#include "hal.h"
#include "gfx.h"

#include "chprintf.h"

#include "gui.h"
#include "data.h"

extern adcsample_t v1, v2, dV;
extern point vdata[N_DATA];

float volt;

/**
 * @brief   object for overall graphic GUI
 */
static GGraphObject g;

/**
 * @brief   graphic line configuration
 */
static GGraphStyle GraphLine = {
    { GGRAPH_POINT_DOT, 10, White },          // Point
    { GGRAPH_LINE_SOLID, 10, White },          // Line
    { GGRAPH_LINE_SOLID, 0, Gray },        // X axis
    { GGRAPH_LINE_SOLID, 0, Gray },        // Y axis
    { GGRAPH_LINE_DOT, 5, Gray, 50 },      // X grid
    { GGRAPH_LINE_DOT, 5, Gray, 50 },     // Y grid
    GWIN_GRAPH_STYLE_POSITIVE_AXIS_ARROWS   // Flags
};

/**
 * @brief   object for graphic and console window
 */
GHandle gh,gc;

/**
 * @brief   console string variable
 */
char txt_value[32];

/*
 * Green LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waGui, 512);
static THD_FUNCTION(thdGui, arg) {

  (void)arg;
  chRegSetThreadName("blinker");
  while (true) {
    guiLoop();
    chThdSleepMilliseconds(10);
  }
}

void guiInit(void){
    font_t gfont;

    gdispSetOrientation(GDISP_ROTATE_90);

    gfont = gdispOpenFont("fixed_7x14");
    gwinSetDefaultFont(gfont);

    {
      GWindowInit wi;
      gwinClearInit(&wi);

      wi.show = true;

      wi.x = 0;
      wi.y = 0;
      wi.width = gdispGetWidth();
      wi.height = (gdispGetHeight()/16)*14;
      gh = gwinGraphCreate(&g, &wi);

      wi.x = 0;
      wi.y = (gdispGetHeight()/16)*14;;
      wi.width = gdispGetWidth();
      wi.height = (gdispGetHeight()/16)*2;

      gc = gwinConsoleCreate(0, &wi);

    }

  gwinGraphSetOrigin(gh, 0, 0);
  gwinGraphSetStyle(gh, &GraphLine);

  gwinClear(gc);
  gwinPrintf(gc, "System Ready \n");
  gwinGraphStartSet(gh);
  gwinGraphDrawAxis(gh);

  chThdCreateStatic(waGui, sizeof(waGui), NORMALPRIO, thdGui, NULL);
}

void guiLoop(void){
  gwinGraphStartSet(gh);
  gwinGraphDrawAxis(gh);

  gwinGraphDrawPoints(gh, vdata, sizeof(vdata)/sizeof(vdata[0]));

  chsnprintf(txt_value,32,"V1=%4i ",v1);
  gwinPrintf(gc, txt_value);

  chsnprintf(txt_value,32,"V2=%4i ",v2);
  gwinPrintf(gc, txt_value);

  chsnprintf(txt_value,32,"dV=%i ",dV);
  gwinPrintf(gc, txt_value);

  volt = VOLT_CALIB * dV;
  chsnprintf(txt_value,32,"v=%4.2f ",volt);
  gwinPrintf(gc, txt_value);

  chThdSleepMilliseconds(100);

  gwinClear(gh);
  gwinClear(gc);
}

void guiTest(void){
}
