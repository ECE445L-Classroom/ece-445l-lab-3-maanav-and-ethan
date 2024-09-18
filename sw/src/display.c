#include "../inc/tm4c123gh6pm.h"
#include "../inc/display.h"
#include "../inc/ST7735.h"

char init_message[] = "hello";

void display_init(){
    Output_Init();
    //ST7735_InvertColors(False);
//    ST7735_DrawCharS(32, 32, 'p', 0xFFFF, 0, 2);
		ST7735_DrawCircle(32, 32, ST7735_BLUE);
    
}



