#include "../inc/tm4c123gh6pm.h"
#include "../inc/time.h"
#include <stdio.h>
#include <stdint.h>

void itos_2digit(char out[2], int in);


//consider adding am pm, if needed
void oneSecIncrement(timeVal* timeVal) {
    timeVal->seconds++;
    
    if (timeVal->seconds == 60) {
        timeVal->seconds = 0;
        timeVal->minutes++;
        
        if (timeVal->minutes == 60) {
            timeVal->minutes = 0;
            timeVal->hours++;
            
            if (timeVal->hours == 24) {
                timeVal->hours = 0;
            }
        }
    }
}

void CurrentTime_Init(int16_t hours_Init, int16_t minutes_Init, int16_t seconds_Init, timeVal* currentTime){
  currentTime->seconds = seconds_Init;
  currentTime->minutes = minutes_Init;
  currentTime->hours = hours_Init;
}

void convert_CurrentTime_toStr(timeVal* currentTime, char currentTime_str[10]){
    int inttostr_idx = 0;
    char conversion_string[2];
    int16_t time_Units_List[3];
    time_Units_List[0] = currentTime->hours;
    time_Units_List[1] = currentTime->minutes;
    time_Units_List[2] = currentTime->seconds;

    for(int i = 0; i < 3; i++){
        itos_2digit(conversion_string, time_Units_List[i]);
        currentTime_str[inttostr_idx] = conversion_string[0];
        inttostr_idx++;
        currentTime_str[inttostr_idx] = conversion_string[1];
        inttostr_idx++;
        currentTime_str[inttostr_idx] = ':';
        inttostr_idx++;
    }
    currentTime_str[inttostr_idx-1] = '\0';
    currentTime_str[inttostr_idx] = '\0';

}

void itos_2digit(char out[2], int in) {
    // Ensure that the number is between 0 and 99
    if (in < 0 || in > 99) {
        out[0] = '0';  // Default to '00' if input is out of bounds
        out[1] = '0';
        return;
    }

    // If the input is less than 10, pad with a leading '0'
    out[0] = (in / 10) + '0';  // Tens place (0 for single-digit numbers)
    out[1] = (in % 10) + '0';  // Ones place
}
