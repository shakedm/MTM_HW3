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
 * @return MTM_NULL_PARAMETER if the email is NULL
 * @return MTM_INVALID_PARAMETER if the email adrress is not legal (no @)
 * @return MTM_OUT_OF_MEMORY if one of the mallocs failed
 * @return MTM_SUCCESS if all went well
 */
CompanyError initCompany(Company company, const char* email, TechnionFaculty faculty);

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
 *
 * @param company
 * @param room
 * @return
 */
CompanyError addRoomCompany(Company company, Room room);

CompanyError removeRoomCompany(Company company, Room room);

int compareCompany(void* company1, void* company2);

void* copyCompany(void* company);

/*!
 * function gets the compnay and returns its email as a const char*
 * the email cannot be changed from this function only read and compared to
 * @param company the ADT
 * @return the string that is the company email
 */
const char* getCompanyEmail(Company company);

Room findRoomInCompany(Company company, int Id);


#endif //HW3WET_COMPANY_H
