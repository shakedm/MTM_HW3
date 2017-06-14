
#ifndef HW3WET_USEFULLFUNCTIONS_H
#define HW3WET_USEFULLFUNCTIONS_H

//#include "EscapeTechnion.h"
#include "mtm_ex3.h"
#include "set.h"
#include "list.h"

#define GOOD_AMOUNT 1
#define COMPANY 10
#define ESCAPER 20
#define ROOM 30
#define ESCAPE_TECHNION 40
#define ORDER 50
#define FACULTY 60
#define HANDEL_SET 100
#define HANDEL_LIST 110
#define HANDEL_ORDER 120
#define HANDEL_ESCAPER 130
#define HANDEL_ROOM 140
#define HANDEL_COMPANY 150
#define HANDEL_FACULTY 160
#define MAX_SKILL 10
#define MIN_SKILL 1
#define HOURS_FORMAT 2
#define BAD_HOURS -1
#define HOURS_PER_DAY 24
#define OPEN_HOUR 0
#define CLOSE_HOUR 1


/* * This function checks that the given email address is valid AI contines
 * exectly one @.
 * @param email - the given email string to check
 * @return false if the email address has more than one @ or none at all
 * true if the email address is valid
 */
bool emailCheck(char* email);

/*  * This function translate the hours string to int array while checking the
 * validity of the string.
 * return true if the string is traslated properly.
 * false if the string is not to format.
 */
bool translateHours(char* working_hours, int *time, bool order);

#endif //HW3WET_USEFULLFUNCTIONS_H
