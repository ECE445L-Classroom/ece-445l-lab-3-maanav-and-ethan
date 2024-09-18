#ifndef SPEAKER_H   
#define SPEAKER_H

#include "../inc/tm4c123gh6pm.h"
#include <stdint.h>

void PortB_Init(void);

void SpeakerOn(void);

void SpeakerOff(void);

#endif