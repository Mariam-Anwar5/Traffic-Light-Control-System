#include "tm4c123gh6pm.h"
#include "types.h"

void SysTickDisable(void)
{
    NVIC_ST_CTRL_R = 0;          
}


void SysTickEnable(void)
{
     NVIC_ST_CTRL_R   |= 0x05;
}
 
  uint32 SysTickPeriodGet(void){
  return NVIC_ST_CURRENT_R;
 }
 
 void SysTickPeriodSet(uint32 ui32Period){   // in milliseconds
       
   NVIC_ST_RELOAD_R  = (ui32Period*16000000)-1 ;  
 }
 
 Bool SysTick_Is_Time_out(void){
    return (NVIC_ST_CTRL_R & (1<<16))>>16;
 }  
 
 
 
 