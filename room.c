#include "room.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct room_t{
    char** email;
    int id;
    char* working_hours; // יכול להשתנות לשדות של אינטג'רים
    int num_ppl;
    int difficulty;
    int price;
    Order current_orders;
};

/*struct roomPointer_t{
    int id;
    Room* room;
};*/

MtmErrorCode initRoom(Room room, char** Email , int id , int num_ppl ,
                      char* working_hours, int difficulty, int price){
    assert(room != NULL);
    assert(working_hours!=NULL);
    if ( id <= 0 || num_ppl <= 0 || price <= 0 || difficulty <= 0 ){
        return MTM_INVALID_PARAMETER;
    }
    if(price %4 != 0){
        return MTM_INVALID_PARAMETER;
    }
    if (Email == NULL){
        return MTM_NULL_PARAMETER;
    }
    char *new_string = malloc(strlen(working_hours)+1);
    if(!new_string){
        return MTM_OUT_OF_MEMORY;
    }

    strcpy(new_string,working_hours);
    room->num_ppl = num_ppl;
    room->working_hours = new_string;
    room->difficulty = difficulty;
    room->id = id;
    room->price = price;
    room->email = Email;
    room->current_orders = NULL;
    return MTM_SUCCESS;
}

//could change to void function
void resetRoom(void* room){
    assert(room != NULL);
    free((*(Room*)room)->working_hours);
    (*(Room*)room)->num_ppl = 0;
    (*(Room*)room)->id = 0;
    (*(Room*)room)->price = 0;
    (*(Room*)room)->difficulty = 0;
    (*(Room*)room)->email = NULL;
    (*(Room*)room)->current_orders = NULL; //could handle differenetly if there is an order
}

MtmErrorCode roomGetId(Room room, int* id){
    assert(room != NULL);
    *id = room->id;
    return MTM_SUCCESS;
}
MtmErrorCode roomGetNumppl(Room room, int * num_ppl){
    assert(room != NULL);
    *num_ppl = room->num_ppl;
    return MTM_SUCCESS;
}
MtmErrorCode roomGetDifficulty(Room room, int* difficulty){
    assert(room != NULL);
    *difficulty = room->difficulty;
    return MTM_SUCCESS;
}
MtmErrorCode roomGetWorkingHours(Room room, char** str){
    assert(room != NULL);
    *str = (room->working_hours);
    return MTM_SUCCESS;
}
MtmErrorCode roomGetPrice(Room room , int* price){
    assert(room != NULL);
    *price = room->price;
    return MTM_SUCCESS;
}
MtmErrorCode roomGetEmail(Room room , char** email){
    assert(room != NULL);
    *email = (*room->email);
    return MTM_SUCCESS;
}
