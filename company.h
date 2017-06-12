#include "mtm_ex3.h"


#ifndef HW3WET_COMPANY_H
#define HW3WET_COMPANY_H

#include <stdbool.h>
#include "room.h"
#include "set.h"
/* type to define the company struct */
typedef struct company_t* Company;

typedef enum  {
    COMPANY_SUCCESS,
    COMPANY_NULL_ARGUMENT,
    COMPANY_OUT_OF_MEMORY,
    COMPANY_INVALID_ARGUMENT,
    COMPANY_ID_ALREADY_EXIST,
    COMPANY_ID_DOES_NOT_EXIST,
} CompanyError;

/*!
 * this function init and create the Company ADT from a given pointer
 * @param company points to the memory space given to the ADT
 * @param email- a string that is the identefier for each company
 * @param faculty-  a ENUM of the faculties in Technion
 * also initiate a set of rooms for the company that is empty in the start
 * revenue of the company is 0
 * @return COMPANY_NULL_ARGUMENT if the email is NULL
 * @return COMPANY_INVALID_ARGUMENT if the email adrress is not legal (no @)
 * @return COMPANY_OUT_OF_MEMORY if one of the mallocs failed
 * @return COMPANY_SUCCESS if all went well
 */
CompanyError initCompany(Company company, const char* email,
                         TechnionFaculty faculty);

/*!
 * this function reset and free all the ADT fields and the ADT itself
 * @param company void pointer to the ADT for generic use in set and list
 */
void resetCompany(void* company);

/*!
 * allocates the needed memory space for an Company ADT
 * @return NULL if allocation failed
 */
Company createCompany();

/*!
 * release all memory allocated for this ADT
 * @param order - the ADT to realse
 */
void destroyCompany(void* company);

/*!
 * function returns the faculty of the company
 * @param company the ADT of company
 * @return company->faculty
 */
TechnionFaculty getCompanyFaculty(Company company);

/*!
 * get the revenue of the company
 * @param company the ADT
 * @return the field revenue int the company
 */
int getCompanyRevenue(Company company);

/*!
 * Functun returns the Company's room set pointer
 * @param company - points to company ADT
 * @return NULL is company is NULL;
 */
Set getCompanyRooms(Company company);

/*!
 *function addes room to the company
 * @param company - points to the company ADT
 * @param room - the ADT room to add
 * @return COMPANY_ID_ALREADY_EXIST - if there is a room with that ID
 *          COMPANY_NULL_ARGUMENT - if company / room is NULL
 *          COMPANY_OUT_OF_MEMORY - if allocation failed.
 */
CompanyError addRoomCompany(Company company, Room room);

/*!
 * function removes a room from company set
 * @param company - points to the company
 * @param room - the room to remove.
 * @return COMPANY_ID_DOES NOT_EXIST - if there is no room with that ID
 *          COMPANY_NULL_ARGUMENT - if company / room is NULL
 */
CompanyError removeRoomCompany(Company company, Room room);

/*
 * function adds a day's revenue to company's revenue.
 */
void addCompanyRevenue(Company company, int revenue);

/*!
 * function compares to companies by their email
 * @param company1 - points to the 1st company ADT
 * @param company2 - points to the 2nd comopany's ADT
 * @return positive int if 1st company is before 2sd
 *          negative int if 2nd company is before first
 *          0 if the same
 */
int compareCompany(void* company1, void* company2);

/*!
 * function copies a company ADT
 * @param company - points to the company to copy
 * @return NULL if allocation fails
 */
void* copyCompany(void* company);

/*!
 * function gets the compnay and returns its email as a const char*
 * the email cannot be changed from this function only read and compared to
 * @param company the ADT
 * @return the string that is the company email
 */
const char* getCompanyEmail(Company company);

/*!
 * function fins room in company set, and returns a pointer to it.
 * @param company - the company's ADT
 * @param Id - the desired room's ID
 * @return NULL if room is not in set.
 */
Room findRoomInCompany(Company company, int Id);


#endif //HW3WET_COMPANY_H
