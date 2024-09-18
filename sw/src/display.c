#include "../inc/tm4c123gh6pm.h"
#include "../inc/display.h"
#include "../inc/ST7735.h"

char init_message[] = "hello";

void display_init(){
    ST7735_InitR(INITR_REDTAB);
    //ST7735_InvertColors(False);
    ST7735_SetCursor(0,0);
    ST7735_OutString(init_message);
}

