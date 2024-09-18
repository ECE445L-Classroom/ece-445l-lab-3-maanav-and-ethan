// Lab3Main.c
// Runs on LM4F120/TM4C123
// Uses ST7735.c to display the clock
// patterns to the LCD.
//    16-bit color, 128 wide by 160 high LCD
// Mark McDermott, Daniel Valvano and Jonathan Valvano
// Lab solution, do not post
// August 3,2024

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2024

 Copyright 2024 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
// Specify your hardware connections, feel free to change
// PD0 is squarewave output to speaker
// PE0 is mode select
// PE1 is left
// PE2 is right 
// PE3 is up
// PE4 is down
// if alarm is sounding, any button will quiet the alarm

#include <stdio.h>
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Lab3.h"
#include "../inc/ST7735.h"
#include "../inc/PLL.h"
#include "../inc/LaunchPad.h"
#include "../inc/UART.h"
#include "../inc/Timer0A.h"
#include "../inc/Timer1A.h"
#include "../inc/Timer2A.h"
#include "../inc/time.h"
#include "../inc/speaker.h"

#define Sqr_wave_freq 80000
// ---------- Prototypes   -------------------------
void WaitForInterrupt(void);  // low power mode
void DisableInterrupts(void);
void EnableInterrupts(void);
void itsBeenOneSec(void);
void HeartBeat(void);


// ---------- Globals  -------------------------
timeVal currentTime;
char currentTime_str[10];

// ---------- MAIN  -------------------------
int main(void){
  DisableInterrupts();
  // write this
  PLL_Init(Bus80MHz);    // bus clock at 80 MHz
  LaunchPad_Init();
  PortB_Init();//init pb1 for speaker square wave
  UART_Init();
  Timer0A_Init(itsBeenOneSec, 80000000, 1);
  Timer1A_Init(HeartBeat, 40000000, 6);
  Timer2A_Init(PortB_Toggle, Sqr_wave_freq, 2);
  CurrentTime_Init(0,0,0, &currentTime);
  EnableInterrupts();
  while(1){
      // write this
  }
}


void itsBeenOneSec(void){
  oneSecIncrement(&currentTime);
  convert_CurrentTime_toStr(&currentTime, currentTime_str);
  UART_OutString(currentTime_str);
}

void HeartBeat(void){
  GPIO_PORTF_DATA_R ^= 0x02;
}