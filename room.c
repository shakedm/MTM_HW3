#include "room.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct room_t{
    char** email;
    unsigned int id;
    char** working_hours; // יכול להשתנות לשדות של אינטג'רים
    int difficulty;
    int price;
    Order current_orders;
};
MtmErrorCode initRoom(Room room, char** Email ,unsigned int id , int num_ppl ,
                      char* working_hours, int difficulty, int price){
    assert(room != NULL);
    assert(working_hours!=NULL);
    if ( id<=0 || num_ppl<=0 || price<=0 || difficulty<=0 )
        return MTM_INVALID_PARAMETER;
    if(price%4 != 0)
        return MTM_INVALID_PARAMETER;
    char *new_string = malloc(strlen(working_hours)+1);
    if(!new_string)
        return MTM_OUT_OF_MEMORY;
    strcpy(new_string,working_hours);
    room->working_hours = &new_string;
    room->difficulty = difficulty;
    room->id = id;
    room->price = price;
    room->email = Email;
    room->current_orders = NULL;
    return MTM_SUCCESS;
}
//could change to void function
MtmErrorCode resetRoom(Room room){
    assert(room != NULL);
    free(room->working_hours);
    room->id = 0;
    room->price = 0;
    room->difficulty = 0;
    room->email = NULL;
    room->current_orders = NULL; //could handle differenetly if there is an order
    return MTM_SUCCESS;
}
