#include "mtm_ex3.h"
#ifndef HW3WET_ESCAPER_H
#define HW3WET_ESCAPER_H

/* type to define the escaper struct*/
typedef struct escaper_t* Escaper;

/**
 * This type defines all errors for the Order ADT
 */
typedef enum {
    ESCAPER_OUT_OF_MEMORY,
    ESCAPER_NULL_PARAMETER,
    ESCAPER_INVALID_PARAMETER,
    ESCAPER_SUCCESS,
} EscaperError;

/*!
 * allocates the needed memory space for an Escaper ADT
 * @return NULL if allocation failed
 */
Escaper createEscaper();

/*!
 * release all memory allocated for this ADT
 * @param order - the ADT to realse
 */
void destroyEscaper(void* escaper);

/*!
 * function to initialize the struct and its fields
 * @param visitor recieves a pointer to the struct and alllocates space for it
 * @param email a string that is the identifier of the escaper
 * @param faculty- the faculty of the visitor
 * @param skill_level - integer of 1-10 for the skill of the visitor
 * @return ESCAPER_NULL_PARAMETER if the visitor is NULL
 * @return ESCAPER_INVALID_PARAMETER if the skill level or the email are not legal
 * parameters or not in range
 * @return ESCAPER_OUT_OF_MEMORY if one of the allocations failed
 * @return ESCAPER_SUCCESS if all went well
 */
EscaperError initEscaper(Escaper visitor, const char* email, TechnionFaculty faculty,
                            int skill_level);


/*!
 * functions reset and free all allocated fields then free the ADT itself
 * @param visitor the ADT that need to be freed
 */
void resetEscaper(void* visitor);

/*!
 * function returns a const string so the email can only be read from this
 * function but not changed
 * @param visitor - a pointer to an escaper
 * @return the const string of the email
 */
const char* getEscaperEmail(Escaper visitor);

/*!
 * function to get the field
 * @param visitor pointer to the escaper
 * @return the faculty of said escaper
 */
TechnionFaculty getEscaperFaculty(Escaper visitor);

/*!
 * function to reach the skill level of the escaper
 * @param visitor a pointer of the escaper
 * @return an integer that is the skill level of the escaper
 */
int getEscaperSkillLevel(Escaper visitor);

/*!
 * function to comapare two visitors
 * @param visitor1 the first visitor
 * @param visitor2 the second visitor
 * @return 0 if the emails are the same >0 if first is smaller <0
 * if second is smaller by lexicography order
 */
int compareEscaper(void* visitor1, void* visitor2);

/*!
 * functions copies the Escaper ADT
 * @param escaper - points to the ADT to copy
 * @return NULL if aloocation failes.
 */
void* copyEscaper(void* escaper);

#endif //HW3WET_ESCAPER_H
