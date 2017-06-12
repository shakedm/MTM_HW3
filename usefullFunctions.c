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

EscapeTechnionError setErrorHandel(SetResult result, int sender_ID, void* ADT){
    switch (result){
        case SET_OUT_OF_MEMORY :
            return memoryFaultHandel(sender_ID, ADT);
        case SET_NULL_ARGUMENT:
            return ESCAPE_NULL_PARAMETER;
        case SET_ITEM_ALREADY_EXISTS:
            switch (sender_ID){
                case COMPANY:
                    return ESCAPE_EMAIL_ALREADY_EXISTS;
                case ROOM:
                    return ESCAPE_ID_ALREADY_EXIST;
                default:
                    return ESCAPE_INVALID_PARAMETER;
            }
        case SET_ITEM_DOES_NOT_EXIST:
            switch (sender_ID){
                case COMPANY:
                    return ESCAPE_COMPANY_EMAIL_DOES_NOT_EXIST;
                case ROOM:
                    return ESCAPE_ID_DOES_NOT_EXIST;
                case ESCAPER:
                    return ESCAPE_CLIENT_EMAIL_DOES_NOT_EXIST;
                default:
                    return ESCAPE_INVALID_PARAMETER;
            }
        default:
            return ESCAPE_INVALID_PARAMETER;
    }
}


EscapeTechnionError memoryFaultHandel(int sender_ID, void* ADT){
    switch (sender_ID){
        case ROOM:
            destroyRoom(ADT);
            break;
        case ESCAPER:
            destroyEscaper(ADT);
            break;
        case COMPANY:
            destroyCompany(ADT);
            break;
        case ESCAPE_TECHNION:
            resetSystem(*(EscapeTechnion*)ADT);
            break;
        default:
            return ESCAPE_OUT_OF_MEMORY;
    }
    return ESCAPE_OUT_OF_MEMORY;
}


EscapeTechnionError errorHandel(int GdtId, void* result, int sender_ID, void* ADT){
    switch (GdtId){
        case HANDEL_SET:
            return setErrorHandel((SetResult)result, sender_ID, ADT);
        case HANDEL_LIST:
            return listErrorHandel((ListResult)result, sender_ID, ADT);
        case HANDEL_ORDER:
            return orderErrorHandel((OrderError)result, sender_ID, ADT);
        case HANDEL_ROOM:
            return roomErrorHandel((RoomError)result, sender_ID, ADT);
        case HANDEL_COMPANY:
            return companyErrorHandel((CompanyError)result, sender_ID, ADT);
        case HANDEL_ESCAPER:
            return escaperErrorHandel((EscaperError)result, sender_ID, ADT);
        default:
            return ESCAPE_INVALID_PARAMETER;
    }
}

bool translateHours(char* working_hours, int *time, bool order){
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
        if(!order || hours_index == HOURS_FORMAT - 1){
            if(time[hours_index] > HOURS_PER_DAY){
                return false;
            }
        }
        working_hours++;
    }
    if(!order){
        if (time[OPEN_HOUR] >= time[CLOSE_HOUR]){
            return false;
        }
    }
    return true;
}


EscapeTechnionError listErrorHandel(ListResult result, int sender_ID, void* ADT){
    switch (result){
        case LIST_OUT_OF_MEMORY :
            return memoryFaultHandel(sender_ID, ADT);
        case LIST_NULL_ARGUMENT:
            return ESCAPE_NULL_PARAMETER;
        case LIST_INVALID_CURRENT:
            return ESCAPE_INVALID_PARAMETER;
        default:
            return ESCAPE_INVALID_PARAMETER;
    }
}

EscapeTechnionError orderErrorHandel(OrderError result, int sender_ID, void* ADT){
    switch (result){
        case ORDER_OUT_OF_MEMORY :
            return memoryFaultHandel(sender_ID, ADT);
        case ORDER_NULL_PARAMETER:
            return ESCAPE_NULL_PARAMETER;
        case ORDER_INVALID_PARAMETER:
            return ESCAPE_INVALID_PARAMETER;
        default:
            return ESCAPE_INVALID_PARAMETER;
    }
}

EscapeTechnionError roomErrorHandel(RoomError result, int sender_ID, void* ADT){
    switch (result){
        case ROOM_OUT_OF_MEMORY :
            return memoryFaultHandel(sender_ID, ADT);
        case ROOM_NULL_PARAMETER:
            return ESCAPE_NULL_PARAMETER;
        case ROOM_INVALID_PARAMETER:
            return ESCAPE_INVALID_PARAMETER;
        default:
            return ESCAPE_INVALID_PARAMETER;
    }
}

EscapeTechnionError companyErrorHandel(CompanyError result, int sender_ID, void* ADT){
    switch (result){
        case COMPANY_OUT_OF_MEMORY:
            return memoryFaultHandel(sender_ID, ADT);
        case COMPANY_NULL_ARGUMENT:
            return ESCAPE_NULL_PARAMETER;
        case COMPANY_INVALID_ARGUMENT:
            return ESCAPE_INVALID_PARAMETER;
        case COMPANY_ID_ALREADY_EXIST:
            return ESCAPE_ID_ALREADY_EXIST;
        case COMPANY_ID_DOES_NOT_EXIST:
            return ESCAPE_ID_DOES_NOT_EXIST;
        default:
            return ESCAPE_INVALID_PARAMETER;
    }
}

EscapeTechnionError escaperErrorHandel(EscaperError result, int sender_ID, void* ADT){
    switch (result){
        case ESCAPER_OUT_OF_MEMORY :
            return memoryFaultHandel(sender_ID, ADT);
        case ESCAPER_NULL_PARAMETER:
            return ESCAPE_ID_DOES_NOT_EXIST;
        case ESCAPER_INVALID_PARAMETER:
            return ESCAPE_INVALID_PARAMETER;
        default:
            return ESCAPE_INVALID_PARAMETER;
    }
}