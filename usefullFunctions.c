#include "usefullFunctions.h"

bool emailCheck(char* email){
    int counter = 0;
    int index = 0;
    while (email[index] != '/0'){
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
