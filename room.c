#include "room.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct room_t{
    char* email;
    int id;
    int working_hours[HOURS_FORMAT];
    int num_ppl;
    int difficulty;
    int price;
    //Order current_orders;
};
Room createRoom(){
    Room new_room = malloc(sizeof(*new_room));
    return new_room; //if malloc failed it returns NULL
}

void destroyRoom(void* room){
    if(!room)
        return;
    resetRoom((Room)room);
    free(*(Room*)room);
}

RoomError initRoom(Room room, char* Email , int id , int num_ppl ,
                      char* working_hours, int difficulty, int price){
    assert(room != NULL);
    if ( id <= 0 || num_ppl <= 0 || price <= 0 || price %4 != 0 ||
            difficulty > MAX_SKILL || difficulty < MIN_SKILL ||
            !emailCheck(Email)){
        return ROOM_INVALID_PARAMETER;
    }
    int time[HOURS_FORMAT] = {0};
    if(!translateHours(working_hours, time, false)){
        return ROOM_INVALID_PARAMETER;
    }
    if (Email == NULL || working_hours == NULL){
        return ROOM_NULL_PARAMETER;
    }
    char* new_email = (char*)malloc((strlen(Email)+1) *sizeof(char));
    if  (!new_email){
        return ROOM_OUT_OF_MEMORY;
    }
    strcpy(new_email,Email);
    room->num_ppl = num_ppl;
    room->difficulty = difficulty;
    room->id = id;
    room->working_hours[OPEN_HOUR] = time[OPEN_HOUR];
    room->working_hours[CLOSE_HOUR] = time[CLOSE_HOUR];
    room->price = price;
    room->email = new_email;
    //(*room)->current_orders = NULL;
    return ROOM_SUCCESS;
}

void resetRoom(Room room){
    if(room == NULL){
        return;
    }
    room->working_hours[0]=0;
    room->working_hours[1]=0;
    room->num_ppl = 0;
    room->id = 0;
    room->price = 0;
    room->difficulty = 0;
    char* email_ptr= room->email;
    if (email_ptr != NULL){
        free(email_ptr);
    }
    room->email = NULL;
}

int roomGetId(Room room){
    if(!room){
        return -1;
    }
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
    return ((((Room)room1)->id) - (((Room)room2)->id));
}

int roomGetOpenTime(Room room){
    assert(room != NULL);
    return room->working_hours[OPEN_HOUR];
}

int roomGetCloseTime(Room room){
    assert(room != NULL);
    return room->working_hours[CLOSE_HOUR];
}

void* copyRoom(void* room){
    assert(room != NULL);
    Room new_room = createRoom();
    RoomError result = initRoom(new_room, ((Room)room)->email,
                                   roomGetId(((Room)room)),
                                   roomGetNumPpl(((Room)room)),
                                   DUMMY_TIME, roomGetDifficulty(((Room)room)),
                                   roomGetPrice(((Room)room)));
    if(result != ROOM_SUCCESS){
        return NULL;
    }
    assert(new_room != NULL);
    new_room->working_hours[OPEN_HOUR] = ((Room)room)->working_hours[OPEN_HOUR];
    new_room->working_hours[CLOSE_HOUR] = ((Room)room)->working_hours[CLOSE_HOUR];
    return new_room;
}