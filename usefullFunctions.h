#include "mtm_ex3.h"
#include "room.h"


#ifndef HW3WET_USEFULLFUNCTIONS_H
#define HW3WET_USEFULLFUNCTIONS_H


#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define GOOD_AMOUNT 1

/* * This function checks that the given email address is valid AI contines
 * exectly one @.
 * @param email - the given email string to check
 * @return false if the email address has more than one @ or none at all
 * true if the email address is valid
 */
bool emailCheck(char* email);


#endif //HW3WET_USEFULLFUNCTIONS_H
