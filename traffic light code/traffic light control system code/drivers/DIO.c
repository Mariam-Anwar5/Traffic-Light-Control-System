#include "tm4c123gh6pm.h"
#include "bitwise_operation.h"

#define OUTPUT 1
#define INPUT 0
#define HIGH 0xFF
#define LOW  0x00

void DIO_Init (char port ,int pin, int pin_direction){
  switch (port)
  {
case 'A':
  SYSCTL_RCGCGPIO_R |= 0x0000001;                  
  while ((SYSCTL_PRGPIO_R & 0x00000001 ) == 0){};
  GPIO_PORTA_LOCK_R = 0x4C4F434B;
  GPIO_PORTA_DEN_R = 0xFF;
  GPIO_PORTA_CR_R = 0x1F;
   if(pin_direction==OUTPUT){
     SET_BIT(GPIO_PORTA_DIR_R, pin);}
   else if (pin_direction==INPUT)
   {
     CLEAR_BIT (GPIO_PORTA_DIR_R, pin);
     SET_BIT(GPIO_PORTA_PUR_R, pin);
   }
 break;

   case 'B':
  SYSCTL_RCGCGPIO_R |= 0x00000002;                  
  while ((SYSCTL_PRGPIO_R & 0x00000002 ) == 0){};
  GPIO_PORTB_LOCK_R = 0x4C4F434B;
  GPIO_PORTB_DEN_R = 0xFF;
  GPIO_PORTB_CR_R = 0x1F;
   if(pin_direction==OUTPUT){
     SET_BIT(GPIO_PORTB_DIR_R, pin);}
   else if (pin_direction==INPUT){
     CLEAR_BIT (GPIO_PORTB_DIR_R, pin);
     SET_BIT(GPIO_PORTB_PUR_R, pin);
   }
  break;
  
  case 'C':
  SYSCTL_RCGCGPIO_R |= 0x000000004;                  
  while ((SYSCTL_PRGPIO_R & 0x000000004 ) == 0){};
  GPIO_PORTC_LOCK_R = 0x4C4F434B;
  GPIO_PORTC_DEN_R = 0xFF;
  GPIO_PORTC_CR_R = 0x1F;
   if(pin_direction==OUTPUT){
     SET_BIT(GPIO_PORTC_DIR_R, pin);}
   else if (pin_direction==INPUT){
     CLEAR_BIT (GPIO_PORTC_DIR_R, pin);
     SET_BIT(GPIO_PORTC_PUR_R, pin);
   }
  break;
  
  case 'D':
  SYSCTL_RCGCGPIO_R |= 0x00000008;                  
  while ((SYSCTL_PRGPIO_R & 0x000000008 ) == 0){};
  GPIO_PORTD_LOCK_R = 0x4C4F434B;
  GPIO_PORTD_DEN_R = 0xFF;
  GPIO_PORTD_CR_R = 0x1F;
   if(pin_direction==OUTPUT){
     SET_BIT(GPIO_PORTD_DIR_R, pin);}
   else if (pin_direction==INPUT){
     CLEAR_BIT (GPIO_PORTD_DIR_R, pin);
     SET_BIT(GPIO_PORTD_PUR_R, pin);
   }
  break;
  
  case 'E':
  SYSCTL_RCGCGPIO_R |= 0x00000010;                  
  while ((SYSCTL_PRGPIO_R & 0x00000010 ) == 0){};
  GPIO_PORTE_LOCK_R = 0x4C4F434B;
  GPIO_PORTE_DEN_R = 0xFF;
  GPIO_PORTE_CR_R = 0x1F;
   if(pin_direction==OUTPUT){
     SET_BIT(GPIO_PORTE_DIR_R, pin);}
   else if (pin_direction==INPUT){
     CLEAR_BIT (GPIO_PORTE_DIR_R, pin);
     SET_BIT(GPIO_PORTE_PUR_R, pin);
   }
  break;
  
  case 'F':
  SYSCTL_RCGCGPIO_R |= 0x00000020;                  
  while ((SYSCTL_PRGPIO_R & 0x00000020 ) == 0){};
  GPIO_PORTF_LOCK_R = 0x4C4F434B;
  GPIO_PORTF_DEN_R = 0xFF;
  GPIO_PORTF_CR_R = 0x1F;
   if(pin_direction==OUTPUT){
     SET_BIT(GPIO_PORTF_DIR_R, pin);}
   else if (pin_direction==INPUT){
     CLEAR_BIT (GPIO_PORTF_DIR_R, pin);
     SET_BIT(GPIO_PORTF_PUR_R, pin);
   }
  break;
}
}


void DIO_WritePORT (char port , int port_value)
{
   switch (port)
   {
case 'A':                 
  GPIO_PORTA_DIR_R = port_value;
 break;
 
 case 'B':                 
  GPIO_PORTB_DIR_R = port_value;
 break;
 
 case 'C':                 
   GPIO_PORTC_DIR_R = port_value;
 break;
 
 case 'D':                 
   GPIO_PORTD_DIR_R = port_value;
 break;
 
 case 'E':                 
   GPIO_PORTE_DIR_R = port_value;
 break;
 
 case 'F':                 
   GPIO_PORTF_DIR_R = port_value;
 break;
   }
}
  
 void DIO_WritePin (char port ,int pin, int pin_value)
{
   switch (port)
   {
case 'A':                 
   if(pin_value==1)
     SET_BIT(GPIO_PORTA_DATA_R, pin);
   else if (pin_value==0)
     CLEAR_BIT (GPIO_PORTA_DATA_R, pin);
 break;
 
 case 'B':                 
   if(pin_value==1)
     SET_BIT(GPIO_PORTB_DATA_R, pin);
   else if (pin_value==0)
     CLEAR_BIT (GPIO_PORTB_DATA_R, pin);
 break;
 
 case 'C':                 
   if(pin_value==1)
     SET_BIT(GPIO_PORTC_DATA_R, pin);
   else if (pin_value==0)
     CLEAR_BIT (GPIO_PORTC_DATA_R, pin);
 break;
 
 case 'D':                 
   if(pin_value==1)
     SET_BIT(GPIO_PORTD_DATA_R, pin);
   else if (pin_value==0)
     CLEAR_BIT (GPIO_PORTD_DATA_R, pin);
 break;
 
 case 'E':                 
   if(pin_value==1)
     SET_BIT(GPIO_PORTE_DATA_R, pin);
   else if (pin_value==0)
     CLEAR_BIT (GPIO_PORTE_DATA_R, pin);
 break;
 
 case 'F':                 
   if(pin_value==1)
     SET_BIT(GPIO_PORTF_DATA_R, pin);
   else if (pin_value==0)
     CLEAR_BIT (GPIO_PORTF_DATA_R, pin);
 break;
   }
 }
  
char DIO_ReadPin (char port ,int pin)
{
  char value;
   switch (port)
   {
case 'A':                 
    value = GET_BIT (GPIO_PORTA_DATA_R, pin);
 
 case 'B':                 
     value = GET_BIT (GPIO_PORTB_DATA_R, pin);
 break;
 
 case 'C':                 
    value = GET_BIT (GPIO_PORTC_DATA_R, pin);
 break;
 
 case 'D':                 
    value = GET_BIT (GPIO_PORTD_DATA_R, pin);
 break;
 
 case 'E':                 
    value = GET_BIT (GPIO_PORTE_DATA_R, pin);
 break;
 
 case 'F':                 
   value = GET_BIT (GPIO_PORTF_DATA_R, pin);
 break;
   }
   return value;
 }  

void DIO_TogglePin (char port ,int pin)
{
   switch (port)
   {
case 'A':                 
      TOGGLE_BIT (GPIO_PORTA_DATA_R, pin);
 
 case 'B':                 
     TOGGLE_BIT (GPIO_PORTB_DATA_R, pin);
 break;
 
 case 'C':                 
    TOGGLE_BIT (GPIO_PORTC_DATA_R, pin);
 break;
 
 case 'D':                 
    TOGGLE_BIT (GPIO_PORTD_DATA_R, pin);
 break;
 
 case 'E':                 
    TOGGLE_BIT (GPIO_PORTE_DATA_R, pin);
 break;
 
 case 'F':                 
   TOGGLE_BIT (GPIO_PORTF_DATA_R, pin);
 break;
   }
 }  