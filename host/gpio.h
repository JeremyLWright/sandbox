#ifndef GPIO_H
#define GPIO_H
#include "p24fxxxx.h"
#include "ports.h"
#define MISSED_CALL_LED _RA2
#define PHONE_LINE_INPUT_N _RA0
#define RINGER_LED _RA1
#define RESET_INPUT_N _RA3

void init_io();
unsigned char check_for_call();
#endif

