#include "mtm_ex3.h"


#ifndef HW3WET_ROOM_H
#define HW3WET_ROOM_H

#include "order.h"

#define DUMMY_TIME "00-01"

/** Type for defining the room */
typedef struct room_t* Room;


Room createRoom();

void destroyRoom(Room room);
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

/* * This function releases all allocated memory the resets.
 * @param room - points to the memory to free. if NULL this function does
 * nothing.
 */
void resetRoom(void* room);

/* * This function returns the room's ID (the unige identifier)
 * @param room - points to the ADT
 * @return the ID field in the ADT.
 */
int roomGetId(Room room);

/* * This function returns the maximum amount of people allowed in the room ADT
 * @param room - points to the room ADT
 * @return the int number of people.
 */
int roomGetNumPpl(Room room);

/* * This function returns the difficulty level of the room
 * @param room - points to the room ADT
 * @return int level num
 */
int roomGetDifficulty(Room room);

/* * This function copies the room's working hours to a given int array
 * @param room - points to the room ADT
 * @param hours - return parameter, int array.
 * @return -.
 */
void roomGetWorkingHours(Room room, int* time);

/* * This function returns the price to a given room.
 * @param room - points to the room ADT
 * @return - int price.
 */
int roomGetPrice(Room room);

/* * This function returns a CONST pointer to the room's email string
 * @param room - points to the room ADT
 * @return - const pointer to string.
 */
const char* roomGetEmail(Room room);


MtmErrorCode roomGetOrder(Room room , Order order);

/* *
 * @param room
 * @param order
 * @return
 */
MtmErrorCode setRoomOrder(Room room, Order order);

MtmErrorCode resetRoomOrder(Room room );

/* * This function compares two room ADT by theis ID fields
 * @param room1 - points to the 1st room ADT
 * @param room2 - points to the 2nd room ADT
 * @return A positive integer if the first room's ID is greater.
* 		0 if they're equal;
*		A negative integer if the second room's ID is greater.
 */
int compareRoom(void* room1, void* room2);

/* * This function creates a new room ADT and copies the given ADT fields.
 * @param room - points to the room to copy
 * @return - NULL if the allocation failed.
 * pointer to room type ADT otherwise.
 */
void* copyRoom(void* room); //copies the POINTER to the room.


#endif //HW3WET_ROOM_H
