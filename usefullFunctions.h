#include "mtm_ex3.h"
#include "room.h"
#include "set.h"
#include "list.h"
#include "escaper.h"
#include "company.h"
#include "EscapeTechnion.h"

#ifndef HW3WET_USEFULLFUNCTIONS_H
#define HW3WET_USEFULLFUNCTIONS_H


#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define GOOD_AMOUNT 1
#define COMPANY 10
#define ESCAPER 20
#define ROOM 30
#define ESCAPE_TECHNION 40
#define HANDEL_SET 100
#define HANDEL_LIST 110
#define MAX_SKILL 10
#define MIN_SKILL 1


/* * This function checks that the given email address is valid AI contines
 * exectly one @.
 * @param email - the given email string to check
 * @return false if the email address has more than one @ or none at all
 * true if the email address is valid
 */
bool emailCheck(char* email);

/* * This Function handels cases in which a set action fails according to the
 * error masseges
 * @param result the error result the action returned
 * @param sender_ID signefies the ADT from which the action was taken.
 * @param ADT points to the ADT to handel
 * @return the correct error massege after handeling the fault.
 */
MtmErrorCode setErrorHandel(SetResult result, int sender_ID, void* ADT);

/* * This Function handels cases in which a list action fails according to the
 * error masseges
 * @param result the error result the action returned
 * @param sender_ID signefies the ADT from which the action was taken.
 * @param ADT points to the ADT to handel
 * @return the correct error massege after handeling the fault.
 */
MtmErrorCode listErrorHandel(ListResult result, int sender_ID, void* ADT);

/* * This Function handels a memory fault in allocation. frees all priviously
 * allocated space
 * @param sender_ID to ID the ADT to handel
 * @param ADT points to the ADT to free
 * @return MTM_OUT_OF_MEMORY after freeing
 */
MtmErrorCode memoryFaultHandel(int sender_ID, void* ADT);

/* * This Function handels cases in which a set action fails according to the
 * error masseges
 * @param GdtId - to sort for List or Set hadel functions
 * @param result the error result the action returned
 * @param sender_ID signefies the ADT from which the action was taken.
 * @param ADT points to the ADT to handel
 * @return the correct error massege after handeling the fault.
 */
MtmErrorCode errorHandel(int GdtId, void* result, int sender_ID, void* ADT);


#endif //HW3WET_USEFULLFUNCTIONS_H
