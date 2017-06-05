#include "order.h"


typedef struct order_t {
    Room* room;
    Escaper* escaper;
    int time_until_order [HOURS_FORMAT];
    int num_of_people;
    int cost;
};

MtmErrorCode initOrder(Order* order , Room* room, Escaper* escaper,
                       int time[HOURS_FORMAT], int num_of_visitors, int cost){
    if( order == NULL)
        return MTM_NULL_PARAMETER;
    if(time[days]<= BAD_HOURS || time[hours]<= BAD_HOURS ||
            time[hours]> HOURS_PER_DAY || cost < 0 || num_of_visitors <1)
        return MTM_INVALID_PARAMETER;
    Order new_order = malloc(sizeof(Order));
    if(new_order== NULL)
        return MTM_OUT_OF_MEMORY;
    new_order->escaper= escaper;
    new_order->room = room;
    new_order->cost = cost;
    new_order->num_of_people = num_of_visitors;
    for (int i = 0; i <HOURS_FORMAT ; ++i) {
        new_order->time_until_order[i] = time[i];
    }
    *order= new_order;
    return MTM_SUCCESS;
}

void* copyOrder(void* order){
    if(order == NULL)
        return NULL;
    Order *copy_order;
    if(initOrder(copy_order, ((Order)order)->room,((Order)order)->escaper,
              ((Order)order)->time_until_order, ((Order)order)->num_of_people,
              ((Order)order)->cost) != MTM_SUCCESS)
        return NULL;
    return copy_order;
}
void resetOrder(void* order){
    if (order == NULL)
        return;
    ((Order)order)->escaper = NULL;
    ((Order)order)->room = NULL;
    free(order);
}
int getCost(Order order){
    assert(order!= NULL);
    return order->cost;
}
int getNumOfVisitors(Order order){
    assert(order!=NULL);
    return order->num_of_people;
}
int getDaysOrder(Order order){
    assert(order!= NULL);
    return order->time_until_order[days];
}
int getHoursOrder(Order order){
    assert(order!=NULL);
    return order->time_until_order[hours];
}
void decreaseDay(Order order){
    assert(order!= NULL);
    (order->time_until_order[days])--;
}