#include "room.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "usefullFunctions.h"

struct room_t{
    char* email;
    int id;
    int working_hours[HOURS_FORMAT];
    int num_ppl;
    int difficulty;
    int price;
    Order current_orders;
};

MtmErrorCode initRoom(Room *room, char* Email , int id , int num_ppl ,
                      char* working_hours, int difficulty, int price){
    assert(room != NULL);
    if ( id <= 0 || num_ppl <= 0 || price <= 0 || price %4 != 0 ||
            difficulty > MAX_SKILL | difficulty < MIN_SKILL ||
            !emailCheck(Email)){
        return MTM_INVALID_PARAMETER;
    }
    int time[HOURS_FORMAT] = {{0}};
    if(!translateHours(working_hours, time)){
        return MTM_INVALID_PARAMETER;
    }
    if (Email == NULL || working_hours == NULL){
        return MTM_NULL_PARAMETER;
    }
    Room new_room = malloc(sizeof(Room));
    if(!new_room){
        return MTM_OUT_OF_MEMORY;
    }
    *room = new_room;
    char *new_string = malloc(strlen(working_hours)+1);
    if(!new_string){
        free(room);
        return MTM_OUT_OF_MEMORY;
    }
    strcpy(new_string,working_hours);
    (*room)->num_ppl = num_ppl;
    (*room)->difficulty = difficulty;
    (*room)->id = id;
    (*room)->working_hours[OPEN_HOUR] = time[OPEN_HOUR];
    (*room)->working_hours[CLOSE_HOUR] = time[CLOSE_HOUR];
    (*room)->price = price;
    (*room)->email = Email;
    (*room)->current_orders = NULL;
    return MTM_SUCCESS;
}

void resetRoom(void* room){
    if(room == NULL){
        return;
    }
    free((*(Room*)room)->working_hours);
    (*(Room*)room)->num_ppl = 0;
    (*(Room*)room)->id = 0;
    (*(Room*)room)->price = 0;
    (*(Room*)room)->difficulty = 0;
    free((*(Room*)room)->email);
    (*(Room*)room)->current_orders = NULL;
    free(room);
}

int roomGetId(Room room){
    assert(room != NULL);
    return  room->id;
}

int roomGetNumPpl(Room room){
    assert(room != NULL);
    return  room->num_ppl;
}

int roomGetDifficulty(Room room){
    assert(room != NULL);
    return room->difficulty;
}

void roomGetWorkingHours(Room room, int* time){
    assert(room != NULL);
    time[OPEN_HOUR] = room->working_hours[OPEN_HOUR];
    time[CLOSE_HOUR] = room->working_hours[CLOSE_HOUR];
}

int roomGetPrice(Room room){
    assert(room != NULL);
    return  room->price;
}

const char* roomGetEmail(Room room){
    assert(room != NULL);
    return room->email;
}

int compareRoom(void* room1, void* room2){
    return (((*(Room*)room1)->id) - ((*(Room*)room2)->id));
}

void* copyRoom(void* room){
    assert(room != NULL);
    Room *new_room = NULL;
    MtmErrorCode result = initRoom(new_room, (*(Room*)room)->email,
                                   roomGetId((*(Room*)room)),
                                   roomGetNumPpl((*(Room*)room)),
                                   DUMMY_TIME, roomGetDifficulty((*(Room*)room)),
                                   roomGetPrice((*(Room*)room)));
    if(result != MTM_SUCCESS){
        return NULL;
    }
    assert(new_room != NULL);
    (*new_room)->working_hours[OPEN_HOUR] = (*(Room*)room)->working_hours[OPEN_HOUR];
    (*new_room)->working_hours[CLOSE_HOUR] = (*(Room*)room)->working_hours[CLOSE_HOUR];
    return new_room;
}