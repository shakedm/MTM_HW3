
#ifndef HW3WET_ORDER_H
#define HW3WET_ORDER_H

#include "mtm_ex3.h"
#include "room.h"
#include "escaper.h"
#include "usefullFunctions.h"

#include <assert.h>

// the type of the ADT
typedef struct order_t* Order;

MtmErrorCode initOrder(Order* order , Room* room, Escaper* visitor,
                       int time[HOURS_FORMAT], int num_of_visitors, int cost);

void* copyOrder(void* order);

void resetOrder(void* order);

int getCost(Order order);

int getNumOfVisitors(Order order);

int getDaysOrder(Order order);

int getHoursOrder(Order order);

#endif //HW3WET_ORDER_H
