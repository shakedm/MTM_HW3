#include "usefullFunctions.h"


#include <assert.h>


bool emailCheck(char* email){
    int counter = 0;
    int index = 0;
    while (email[index] != '\0'){
        if(email[index] == '@'){
            counter++;
        }
        index++;
    }
    if (counter != GOOD_AMOUNT ){
        return false;
    }
    return true;
}


bool translateHours(char* working_hours, int *time, bool order){
    assert(working_hours != NULL);
    int hours_index = 0;
    while(*working_hours != '\0'){
        if(*working_hours < '0' || *working_hours > '9'){
            if (*working_hours != '-'){
                time[0] = BAD_HOURS;
                time[1] = BAD_HOURS;
                return false;
            }
            hours_index++;
            if (hours_index == HOURS_FORMAT) {
                return false;
            }
            working_hours++;
            continue;
        }
        time[hours_index] = (time[hours_index] * 10) + (*working_hours - '0');
        if(!order && hours_index == HOURS_FORMAT - 1){
            if(time[hours_index] > HOURS_PER_DAY){
                return false;
            }
        }
        if(order && hours_index == HOURS_FORMAT - 1){
            if(time[hours_index] >= HOURS_PER_DAY){
                return false;
            }
        }
        working_hours++;
    }
    if(!order){
        if (time[OPEN_HOUR] >= time[CLOSE_HOUR]){
            return false;
        }
    }
    return true;
}

