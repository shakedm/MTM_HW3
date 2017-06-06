#include "order.h"


typedef struct order_t {
    int room_id;
    char* company_email;
    char* escaper_email;
    int time_until_order [HOURS_FORMAT];
    int num_of_people;
    int cost;
};

MtmErrorCode initOrder(Order order , int room_id, char* company_email,
                       char* escaper_email, int time[HOURS_FORMAT],
                       int num_of_visitors, int room_price){
    assert(Order != NULL);
    if( escaper_email == NULL || company_email == NULL)
        return MTM_NULL_PARAMETER;
    if(time[days] <= OPEN_HOUR || time[hours] < OPEN_HOUR ||
            time[hours]> HOURS_PER_DAY || room_id < 0 || num_of_visitors < 1 ||
            room_price < 0 || room_price %4 != 0)
        return MTM_INVALID_PARAMETER;
    char* company_copy = malloc(strlen(company_email) + 1);
    if(company_copy== NULL){
        return MTM_OUT_OF_MEMORY;
    }
    char* escaper_copy = malloc(strlen(escaper_email) + 1);
    if(escaper_copy== NULL){
        free(company_email);
        return MTM_OUT_OF_MEMORY;
    }
    strcpy(company_copy, company_email);
    strcpy(escaper_copy, escaper_email);
    order->room_id = room_id;
    order->escaper_email= escaper_copy;
    order->company_email = company_copy;
    order->num_of_people = num_of_visitors;
    order->cost = num_of_visitors * room_price;
    for (int i = 0; i < HOURS_FORMAT ; ++i) {
        order->time_until_order[i] = time[i];
    }
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
Room getOrderRoom(Order order){
    assert(order!= NULL);
    return (*order->room);
}

bool orderForEscaper(Order order, Escaper visitor){
    assert( order != NULL && visitor != NULL);
    int compare = strcmp(getEscaperEmail((*order->escaper)),
                         getEscaperEmail(visitor));
    if (compare == 0){
        return true;
    }
    return false;
}

bool orderAtTime(Order order, int time[HOURS_FORMAT]){

}