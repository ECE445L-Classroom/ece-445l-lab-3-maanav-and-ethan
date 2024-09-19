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
#include "../inc/display.h"

#define Sqr_wave_freq 80000
#define Length_Longest_Mode 9
// ---------- Prototypes   -------------------------
void WaitForInterrupt(void);  // low power mode
void DisableInterrupts(void);
void EnableInterrupts(void);
void itsBeenOneSec_Clock(void);
void HeartBeat(void);
void global_Variable_Init(void);
void screen_setup_init(void);

// ---------- Globals  -------------------------
timeVal currentTime;
char currentTime_str[10];
enum Mode currentMode;
char currentMode_str[Length_Longest_Mode+1];
// ---------- MAIN  -------------------------
int main(void){
  DisableInterrupts();
  PLL_Init(Bus80MHz);    // bus clock at 80 MHz
  LaunchPad_Init();//onboard leds and buttons
  PortB_Init();//pb1 for sqaure wave
  display_init();//init lcd
  screen_setup_init();//setting up initial screen layout
  global_Variable_Init();
  Timer0A_Init(itsBeenOneSec_Clock, 80000000, 0);//starts the global clock
  Timer1A_Init(HeartBeat, 40000000, 7);//heardbeat
  Timer2A_Init(SpeakerOn, Sqr_wave_freq, 6);//output to speaker
  EnableInterrupts();
  while(1){
      //nothign yet
  }
}

void itsBeenOneSec_Clock(void){
  oneSecIncrement(&currentTime);
  convert_Time_toStr(&currentTime, currentTime_str);
  ST7735_DrawString(7, 2, currentTime_str, ST7735_WHITE);
}

void HeartBeat(void){
  GPIO_PORTF_DATA_R ^= 0x02;
}

void global_Variable_Init(void){
  SetTime_Init(0,0,0,&currentTime);//set the initial time on clock start up
  GPIO_PORTF_DATA_R |= 0x02;//to make led light up on seconds
  currentMode = Clock;
}

void screen_setup_init(void){
    ST7735_DrawString(0, 2, "Time-> ", ST7735_WHITE);
    ST7735_DrawString(0,0, "Mode-> ", ST7735_WHITE);
    convert_Mode_toStr(currentMode, currentMode_str);
    ST7735_DrawString(7,0, currentMode_str, ST7735_WHITE);
    ST7735_DrawBitmap(24,130,clock_bitmap, 80, 80);
}