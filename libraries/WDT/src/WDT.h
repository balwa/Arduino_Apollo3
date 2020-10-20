#ifndef WDT_H
#define WDT_H

#include <Arduino.h>

// Simplified WDT Clock Divider Selections
#define WDT_OFF     WDT_CFG_CLKSEL_OFF      // = 0    Low Power Mode. This setting disables the watch dog timer
#define WDT_128HZ   WDT_CFG_CLKSEL_128HZ    // = 1,   128 Hz LFRC clock
#define WDT_16HZ    WDT_CFG_CLKSEL_16HZ     // = 2    16 Hz LFRC clock
#define WDT_1HZ     WDT_CFG_CLKSEL_1HZ      // = 3,   1 Hz LFRC clock
#define WDT_1_16HZ  WDT_CFG_CLKSEL_1_16HZ   // = 4,   1/16th Hz LFRC clock

class APM3_WDT
{
public:
  APM3_WDT();

  // Default watchdog timer configuration structure
  am_hal_wdt_config_t watchdogConfig = {

    // Configuration values for generated watchdog timer event.
    .ui32Config = AM_HAL_WDT_LFRC_CLK_16HZ | AM_HAL_WDT_ENABLE_RESET | AM_HAL_WDT_ENABLE_INTERRUPT,

    // Number of watchdog timer ticks allowed before a watchdog interrupt event is generated
    .ui16InterruptCount = 16 * 4, // Set WDT interrupt timeout for 4 seconds (16 * 4) / 16 = 4

    // Number of watchdog timer ticks allowed before the watchdog will issue a system reset
    .ui16ResetCount = 16 * 8 // Set WDT reset timeout for 8 seconds (16 * 8 ) / 16 = 8
  };

  void start(); // Starts the watchdog timer
  void stop(); // Disables the watchdog timer
  void restart(); // Restarts the watchdog timer ("Pets" the dog)
  void clear(); // Clears the watchdog interrupt
  uint32_t getCounter(); // Reads the current value of watch dog timer counter register
  void configure(uint8_t clock, uint8_t interrupt, uint8_t reset);
  void setClock(uint8_t clock); // Set the clock frequency of the watchdog timer
  void setInterrupt(uint8_t interrupt); // Set number of ticks before a watchdog interrupt event is generated
  void setReset(uint8_t reset); // Set number of ticks before the watchdog will issue a system reset
};
#endif //WDT_H