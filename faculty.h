#ifndef HW3WET_FACULTY_H
#define HW3WET_FACULTY_H

#include "mtm_ex3.h"
#include "company.h"
#include "room.h"

/* type to define the escaper struct*/
typedef struct faculty_t* Faculty;

/**
 * This type defines all errors for the Order ADT
 */
typedef enum {
    FACULTY_OUT_OF_MEMORY,
    FACULTY_NULL_PARAMETER,
    FACULTY_INVALID_PARAMETER,
    FACULTY_EMAIL_ALREADY_EXISTS,
    FACULTY_COMPANY_EMAIL_DOES_NOT_EXIST,
    FACULTY_ID_DOES_NOT_EXIST,
    FACULTY_ID_ALREADY_EXIST,
    FACULTY_SUCCESS,
} FacultyError;

/*!
 * allocates the needed memory space for an Faculty ADT
 * @return NULL if allocation failed
 */
Faculty createFaculty();

/*!
 * release all memory allocated for this ADT
 * @param order - the ADT to realse
 */
void destroyFaculty(void* faculty);

/*!
 * function to initialize the struct and its fields
 * @param faculty recieves a pointer to the struct and alllocates space for it
 * @param faculty_ID - the faculty ID (in the TechnionFaculty enum)
 * @return FACULTY_NULL_PARAMETER if the faculty is NULL
 * @return FACULTY_INVALID_PARAMETER if the faculty ID is not a legal
 * parameters or not in enum.
 * @return FACULTY_OUT_OF_MEMORY if one of the allocations failed
 * @return FACULTY_SUCCESS if all went well
 */
FacultyError initFaculty(Faculty faculty, TechnionFaculty faculty_ID);


/*!
 * functions reset and free all allocated fields.
 * @param faculty the ADT that need to be freed
 */
void resetFaculty(Faculty faculty);

/*!
 * Function find a room ADT int the faculty
 * @param faculty - the faculty ADT to check
 * @param id - the desired room's ID
 * @return NULL if room does not belong to faculty
 * room ADT if all went well
 */
Room findRoomInFaculty(Faculty faculty, int id);

/*!
* Function find a company ADT int the faculty
* @param faculty - the faculty ADT to check
* @param email - the desired company's email
* @return NULL if company does not belong to faculty
* company ADT if all went well
*/
Company findCompanyInFaculty(Faculty faculty, char* email);

/*!
 *function addes company to the faculty
 * @param faculty - points to the company ADT
 * @param company - the ADT company to add
 * @return FACULTY_EMAIL_ALREADY_EXISTS - if there is a company with that email
 *          FACULTY_NULL_ARGUMENT - if company / faculty is NULL
 *          COMPANY_OUT_OF_MEMORY - if allocation failed.
 */
FacultyError addFacultyCompany(Faculty faculty, Company company);

FacultyError removeFacultyCompany(Faculty faculty, Company company);

Company findWhereRoom(Faculty faculty, int id);


/*!
 *function addes room to the faculty
 * @param faculty - points to the faculty ADT
 * @param room - the ADT room to add
 * @return FACULTY_ID_ALREADY_EXIST - if there is a room with that ID
 *          FACULTY_NULL_ARGUMENT - if faculty / room is NULL
 *          FACULTY_OUT_OF_MEMORY - if allocation failed.
 */
//FacultyError addFacultyRoom(Faculty faculty, Room *room);

//FacultyError removeFacultyRoom(Faculty faculty, Room *room);

/*!
 * function to comapare two visitors
 * @param faculty1 the first faculty
 * @param faculty2 the second faculty
 * @return 0 if the faculty_ID are the same >0 if first is smaller <0
 * if second is smaller by enum order
 */
int compareFaculty(void* faculty1, void* faculty2);

/*!
 * function return the faculty ID in enum.
 * @param faculty - points to the paculty ADT
 * @return UKNOWN if faculty is NULL
 *          TechnionFaculty if all went well.
 */
TechnionFaculty getFacultyID (Faculty faculty);

/*!
 * function returns the total revenue for all the faculty companies
 * @param faculty - points to the faculty ADT
 * @return -1 if faculty is NULL
 *          revenue if all went well
 */
int getFacultyRevenue (Faculty faculty);

/*!
 * functions copies the faculty ADT
 * @param faculty - points to the ADT to copy
 * @return NULL if allooation failes.
 */
void* copyFaculty(void* faculty);

/*!
 * function sums up all the companay's revenue and adds to total faculty revenue.
 * @param faculty - points to Faculty ADT
 */
void collectRevenue(Faculty faculty);

//void* copyRoomPtr(void* room);

void* copyCompanyPtr(void* company);

//void destroyRoomPtr(void* room);

void destroyCompanyPtr(void* company);

//int compareRoomPtr(void* room1, void* room2);

int compareCompanyPtr(void* company1, void* company2);

#endif //HW3WET_FACULTY_H
