
#ifndef HW3WET_ORDER_H
#define HW3WET_ORDER_H

#include "mtm_ex3.h"
#include "room.h"
#include "escaper.h"
#include "usefullFunctions.h"

#include <assert.h>

#define DAYS 0
#define HOURS 1
#define DISCOUNT 0.75

// the type of the ADT
typedef struct order_t* Order;

/**
 * This type defines all errors for the Order ADT
 */
typedef enum {
    ORDER_OUT_OF_MEMORY,
    ORDER_NULL_PARAMETER,
    ORDER_INVALID_PARAMETER,
    ORDER_SUCCESS,
} OrderError;

/*!
 * function initialize a order from a a pointer to order and allocates the memory
 * needed for the ADT
 * @param order- the pointer that it recieves
 * @param room_id - the ID of the desired room
 * @param company_email - string to signefy the company's email
 * @param escaper_email- pointer to the escaper that made the order
 * @param time- an array with 2 blocks first for the days and second for hours
 * @param num_of_visitors- the number of people in this order
 * @param room_price - the cost of the desired room.
 * @return MTM_OUT_OF_MEMORY if malloc failed
 * @return MTM_INVALID_PARAMETERS if one of the parameters is not legal
 * @return MTM_NULL_PARAMETER if order is null
 * @return MTM_SUCCESS if all went well
 */
OrderError initOrder(Order order , int room_id, const char* company_email,
                     const char* escaper_email, int time[HOURS_FORMAT],
                     int num_of_visitors, int room_price,
                     TechnionFaculty faculty);

/*!
 * allocates the needed memory space for an Order ADT
 * @return NULL if allocation failed
 */
Order createOrder();

/*!
 * release all memory allocated for this ADT
 * @param order - the ADT to realse
 */
void destroyOrder(void* order);

/*!
 * function to copy all the order ADT
 * @param order- what we want to order
 * @return the new copy of the order
 */
void* copyOrder(void* order);

/*!
 * function to resert all fields and free the allocated memory
 * @param order- what we want to free
 */
void resetOrder(void* order);

/*!
 * function to reach the cost field
 * @param order- that we want to check
 * @return the cost of this order
 */
int getCost(Order order);

/*!
 * function to reach the num_of_ppl field
 * @param order- that we want to check
 * @return the number of people in the order
 */
int getNumOfVisitors(Order order);

/*!
 * function to reach the number of days till the order
 * @param order- the order we want to check
 * @return the first block in the time array which is a the number of days
 * until the order
 */
int getDaysOrder(Order order);

/*!
 * function to reach the hour of the order
 * @param order- the order we want to check
 * @return the second block of the time array which is the hour of the order
 */
int getHoursOrder(Order order);

/*!
 * function to decrease one day from the time left until the order
 * @param order- the order we want to do it to
 */
void decreaseDay(Order order);

/*!
 * Function returns the order room's ID
 * @param order - points to the room ADT
 * @return room ID
 */
int getOrderRoomID(Order order);

/*!
 * Function returns the email of the escaper that made the oder
 * @param order - points to the order ADT
 * @return email string
 */
const char* getOrderEscaperEmail(Order order);

/*!
 * Function returns the email of the company that owns the ordered room
 * @param order - points to the order ADT
 * @return email string
 */
const char* getOrderCompanyEmail(Order order);

/*!
 * Function returns the faculty of the desired order
 * @param order points to Order ADT
 * @return the faculy
 * UNKNOWN if order is NULL
 */
TechnionFaculty getOderFaculty(Order order);

/*!
 * This function resets the order price to a dicounted figure;
 * @param order - points to the Order to reset
 * @return ORDER_NULL_PARAMETER if Order is NULL
 */
OrderError setDiscountOrder(Order order);

//Filter functions:

bool orderForEscaper(void* order, void* visitor_email);

bool orderAtDay(void* order, void* day);

bool orderForFaculty(void* order, void* faculty);

#endif //HW3WET_ORDER_H
