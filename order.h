
#ifndef HW3WET_ORDER_H
#define HW3WET_ORDER_H

#include "mtm_ex3.h"
#include "room.h"
#include "escaper.h"
#include "usefullFunctions.h"

#include <assert.h>

// the type of the ADT
typedef struct order_t* Order;


/*!
 * function initialize a order from a a pointer to order and allocates the memory
 * needed for the ADT
 * @param order- the pointer that it recieves
 * @param room- pointer to the room of the order
 * @param escaper- pointer to the escaper that made the order
 * @param time- an array with 2 blocks first for the days and second for hours
 * @param num_of_visitors- the number of people in this order
 * @param cost - the total cost of the order, already calculated
 * @return MTM_OUT_OF_MEMORY if malloc failed
 * @return MTM_INVALID_PARAMETERS if one of the parameters is not legal
 * @return MTM_NULL_PARAMETER if order is null
 * @return MTM_SUCCESS if all went well
 */
MtmErrorCode initOrder(Order* order , Room* room, Escaper* escaper,
                       int time[HOURS_FORMAT], int num_of_visitors, int cost);



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
 * @param order
 * @return
 */
int getCost(Order order);

int getNumOfVisitors(Order order);

int getDaysOrder(Order order);

int getHoursOrder(Order order);

#endif //HW3WET_ORDER_H
