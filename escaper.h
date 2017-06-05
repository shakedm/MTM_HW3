#include "mtm_ex3.h"
#ifndef HW3WET_ESCAPER_H
#define HW3WET_ESCAPER_H

/* type to define the escaper struct*/
typedef struct escaper_t* Escaper;

/*!
 * function to initialize the struct and its fields
 * @param visitor recieves a pointer to the struct and alllocates space for it
 * @param email a string that is the identifier of the escaper
 * @param faculty- the faculty of the visitor
 * @param skill_level - integer of 1-10 for the skill of the visitor
 * @return MTM_NULL_PARAMETER if the visitor is NULL
 * @return MTM_INVALID_PARAMETER if the skill level or the email are not legal
 * parameters or not in range
 * @return MTM_OUT_OF_MEMORY if one of the allocations failed
 * @return MTM_SUCCESS if all went well
 */
MtmErrorCode initEscaper(Escaper *visitor, char* email, TechnionFaculty faculty,
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
int compareEscaper(Escaper visitor1, Escaper visitor2);


void* copyEscaper(void* escaper);

#endif //HW3WET_ESCAPER_H
