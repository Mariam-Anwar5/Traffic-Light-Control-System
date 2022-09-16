#ifndef TIMER0_H__
#define TIMER0_H__
#define Mode32 0x00
#define Mode16 0x04
#include "types.h"
#include "tm4c123gh6pm.h"
void Timer0_Init(void);
void timer0A_delayMs(int ttime);
void timer0_pause(void);
void timer0_resume(void);
#endif