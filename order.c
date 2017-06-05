#include "order.h"


typedef struct order_t {
    Room* room;
    Escaper* escaper;
    int time_until_order [HOURS_FORMAT];
    int num_of_people;
    int cost;
};

MtmErrorCode initOrder(Order* order , Room* room, Escaper* visitor,
                       int time[HOURS_FORMAT], int num_of_visitors, int cost){
    if( order == NULL)
        return MTM_NULL_PARAMETER;
    Order new_order = malloc(sizeof(Order));
    if(new_order== NULL)
        return MTM_OUT_OF_MEMORY;
    new_order->escaper= visitor;
    new_order->room = room;
    new_order->cost = cost;
    new_order->num_of_people = num_of_visitors;
    for (int i = 0; i <HOURS_FORMAT ; ++i) {
        new_order->time_until_order[i] = time[i];
    }
    *order= new_order;
    return MTM_SUCCESS;
}
