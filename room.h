#include "mtm_ex3.h"

#ifndef HW3WET_ROOM_H
#define HW3WET_ROOM_H


/** Type for defining the room */
typedef struct room_t* Room;
typedef struct order_t* Order;

/*!
 * This function creates & initiates to given value a room type ADT
 * @param room - points to the memory space given to the ADT
 * @param Email - a string the sigenfies the room's company email
 * @param id - unique identifier of a room.
 * @param num_ppl - the maximum amount of people that can enter the room
 * @param working_hours - string to repesent the working hours in which the room
 * is active
 * @param difficulty - int number between 1 anf 10 to represent the level.
 * @param price - int number to represent the price.
 * @return MTM_INVALID_PARAMETER - if one of the given parametes if not valid
 * MTM_NULL_PARAMETER - id email points to NULL
 * MTM_OUT_OF_MEMORY - if unable to allocate memory
 */
MtmErrorCode initRoom(Room *room, char* Email , int id , int num_ppl ,
                      char* working_hours, int difficulty, int price);

/*!
 * This function releases all allocated memory the resets
 * @param room
 */
void resetRoom(void* room);

MtmErrorCode roomGetId(Room room, int* id);

MtmErrorCode roomGetNumPpl(Room room, int * num_ppl);

MtmErrorCode roomGetDifficulty(Room room, int* difficulty);

MtmErrorCode roomGetWorkingHours(Room room, char** str);

MtmErrorCode roomGetPrice(Room room , int* price);

MtmErrorCode roomGetEmail(Room room , char* email);

MtmErrorCode roomGetOrder(Room room , Order order);

MtmErrorCode setRoomOrder(Room room, Order order);

MtmErrorCode resetRoomOrder(Room room );

int compareRoom(void* room1, void* room2);

void* copyRoom(void* room); //copies the POINTER to the room.


#endif //HW3WET_ROOM_H
