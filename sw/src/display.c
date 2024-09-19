#include "../inc/tm4c123gh6pm.h"
#include "../inc/display.h"
#include "../inc/ST7735.h"

char init_message[] = "hello";

void display_init(){
    Output_Init();
	ST7735_SetRotation(0);
	//ST7735_OutString(init_message);
}



