#include "ch.h"
#include "hal.h"
#include "gfx.h"

#include "chprintf.h"
#include "shell.h"

#include "gui.h"

#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(512)

static THD_WORKING_AREA(waLED, 128);
static THD_FUNCTION(thdLED, arg) {

    (void)arg;

    chRegSetThreadName("blinker");
    while (true) {
        palTogglePad(GPIOC,13);
        chThdSleepMilliseconds(100);
    }
}

static THD_WORKING_AREA(waGUI, 2048);
static THD_FUNCTION(thdGUI, arg) {

    (void)arg;

    chRegSetThreadName("gui");
    while (true) {
        gui_loop();
        chThdSleepMicroseconds(10);
    }
}

static thread_t *shelltp = NULL;

static void cmd_test(BaseSequentialStream *chp, int argc, char *argv[]) {
    (void)argv;
    if (argc > 0) {chprintf(chp, "Usage: test\r\n");return;}

    chprintf(chp,"Serial OK\r\n");
    gui_test();
}

static const ShellCommand commands[] = {
    {"test", cmd_test},
    {NULL, NULL}
};

static const ShellConfig shell_cfg = {
    (BaseSequentialStream *)&SD1,
    commands
};

int main(void) {

  gfxInit();

  palSetPadMode(GPIOA,9,PAL_MODE_STM32_ALTERNATE_PUSHPULL); //TX
  palSetPadMode(GPIOA,10,PAL_MODE_INPUT); //RX
  sdStart(&SD1,NULL);

  shellInit();

  gui_init();
  chThdCreateStatic(waGUI, sizeof(waGUI), NORMALPRIO, thdGUI, NULL);

  chThdCreateStatic(waLED, sizeof(waLED), NORMALPRIO, thdLED, NULL);

  while(true){
    if (!shelltp)
      shelltp = shellCreate(&shell_cfg, SHELL_WA_SIZE, NORMALPRIO);
    else if (chThdTerminatedX(shelltp)) {
      chThdRelease(shelltp);
      shelltp = NULL;
    }
    chThdSleepMilliseconds(100);
  }
}
