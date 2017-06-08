#include "order.h"


typedef struct order_t {
    int room_id;
    TechnionFaculty faculty;
    char* company_email;
    char* escaper_email;
    int time_until_order [HOURS_FORMAT];
    int num_of_people;
    int cost;
};

OrderError initOrder(Order order , int room_id, const char* company_email,
                       const char* escaper_email, int time[HOURS_FORMAT],
                       int num_of_visitors, int room_price,
                     TechnionFaculty faculty){
    assert(Order != NULL);
    if( escaper_email == NULL || company_email == NULL){
        return ORDER_NULL_PARAMETER;
    }
    if(time[DAYS] <= OPEN_HOUR || time[HOURS] < OPEN_HOUR ||
            time[HOURS]> HOURS_PER_DAY || room_id < 0 || num_of_visitors < 1 ||
            room_price < 0 || room_price %4 != 0 || faculty == UNKNOWN){
        return ORDER_INVALID_PARAMETER;
    }
    if (!emailCheck(company_email) || !emailCheck(escaper_email)){
        return ORDER_INVALID_PARAMETER;
    }
    char* company_copy = malloc(strlen(company_email) + 1);
    if(company_copy== NULL){
        return ORDER_OUT_OF_MEMORY;
    }
    char* escaper_copy = malloc(strlen(escaper_email) + 1);
    if(escaper_copy== NULL){
        free(company_copy);
        return ORDER_OUT_OF_MEMORY;
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
    order->faculty = faculty;
    return ORDER_SUCCESS;
}

Order createOrder(){
    return malloc(sizeof(Order));
}

void destroyOrder(void* order){
    resetOrder(order);
    free(*(Order*)order);
}

void* copyOrder(void* order){
    if(order == NULL)
        return NULL;
    Order copy_order = createOrder();
    if(!copy_order){
        return NULL;
    }
    int time_copy[HOURS_FORMAT] = {{0}};
    time_copy[DAYS] = getDaysOrder(order);
    time_copy[HOURS] = getHoursOrder(order);
    int room_price = getCost(order) / getNumOfVisitors(order);
    if(initOrder(copy_order, getOrderRoomID(order), getOrderCompanyEmail(order),
                 getEscaperEmail(order), time_copy,
                 getNumOfVisitors(order), room_price, getOderFaculty(order))
                != ORDER_SUCCESS){
        errorHandel(HANDEL_ORDER, (void*)ORDER_OUT_OF_MEMORY, ORDER, copy_order);
        return NULL;
    }
    return copy_order;
}

void resetOrder(void* order){
    if (order == NULL)
        return;
    if (((Order)order)->escaper_email != NULL ){ //fail-safe
        free(((Order)order)->escaper_email);
    }
    if (((Order)order)->company_email != NULL ){ //fail-safe
        free(((Order)order)->company_email);
    }
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
    return order->time_until_order[DAYS];
}

int getHoursOrder(Order order){
    assert(order!=NULL);
    return order->time_until_order[HOURS];
}

void decreaseDay(Order order){
    assert(order!= NULL);
    (order->time_until_order[DAYS])--;
}

int getOrderRoomId(Order order){
    assert(order!= NULL);
    return (order->room_id);
}

TechnionFaculty getOderFaculty(Order order){
    if(order == NULL){
        return UNKNOWN;
    }
    return order->faculty;
}

OrderError setDiscountOrder(Order order){
    if (order == NULL){
        return ORDER_NULL_PARAMETER;
    }
    order->cost = (int)(order->cost * DISCOUNT + 0.5);
    return ORDER_SUCCESS;
}

bool orderForEscaper(void* order, void* visitor_email){
    assert( order != NULL && visitor != NULL);
    int compare = strcmp((char*)visitor_email, ((Order)order)->escaper_email);
    if (compare == 0){
        return true;
    }
    return false;
}

bool orderAtTime(void* order, void* time[HOURS_FORMAT]){
    for (int i = 0; i < HOURS_FORMAT ; ++i) {
        if( ((Order)order)->time_until_order[i] != *(int*)time[i]){
            return false;
        }
    }
    return true;
}

bool orderForFaculty(void* order, void* faculty){
    return (((Order)order)->faculty == (TechnionFaculty)faculty);
}