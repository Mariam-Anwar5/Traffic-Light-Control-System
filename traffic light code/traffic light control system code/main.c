#include "tm4c123gh6pm.h"
#include "Timer0.h"
#include "SysTick.h"
#include "types.h"
#include "DIO.h"

#define PORTF 'F'
#define PORTA 'A'
#define PORTB 'B'

#define OUTPUT 1
#define INPUT 0
#define HIGH 1
#define LOW  0

/* Enable Exceptions ... This Macro enable IRQ interrupts, Programmble Systems Exceptions and Faults by clearing the I-bit in the PRIMASK. */
#define Enable_Exceptions()    __asm("CPSIE I")

//car 1 leds
#define car1_red_led 2             // pin 2 in port A
#define car1_yellow_led 3         // pin 3 in port A
#define car1_green_led 4          // pin 4 in port A

//car 2 leds

#define car2_red_led 5          // pin 5 in port A
#define car2_yellow_led 6       // pin 6 in port A
#define car2_green_led 7       // pin 7 in port A

//pedestrian 1 switch and leds
#define SW1 4                   // pin 4 in port F
#define ped1_green_led 0       // pin 0 in port B
#define ped1_red_led 1         // pin 1 in port B

//pedestrian 2 switch and leds
#define SW2 0                    // pin 0 in port F
#define ped2_red_led 2          // pin 2 in port B
#define ped2_green_led 1        // pin 1 in port F


#define GPIO_PORTF_PRIORITY_MASK      0xFF1FFFFF
#define GPIO_PORTF_PRIORITY_BITS_POS  21
#define GPIO_PORTF_INTERRUPT_PRIORITY 2

extern void GPIOF_ISR(void);


/* Enable PF4 (SW1) and activate external interrupt with falling edge */
void SW1_Init(void)
{
   // GPIO_PORTF_LOCK_R   = 0x4C4F434B;   /* Unlock the GPIO_PORTF_CR_REG */
   // GPIO_PORTF_CR_R    |= (1<<4);       /* Enable changes on PF4 */
    GPIO_PORTF_AMSEL_R &= ~(1<<4);      /* Disable Analog on PF4 */
    GPIO_PORTF_PCTL_R  &= 0xFFF0FFFF;   /* Clear PMCx bits for PF4 to use it as GPIO pin */
    GPIO_PORTF_DIR_R   &= ~(1<<4);      /* Configure PF4 as input pin */
    GPIO_PORTF_AFSEL_R &= ~(1<<4);      /* Disable alternative function on PF4 */
    GPIO_PORTF_PUR_R   |= (1<<4);       /* Enable pull-up on PF4 */
    GPIO_PORTF_DEN_R   |= (1<<4);       /* Enable Digital I/O on PF4 */
    GPIO_PORTF_IS_R    &= ~(1<<4);      /* PF4 detect edges */
    GPIO_PORTF_IBE_R   &= ~(1<<4);      /* PF4 will detect a certain edge */
    GPIO_PORTF_IEV_R   &= ~(1<<4);      /* PF4 will detect a falling edge */
    GPIO_PORTF_ICR_R   |= (1<<4);       /* Clear Trigger flag for PF4 (Interupt Flag) */
    GPIO_PORTF_IM_R    |= (1<<4);       /* Enable Interrupt on PF4 pin */
/* Set GPIO PORTF priotiy as 2 by set Bit number 21, 22 and 23 with value 2 */
    NVIC_PRI7_R = (NVIC_PRI7_REG & GPIO_PORTF_PRIORITY_MASK) | (GPIO_PORTF_INTERRUPT_PRIORITY<<GPIO_PORTF_PRIORITY_BITS_POS); 
    NVIC_EN0_R        |= 0x40000000;   /* Enable NVIC Interrupt for GPIO PORTF by set bit number 30 in EN0 Register */
}

/* Enable PF4 (SW1) and activate external interrupt with falling edge */
void SW2_Init(void)
{
    //GPIO_PORTF_LOCK_R   = 0x4C4F434B;   /* Unlock the GPIO_PORTF_CR_REG */
    //GPIO_PORTF_CR_R    |= (1<<0);       /* Enable changes on PF0 */
    GPIO_PORTF_AMSEL_R &= ~(1<<0);      /* Disable Analog on PF0 */
    GPIO_PORTF_PCTL_R  &= 0xFFFFFFF0;   /* Clear PMCx bits for PF0 to use it as GPIO pin */
    GPIO_PORTF_DIR_R   &= ~(1<<0);      /* Configure PF0 as input pin */
    GPIO_PORTF_AFSEL_R &= ~(1<<0);      /* Disable alternative function on PF0 */
    GPIO_PORTF_PUR_R   |= (1<<0);       /* Enable pull-up on PF0 */
    GPIO_PORTF_DEN_R   |= (1<<0);       /* Enable Digital I/O on PF0 */
    GPIO_PORTF_IS_R    &= ~(1<<0);      /* PF0 detect edges */
    GPIO_PORTF_IBE_R   &= ~(1<<0);      /* PF0 will detect a certain edge */
    GPIO_PORTF_IEV_R   &= ~(1<<0);      /* PF0 will detect a falling edge */
    GPIO_PORTF_ICR_R   |= (1<<0);       /* Clear Trigger flag for PF0 (Interupt Flag) */
    GPIO_PORTF_IM_R    |= (1<<0);       /* Enable Interrupt on PF0 pin */
/* Set GPIO PORTF priotiy as 2 by set Bit number 21, 22 and 23 with value 2 */
    NVIC_PRI7_REG = (NVIC_PRI7_REG & GPIO_PORTF_PRIORITY_MASK) | (GPIO_PORTF_INTERRUPT_PRIORITY<<GPIO_PORTF_PRIORITY_BITS_POS); 
    NVIC_EN0_REG         |= 0x40000000;   /* Enable NVIC Interrupt for GPIO PORTF by set bit number 30 in EN0 Register */
}

void delay(int n){
  for(int i=0;i<n;i++){
    for (int j=0; j<3180; j++){}  
}
}

int main()
{
  /*
  1. Initializing timer0
  2. Setting all the led pins as an output pins
  3. Initializing all pins by zero as a start
  4. Initializing interrupts of both of the 2 switches
  */
   Timer0_Init();
   DIO_Init (PORTB ,ped1_red_led, OUTPUT);
   DIO_Init (PORTB ,ped1_green_led, OUTPUT);
   DIO_Init (PORTB ,ped2_red_led, OUTPUT);
   DIO_Init (PORTF ,ped2_green_led, OUTPUT);
   DIO_Init (PORTA ,car1_green_led, OUTPUT);
   DIO_Init (PORTA ,car1_red_led, OUTPUT);
   DIO_Init (PORTA ,car1_yellow_led, OUTPUT);
   DIO_Init (PORTA ,car2_green_led, OUTPUT);
   DIO_Init (PORTA ,car2_red_led, OUTPUT);
   DIO_Init (PORTA ,car2_yellow_led, OUTPUT);
   DIO_WritePin (PORTA ,car1_green_led, 0);
   DIO_WritePin (PORTA ,car1_red_led, 0);
   DIO_WritePin (PORTA ,car1_yellow_led, 0);
   DIO_WritePin (PORTA ,car2_green_led, 0);
   DIO_WritePin (PORTA ,car2_red_led, 0);
   DIO_WritePin (PORTA ,car2_yellow_led, 0);
   DIO_WritePin (PORTB ,ped1_green_led, 0);
   DIO_WritePin (PORTB ,ped1_red_led, 0);
   DIO_WritePin (PORTF ,ped2_green_led, 0);
   DIO_WritePin (PORTB ,ped2_red_led, 0);
   SW2_Init();
   SW1_Init();
   
   
   
  while(1){
    /*
    -> Sequence of lighting up the leds.. 
    1) Turn the pedestrian red leds on
    - The first car traffic light:
        1. Green led of the first car traffic light is on for 5 sec & red of the second car traffic light is on
        2. Yellow led of the first car traffic light is on for 2 sec & red of the second car traffic light is on
        3. Both red leds is on for 1 sec
    - The second car traffic light:
        1. Green led of the second car traffic light is on for 5 sec & red of the first car traffic light is on
        2. Yellow led of the second car traffic light is on for 2 sec & red of the first car traffic light is on
        3. Both red leds is on for 1 sec
    */
       DIO_WritePin (PORTB ,ped2_red_led, 1);
       DIO_WritePin (PORTB ,ped1_red_led, 1);
       DIO_WritePin (PORTF ,ped2_green_led, 0);
       DIO_WritePin (PORTB ,ped1_green_led, 0);
       DIO_WritePin (PORTA ,car1_green_led, 1);
       DIO_WritePin (PORTA ,car2_red_led, 1);
       timer0A_delayMs(5000);
       DIO_WritePin (PORTA ,car1_green_led, 0);
       DIO_WritePin (PORTA ,car1_yellow_led, 1);
       timer0A_delayMs(2000);
       DIO_WritePin (PORTA ,car1_yellow_led, 0);
       DIO_WritePin (PORTA ,car1_red_led, 1);
       DIO_WritePin (PORTA ,car2_red_led, 1);
       timer0A_delayMs(1000);
       DIO_WritePin (PORTA ,car1_yellow_led, 0);
       DIO_WritePin (PORTA ,car2_red_led, 0);
       DIO_WritePin (PORTA ,car2_green_led, 1);
       DIO_WritePin (PORTA ,car1_red_led, 1);
       timer0A_delayMs(5000);
       DIO_WritePin (PORTA ,car2_green_led, 0);
       DIO_WritePin (PORTA ,car2_yellow_led, 1);
       timer0A_delayMs(2000);
       DIO_WritePin (PORTA ,car2_yellow_led, 0);
       DIO_WritePin (PORTA ,car1_red_led, 1);
       DIO_WritePin (PORTA ,car2_red_led, 1);
       timer0A_delayMs(1000);
       DIO_WritePin (PORTA ,car1_red_led, 0);

          }
}

// Switches Handler:
  void GPIOF_ISR(void){
  int counter = 0; // Counter to count up when the systick timer flag is up
  int temp = GPIO_PORTA_DATA_R;  // Save the last state before the ISR
  timer0_pause(); // Cut off the clock to stop counting
  DIO_WritePin(PORTB,ped2_red_led,1);
  
  if(DIO_ReadPin(PORTF,SW1) == 0){
     delay(40);
     if(DIO_ReadPin(PORTF,SW1) == 0){
        DIO_WritePin(PORTA,car1_green_led,0);   /*   When the switch is pressed turn of both green and yellow leds*/
        DIO_WritePin(PORTA,car1_yellow_led,0);  /*   of the corresponding car traffic light*/
        DIO_WritePin(PORTA,car1_red_led,1);     /*   and turn its red led on*/
        SysTickPeriodSet(1); // In seconds
        while (counter < 2){ // Loop for counting 2 seconds
          if(SysTick_Is_Time_out()){
            counter++;}
        DIO_WritePin(PORTB,ped1_red_led,0);  
        DIO_WritePin(PORTB,ped1_green_led,1);  // While it is still counting pedestrian green led is turned on
        }
        while(DIO_ReadPin(PORTF,SW1) == 0){}
        delay(50);
      } 
      DIO_WritePin (PORTB ,ped1_red_led, 1);
      DIO_WritePin(PORTB ,ped1_green_led,0);      
      counter = 0;
}

  if(DIO_ReadPin(PORTF,SW2) == 0){
     delay(40);
     if(DIO_ReadPin(PORTF,SW2) == 0){
        DIO_WritePin(PORTA,car2_green_led,0);
        DIO_WritePin(PORTA,car2_yellow_led,0); 
        DIO_WritePin(PORTA,car2_red_led,1); 
          SysTickPeriodSet(1);
        while (counter < 2){
          if(SysTick_Is_Time_out()){
            counter++;}
        DIO_WritePin(PORTB,ped2_red_led,0); 
        DIO_WritePin(PORTF,ped2_green_led,1);
        }
        while(DIO_ReadPin(PORTF,SW2) == 0){}
        delay(50);
      }
      DIO_WritePin (PORTB ,ped2_red_led, 1);     
      DIO_WritePin(PORTF,ped2_green_led,0); 
      counter =0;
}
  GPIO_PORTF_ICR_R   |= (1<<4); // Clearing the interrupt flag
  GPIO_PORTF_ICR_R   |= (1<<0);
  timer0_resume(); // Enabling the clock of timer0 once again 
  GPIO_PORTA_DATA_R = temp; // Return to the state before pressing the switch as the 6 leds of both of the car traffic lights on portA
}
