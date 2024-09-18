#include "../inc/tm4c123gh6pm.h"
#include "../inc/speaker.h"
#include <stdint.h>

//making PB1 digital output pin
void PortB_Init(void){
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
    while((SYSCTL_PRGPIO_R&SYSCTL_PRGPIO_R1) == 0){};

    GPIO_PORTB_AFSEL_R &= ~0x02;//turn off alternate functionality
    GPIO_PORTB_AMSEL_R &= ~0x02;//turn off analog
    GPIO_PORTB_DEN_R |= 0x02;//make it digital
    GPIO_PORTB_DIR_R |= 0x02;//make it out out
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFFFFF0F);
}

void PortB_Toggle(void){
    GPIO_PORTB_DATA_R ^= 0x02;
}

