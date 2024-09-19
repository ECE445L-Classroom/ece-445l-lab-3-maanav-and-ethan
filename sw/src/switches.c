#include <stdio.h>
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "../inc/switches.h"


void EdgeCounter_Init(void){                          
  SYSCTL_RCGCGPIO_R |= 0x00000008; // (a) activate clock for port F
  //FallingEdges = 0;             // (b) initialize counter
  GPIO_PORTD_DIR_R &= ~0x0F;    // (c) make PF4 in (built-in button)
  GPIO_PORTD_AFSEL_R &= ~0x0F;  //     disable alt funct on PF4
  GPIO_PORTD_DEN_R |= 0x0F;     //     enable digital I/O on PF4   
  GPIO_PORTD_PCTL_R &= ~0x000F0000; // configure PF4 as GPIO
  GPIO_PORTD_AMSEL_R = 0;       //     disable analog functionality on PF
  //GPIO_PORTD_PUR_R |= 0x00;     //     enable weak pull-up on PF4
  GPIO_PORTD_IS_R &= ~0x0F;     // (d) PF4 is edge-sensitive
  GPIO_PORTD_IBE_R &= ~0x0F;    //     PF4 is not both edges
  GPIO_PORTD_IEV_R |= 0x0F;    //     PF4 falling edge event
  GPIO_PORTD_ICR_R = 0x0F;      // (e) clear flag4
  GPIO_PORTD_IM_R |= 0x0F;      // (f) arm interrupt on PF4 *** No IME bit as mentioned in Book ***
  NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000; // (g) priority 5
  NVIC_EN0_R = 0x40000000;      // (h) enable interrupt 30 in NVIC
  //EnableInterrupts();           // (i) Clears the I bit
}

void doBut0 (void){}

void doBut1 (void){}
	
void doBut2 (void) {}

void doBut3 (void){}
void GPIOPortF_Handler(void){
	uint32_t thing = 0;
	
	thing = GPIO_PORTD_MIS_R & 0x00FF;
	switch(thing) {
		case (0x01) : doBut0();
		case (0x02) : doBut1();
		case (0x04) : doBut2();
		case (0x08) : doBut3();
	}
			
			
  GPIO_PORTF_ICR_R = 0x10;      // acknowledge flag4
  //FallingEdges = FallingEdges + 1;
}

//debug code
