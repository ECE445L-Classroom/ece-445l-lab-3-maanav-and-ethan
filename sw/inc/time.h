#ifndef TIME_H   
#define TIME_H

#include <stdint.h>  // For int16_t type

// Define the timeVal struct
typedef struct {
    int16_t hours;
    int16_t minutes;
    int16_t seconds;
} timeVal;

// Function prototype for incrementing time
void oneSecIncrement(timeVal* timeVal);

//sets the current time
void CurrentTime_Init(int16_t hours_Init, int16_t minutes_Init, int16_t seconds_Init, timeVal* currentTime);

//returns a null term string with hours:mintues:seconds:
void convert_CurrentTime_toStr(timeVal* currentTime, char currentTime_str[10]);

#endif // TIME_H
