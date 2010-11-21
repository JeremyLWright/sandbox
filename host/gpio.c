#include "gpio.h"

void init_io()
{
   _TRISA0 = 1; //Phone Line
   _TRISA1 = 0; //RINGER LED
   _TRISA2 = 0; //MISSED_CALL_LED
   _TRISA3 = 1; //RESET Button

   MISSED_CALL_LED = 0;
   RINGER_LED = 0;
}

void gpio_task()
{
    if(RESET_INPUT_N == 0)
        MISSED_CALL_LED = 1;
    else
        MISSED_CALL_LED = 0;
}
