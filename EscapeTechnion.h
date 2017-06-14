#ifndef HW3WET_ESCAPETECHNION_H
#define HW3WET_ESCAPETECHNION_H

#include "escaper.h"
#include "room.h"
#include "company.h"
#include "usefullFunctions.h"
#include "order.h"
//#include "faculty.h"

#define SMALLER 1
#define EQUAL 2
#define BIGGER 3
#define TODAY 0
#define TOP 3
#define NUM_FACULTIES 18

/* type to define the EscapeTechnion struct*/
typedef struct escape_technion_t* EscapeTechnion;

//errors enum
typedef enum {
    ESCAPE_OUT_OF_MEMORY,
    ESCAPE_NULL_PARAMETER,
    ESCAPE_INVALID_PARAMETER,
    ESCAPE_EMAIL_ALREADY_EXISTS,
    ESCAPE_COMPANY_EMAIL_DOES_NOT_EXIST,
    ESCAPE_CLIENT_EMAIL_DOES_NOT_EXIST,
    ESCAPE_ID_ALREADY_EXIST,
    ESCAPE_ID_DOES_NOT_EXIST,
    ESCAPE_CLIENT_IN_ROOM,
    ESCAPE_ROOM_NOT_AVAILABLE,
    ESCAPE_RESERVATION_EXISTS,
    ESCAPE_NO_ROOMS_AVAILABLE,
    ESCAPE_SUCCESS,
} EscapeTechnionError;

/*!
 * This function create a new ecape system
 * @param sys - return parameter points to the new system.
 * @return
 */
EscapeTechnionError createEscapeTechnion(EscapeTechnion *sys);

/*!
 * This functions adds a new room the the system.
 * @param sys - points to the system ADT
 * @param email - the company's email, any sting that contains exectly one '@'
 * @param faculty - the faculty to which the company belongs (defined in mtm_ex3
 * @return ESCAPE_INVALID_PARAMETER if the given parametes is invalid
 *          ESCAPE_EMAIL_ALREADY_EXISTS - if the email exists in system.
 */
EscapeTechnionError companyAdd(EscapeTechnion sys, char* email,
                        TechnionFaculty faculty);

/*!
 * function removes an existing company from system, with all related rooms.
 * @param sys - points to the system ADT
 * @param email - the sting from which to find the room
 * @return ESCAPE_INVALID_PARAMETER if the given parametes is invalid
 *          ESCAPE_COMPANY_EMAIL_DOES_NOT_EXIST - if the sys doesn't contain the
 *          company
 *          ESCAPE_RESERVATION_EXISTS - if one of the company's room is booked
 */
EscapeTechnionError companyRemove(EscapeTechnion sys, char* email);

/*!
 * function adds an escape room to the system
 * @param sys - points to the system to which the room is added
 * @param email - the company's mail to which the room belongs
 * @param id - the room's ID
 * @param price - the cost for a single person for the room, a power of four
 * @param num_ppl - the recommanded amount of people ofor the room
 * @param working_hrs - the room's working hours
 * @param difficulty - the room's difficulty
 * @return ESCAPE_INVALID_PARAMETER if the given parametes is invalid
 *          ESCAPE_COMPANY_EMAIL_DOES_NOT_EXIST - if the sys doesn't contain the
 *          company
 *          ESCAPE_ID_ALREADY_EXIST - given company has a room with the same ID
 */
EscapeTechnionError roomAdd(EscapeTechnion sys, char* email, int id, int price,
                     int num_ppl, char* working_hrs, int difficulty);

/*!
 * functinos removes a room from the system
 * @param sys - points to the system ADT
 * @param faculty - the faculty to which the room belongs
 * @param id - the room's ID
 * @return ESCAPE_INVALID_PARAMETER if the given parametes is invalid
 *          ESCAPE_ID_DOES_NOT_EXIST - room is not in the system
 *          ESCAPE_RESERVATION_EXISTS - if there is a standing order for the room
 */
EscapeTechnionError roomRemove(EscapeTechnion sys, TechnionFaculty faculty,
                               int id);

/*!
 * function adds a ner escaper to the system
 * @param sys - points to the system to add in.
 * @param email - the client's email, a string that contains exectly on '@'
 * @param faculty - the faculty to which the client belongs
 * @param skill_level - the client's skill level. a number between 1-10
 * @return ESCAPE_INVALID_PARAMETER if the given parametes is invalid
 *          ESCAPE_EMAIL_ALREADY_EXISTS - if the email exists in system.
 */
EscapeTechnionError escaperAdd(EscapeTechnion sys, char* email,
                        TechnionFaculty faculty, int skill_level);

/*!
 * functino removes a client from the system
 * @param sys - points to the system
 * @param email - the client's email address
 * @return ESCAPE_INVALID_PARAMETER if the given parametes is invalid
 *          ESCAPE_CLIENT_EMAIL_DOES_NOT_EXIST - if the sys doesn't contain the
 *          escaper
 */
EscapeTechnionError escaperRemove(EscapeTechnion sys, char* email);

/*!
 * function creates an order for an escape room. payment occurs on arrival.
 * orders for faculty members get a 25% discount.
 * @param sys - points to the system to create the order in
 * @param email - the client's email
 * @param faculty - the client's faculty
 * @param id - the desired room's ID
 * @param time - the desired arrival time
 * @param num_ppl - the amount of people the order is for
 * @return ESCAPE_INVALID_PARAMETER if the given parametes is invalid
 *          ESCAPE_CLIENT_EMAIL_DOES_NOT_EXIST - if the sys doesn't contain the
 *          escaper
 *          ESCAPE_ID_DOES_NOT_EXIST - room is not in the system
 *          ESCAPE_CLIENT_IN_ROOM - clent has a standing roder at the time.
 *          ESCAPE_ROOM_NOT_AVAILABLE - room has a standing order at the time.
 */
EscapeTechnionError escaperOrder(EscapeTechnion sys, char* email,
                          TechnionFaculty faculty, int id, char* time,
                          int num_ppl);

/*!
 * function creates an order for the nearest available time for the most
 * recommanded room for a client.
 * @param sys - points to the system
 * @param email - the client's email
 * @param num_ppl - the amount of people to creat the order to
 * @return ESCAPE_INVALID_PARAMETER if the given parametes is invalid
 *          ESCAPE_CLIENT_EMAIL_DOES_NOT_EXIST - if the sys doesn't contain the
 *          escaper
 *          ESCAPE_NO_ROOMS_AVAILABLE - there are no rooms in the system.
 */
EscapeTechnionError escaperRecommend(EscapeTechnion sys, char* email,
                                     int num_ppl);

/*!
 * functino prints all the orders that occured today.
 * removes the orders from the system and addvences the time log.
 * prints are formated accordnig to mtm_ex3.h
 * @param sys - points to the system.
 * @param outputChannel - where to print
 * @return -
 */
EscapeTechnionError reportDay(EscapeTechnion sys, FILE* outputChannel);

/*!
 * function prints the top 3 funtions that had the best revenue.
 * prints are formated accordnig to mtm_ex3.h
 * @param sys - points to the system ADT
 * @param outputChannel - where to print.
 * @return
 */
EscapeTechnionError reportBest(EscapeTechnion sys, FILE* outputChannel);

/*!
 * function reserts system. frees all allocated space.
 * @param sys - points to the system ADT.
 */
void resetSystem(EscapeTechnion sys);


#endif //HW3WET_ESCAPETECHNION_H
