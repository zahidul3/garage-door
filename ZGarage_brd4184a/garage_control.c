/*
 * garage_control.c
 *
 *  Created on: Oct 3, 2021
 *      Author: zahidhaq
 */

#include <stdbool.h>
#include "em_gpio.h"
#include "sl_simple_timer.h"
#include "sl_simple_led_instances.h"
#include "app_log.h"
#include "garage_control.h"

#define SL_SIMPLE_GARAGE_POLARITY       1
#define SL_SIMPLE_GARAGE_PORT           gpioPortA
#define SL_SIMPLE_GARAGE_PIN            8

#define GARAGE_TIME_MS                  1000
#define GARAGE_LED                      SL_SIMPLE_LED_INSTANCE(0)

typedef enum{
  GARAGE_UNKNOWN,
  GARAGE_START,
  GARAGE_STARTING,
  GARAGE_IDLE
} GARAGE_STATE;

uint32_t RuntimeSeconds = 0;
static volatile GARAGE_STATE garageState = GARAGE_UNKNOWN;

// Advertising timer
static sl_simple_timer_t garage_timer;

// -----------------------------------------------------------------------------
// Private function declarations
static void garage_timer_cb(sl_simple_timer_t *timer, void *data);

static void printGarageState(GARAGE_STATE gState)
{
  switch(gState)
  {
    case GARAGE_START: app_log_info("State: GARAGE_START\n\r"); break;
    case GARAGE_STARTING: app_log_info("State: GARAGE_STARTING\n\r"); break;
    case GARAGE_IDLE: app_log_info("State: GARAGE_IDLE\n\r"); break;
  }
}

static void garage_timer_cb(sl_simple_timer_t *timer, void *data)
{
  (void)timer;
  (void)data;

  GARAGE_STATE currentGarageState = garageState;

  // Turn on/off garage door, close/open relay switch
  //app_log_info("In garage_timer_cb: %d\n\r", RuntimeSeconds++);
  switch(garageState)
  {
    case GARAGE_START:
      GarageControl_PinSet();
      garageState = GARAGE_STARTING;
      break;
    case GARAGE_STARTING:
      GarageControl_PinClear();
      garageState = GARAGE_IDLE;
      break;
    case GARAGE_IDLE:
      // should be idle most time
      break;
    default:
      garageState = GARAGE_IDLE;
      break;
  }

  // print if state changed
  if(currentGarageState != garageState)
    printGarageState(currentGarageState);

  // Toggle advertising LED state
  sl_led_toggle(GARAGE_LED);
}

void GarageControl_init(void)
{
  sl_status_t sc;

  GPIO_PinModeSet(SL_SIMPLE_GARAGE_PORT,
                  SL_SIMPLE_GARAGE_PIN,
                  gpioModePushPull,
                  !SL_SIMPLE_GARAGE_POLARITY);

  GPIO_SlewrateSet(SL_SIMPLE_GARAGE_PORT, 7, 7);

  // Start timer to alternate advertising data
  sc = sl_simple_timer_start(&garage_timer,
                             GARAGE_TIME_MS,
                             garage_timer_cb,
                             NULL,
                             true);
  if (SL_STATUS_OK != sc) {
      app_log_error("sl_simple_timer_start ERROR: %d", sc);
  }
}

void GarageControl_PinSet(void)
{
  GPIO_PinOutSet(SL_SIMPLE_GARAGE_PORT, SL_SIMPLE_GARAGE_PIN);
  //app_log_info("GarageControl_PinSet\n\r");
}

void GarageControl_PinClear(void)
{
  GPIO_PinOutClear(SL_SIMPLE_GARAGE_PORT, SL_SIMPLE_GARAGE_PIN);
  //app_log_info("GarageControl_PinClear\n\r");
}

void GarageControl_Open(void)
{
  app_log_debug("GarageControl_Open\n\r");
  garageState = GARAGE_START;
}
