/*
 * InitETM.c
 *
 * Initialize the ETM module for Z-Wave.
 *
 */

#include <em_cmu.h>

// ETM definitions - ZGM130S Radio Board; BRD4202A
#define ETM_LOC     3            // PC6, PC7, PC8, PC9, PC10
#define ETMCLK_PORT gpioPortC
#define ETMCLK_PIN  6
#define ETMD0_PORT  gpioPortC
#define ETMD0_PIN   7
#define ETMD1_PORT  gpioPortC
#define ETMD1_PIN   8
#define ETMD2_PORT  gpioPortC
#define ETMD2_PIN   9
#define ETMD3_PORT  gpioPortC
#define ETMD3_PIN   10

/**************************************************************************//**
 * @brief Configure EFM32 for ETM trace output for Z-Wave.
 * This function must be called ideally BEFORE main is executed
 * so Ozone will be happy. It can be called after main but you may
 * need to reset the DUT have it power up and run and then Attach And Halt
 * in Ozone so that the trace pins are setup before Ozone tried to break at main.
*****************************************************************************/
void initTraceETM(void)
{
  /* Enable peripheral clocks */
//  CMU_ClockEnable(cmuClock_GPIO, true);     // virtually all apps start the clock to the GPIOs but uncomment if needed.

  CMU_ClockSelectSet(cmuClock_DBG, cmuSelect_AUXHFRCO); // turn on clock to ETM - The advantage of the AUXHFRCO is that it runs even in EM2. Typically 19MHz
//  CMU_ClockSelectSet(cmuClock_DBG, cmuSelect_HFXO); // turn on clock to ETM - HFXO is too fast (39Mhz). The GPIOs support ~20MHz.

  /* Configure trace output */
  /* Enable GPIO Pins for ETM Trace Data output and ETM Clock */
  GPIO_PinModeSet(ETMCLK_PORT, ETMCLK_PIN, gpioModePushPull, 0);
  GPIO_PinModeSet(ETMD0_PORT, ETMD0_PIN, gpioModePushPull, 0);
  GPIO_PinModeSet(ETMD1_PORT, ETMD1_PIN, gpioModePushPull, 0);
  GPIO_PinModeSet(ETMD2_PORT, ETMD2_PIN, gpioModePushPull, 0);
  GPIO_PinModeSet(ETMD3_PORT, ETMD3_PIN, gpioModePushPull, 0);

  GPIO->ROUTELOC1 = (GPIO->ROUTELOC1 & ~_GPIO_ROUTELOC1_MASK)
                  | (ETM_LOC << _GPIO_ROUTELOC1_ETMTCLKLOC_SHIFT)
                  | (ETM_LOC << _GPIO_ROUTELOC1_ETMTD0LOC_SHIFT)
                  | (ETM_LOC << _GPIO_ROUTELOC1_ETMTD1LOC_SHIFT)
                  | (ETM_LOC << _GPIO_ROUTELOC1_ETMTD2LOC_SHIFT)
                  | (ETM_LOC << _GPIO_ROUTELOC1_ETMTD3LOC_SHIFT);

  GPIO->ROUTEPEN = GPIO->ROUTEPEN
                   | GPIO_ROUTEPEN_ETMTCLKPEN
                   | GPIO_ROUTEPEN_ETMTD0PEN
                   | GPIO_ROUTEPEN_ETMTD1PEN
                   | GPIO_ROUTEPEN_ETMTD2PEN
                   | GPIO_ROUTEPEN_ETMTD3PEN;
}
