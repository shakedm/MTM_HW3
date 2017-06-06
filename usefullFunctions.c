#include "usefullFunctions.h"

bool emailCheck(const char* email){
    int counter = 0;
    int index = 0;
    while (email[index] != '\0'){
        if(email[index] == '@'){
            counter++;
        }
        index++;
    }
    if (counter != GOOD_AMOUNT ){
        return false;
    }
    return true;
}

MtmErrorCode setErrorHandel(SetResult result, int sender_ID, void* ADT){
    switch (result){
        case SET_OUT_OF_MEMORY :
            return memoryFaultHandel(sender_ID, ADT);
        case SET_NULL_ARGUMENT:
            return MTM_NULL_PARAMETER;
        case SET_ITEM_ALREADY_EXISTS:
            switch (sender_ID){
                case COMPANY:
                    return MTM_ID_ALREADY_EXIST;
                case ESCAPE_TECHNION:
                    return MTM_EMAIL_ALREADY_EXISTS;
                default:
                    return MTM_INVALID_PARAMETER;
            }
        case SET_ITEM_DOES_NOT_EXIST:
            switch (sender_ID){
                case COMPANY:
                    return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
                case ROOM:
                    return MTM_ID_DOES_NOT_EXIST;
                case ESCAPER:
                    return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
                default:
                    return MTM_INVALID_PARAMETER;
            }
        default:
            return MTM_INVALID_PARAMETER;
    }
}


MtmErrorCode memoryFaultHandel(int sender_ID, void* ADT){
    switch (sender_ID){
        case ROOM:
            resetRoom(*(Room*)ADT);
            break;
        /*case ESCAPER:
            resetEscaper(*(Escaper*)ADT);
            break;
        case COMPANY:
            resetCompany(*(Company*)ADT);
            break;
        case ESCAPE_TECHNION:
            resetSystem(*(EscapeTechnion*)ADT);
            break;*/
        default:
            return MTM_OUT_OF_MEMORY;
    }
    return MTM_OUT_OF_MEMORY;
}


MtmErrorCode errorHandel(int GdtId, void* result, int sender_ID, void* ADT){
    switch (GdtId){
        case HANDEL_SET:
            return setErrorHandel((SetResult)result, sender_ID, ADT);
        case HANDEL_LIST:
            return listErrorHandel((ListResult)result, sender_ID, ADT);
        /*case HANDEL_ORDER:
            return orderErrorHandel((OrderError)result, sender_ID, ADT);*/
        default:
            return MTM_INVALID_PARAMETER;
    }
}

bool translateHours(char* working_hours, int *time){
    assert(working_hours != NULL);
    int hours_index = 0;
    while(*working_hours != '\0'){
        if(*working_hours < '0' || *working_hours > '9'){
            if (*working_hours != '-'){
                time[0] = BAD_HOURS;
                time[1] = BAD_HOURS;
                return false;
            }
            hours_index++;
            if (hours_index == HOURS_FORMAT) {
                return false;
            }
            working_hours++;
            continue;
        }
        time[hours_index] = (time[hours_index] * 10) + (*working_hours - '0');
        if(time[hours_index] > HOURS_PER_DAY){
            return false;
        }
        working_hours++;
    }
    if (time[OPEN_HOUR] >= time[CLOSE_HOUR]){
        return false;
    }
    return true;
}


MtmErrorCode listErrorHandel(ListResult result, int sender_ID, void* ADT){
    switch (result){
        case LIST_OUT_OF_MEMORY :
            return memoryFaultHandel(sender_ID, ADT);
        case LIST_NULL_ARGUMENT:
            return MTM_NULL_PARAMETER;
        case LIST_INVALID_CURRENT:
            return MTM_INVALID_PARAMETER;
        default:
            return MTM_INVALID_PARAMETER;
    }
}

/*MtmErrorCode orderErrorHandel(OrderError result, int sender_ID, void* ADT){
    switch (result){
        case ORDER_OUT_OF_MEMORY :
            return memoryFaultHandel(sender_ID, ADT);
        case ORDER_NULL_PARAMETER:
            return MTM_NULL_PARAMETER;
        case ORDER_INVALID_PARAMETER:
            return MTM_INVALID_PARAMETER;
        default:
            return MTM_INVALID_PARAMETER;
    }
}*/