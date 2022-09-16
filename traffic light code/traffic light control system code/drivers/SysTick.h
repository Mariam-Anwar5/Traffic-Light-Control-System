#include "types.h"


void SysTickDisable(void);
void SysTickEnable(void);
uint32 SysTickPeriodGet(void);
void SysTickPeriodSet(uint32 ui32Period); 
Bool SysTick_Is_Time_out(void);
 
 