#include "ch.h"
#include "hal.h"
#include "gfx.h"

#include "chprintf.h"
#include "stdint.h"

#include "gui.h"
#include "data.h"
#include "sensor.h"

extern uint16_t senTemp, senHumid;
extern point vdata[N_DATA];

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
char txt_value[16];

void gui_init(void){
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
      wi.height = (gdispGetHeight()/16)*13;
      gh = gwinGraphCreate(&g, &wi);

      wi.x = 0;
      wi.y = (gdispGetHeight()/16)*13;;
      wi.width = gdispGetWidth();
      wi.height = (gdispGetHeight()/16)*3;

      gc = gwinConsoleCreate(0, &wi);

    }

  gwinGraphSetOrigin(gh, 0, 0);
  gwinGraphSetStyle(gh, &GraphLine);

  gwinClear(gc);
  gwinPrintf(gc, "System Ready \n");
  gwinGraphStartSet(gh);
  gwinGraphDrawAxis(gh);
}

void gui_loop(void){
  gwinGraphStartSet(gh);
  gwinGraphDrawAxis(gh);

  gwinGraphDrawPoints(gh, vdata, sizeof(vdata)/sizeof(vdata[0]));

  chsnprintf(txt_value,16,"T=%4i",senTemp);
  gwinPrintf(gc, txt_value);

  gfxSleepMilliseconds(10);

  gwinClear(gh);
  gwinClear(gc);
}

void gui_test(void){
}
