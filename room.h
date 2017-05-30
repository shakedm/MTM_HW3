#include "mtm_ex3.h"

#ifndef HW3WET_ROOM_H
#define HW3WET_ROOM_H



typedef struct room_t* Room;
typedef struct order_t* Order;

//typedef struct roomPointer_t roomPinter;

MtmErrorCode initRoom(Room room, char** Email , int id , int num_ppl ,
                      char* working_hours, int difficulty, int price);
void resetRoom(void* room);
MtmErrorCode roomGetId(Room room, int* id);
MtmErrorCode roomGetNumPpl(Room room, int * num_ppl);
MtmErrorCode roomGetDifficulty(Room room, int* difficulty);
MtmErrorCode roomGetWorkingHours(Room room, char** str);
MtmErrorCode roomGetPrice(Room room , int* price);
MtmErrorCode roomGetEmail(Room room , char** email);

MtmErrorCode roomGetOrder(Room room , Order order);
MtmErrorCode setRoomOrder(Room room, Order order);
MtmErrorCode resetRoomOrder(Room room );

int compareRoom(void* room1, void* room2);

void* copyRoom(void* room); //copies the POINTER to the room.


#endif //HW3WET_ROOM_H
