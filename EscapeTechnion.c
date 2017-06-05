#include "EscapeTechnion.h"


struct escape_technion_t {
    Set companies;
    Set escapers;
    List orderList;
    int time_log; // counts days
};

MtmErrorCode createEscapeTechnion(EscapeTechnion *sys){
    EscapeTechnion new_system = malloc(sizeof(EscapeTechnion));
    if(!new_system ){
        return MTM_OUT_OF_MEMORY;
    }
    new_system->companies = setCreate(copyCompany, resetCompany, compareCompany);
    if(new_system->companies == NULL){
        free(new_system);
        return MTM_OUT_OF_MEMORY;
    }
    new_system->escapers = setCreate(copyEscaper, resetEscaper, compareEscaper);
    if(new_system->escapers == NULL){
        setDestroy(new_system->companies);
        free(new_system);
        return MTM_OUT_OF_MEMORY;
    }
    new_system->orderList = listCreate(copyOrder, resetOrder);
    if(new_system->orderList == NULL){
        setDestroy(new_system->escapers);
        setDestroy(new_system->companies);
        free(new_system);
        return MTM_OUT_OF_MEMORY;
    }
    new_system->time_log = 0;
    *sys = new_system;
}

MtmErrorCode companyAdd(EscapeTechnion sys, char* email,
                        TechnionFaculty faculty){
    Company *new_company = NULL;
    MtmErrorCode result = initCompany(new_company, email, faculty);
    if(result != MTM_SUCCESS){
        return result;
    }
    SetResult setResult = setAdd(sys->companies, (void*)new_company);
    if(setResult != SET_SUCCESS){
        return errorHandel(HANDEL_SET, (void*)setResult, COMPANY,
                           (void*)new_company);
    }
    return MTM_SUCCESS;
}

Company findCompanyByEmail(Set companies, char *email){
    int set_size = setGetSize(companies);
    Company curr_company = setGetFirst(companies);
    bool found = false;
    for (int i = 0; i < set_size ; ++i) {
        if(strcmp(getCompanyEmail(curr_company), email) == 0){
            found = true;
            break;
        }
        curr_company = setGetNext(companies);
    }
    if(found){
        return curr_company;
    }
    return NULL;
}

Company findCompanyByFaculty(Set companies, TechnionFaculty faculty){
    int set_size = setGetSize(companies);
    Company curr_company = setGetFirst(companies);
    bool found = false;
    for (int i = 0; i < set_size ; ++i) {
        if(getCompanyFaculty(curr_company) == faculty){
            found = true;
            break;
        }
        curr_company = setGetNext(companies);
    }
    if(found){
        return curr_company;
    }
    return NULL;
}

Escaper findEscaperInSet(Set escapers, char *email){
    int set_size = setGetSize(escapers);
    Escaper curr_escaper = setGetFirst(escapers);
    bool found = false;
    for (int i = 0; i < set_size ; ++i) {
        if(strcmp(getEscaperEmail(curr_escaper), email) == 0){
            found = true;
            break;
        }
        curr_escaper = setGetNext(escapers);
    }
    if(found){
        return curr_escaper;
    }
    return NULL;
}


MtmErrorCode companyRemove(EscapeTechnion sys, char* email){
    Company company = findCompanyByEmail(sys->companies, email);
    if(company != NULL){
        setRemove(sys->companies, company);
        return MTM_SUCCESS;
    }
    return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
}

MtmErrorCode roomAdd(EscapeTechnion sys, char* email, int id, int price,
                     int num_ppl, char* working_hrs, int difficulty){
    Company company = findCompanyByEmail(sys->companies, email);
    if(company == NULL){
        return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
    }
    Room *new_room = NULL;
    MtmErrorCode result = initRoom(new_room, getCompanyEmail(company), id,
                                   num_ppl, working_hrs, difficulty, price);
    if(result != MTM_SUCCESS){
        return result;
    }
    return addRoomCompany(company, *new_room);
}

MtmErrorCode roomRemove(EscapeTechnion sys, TechnionFaculty faculty, int id){
    Company company = findCompanyByFaculty(sys->companies, faculty);
    if(company == NULL){
        return MTM_INVALID_PARAMETER;
    }
    Room room = findRoomInCompany(company, id);
    if(room == NULL){
        return MTM_ID_DOES_NOT_EXIST;
    }
    if(orderExistForRoom(sys->orderList, room)){
        return MTM_RESERVATION_EXISTS;
    }
    return removeRoomCompany(company, room);
}

MtmErrorCode escaperAdd(EscapeTechnion sys, char* email,
                        TechnionFaculty faculty, int skill_level){
    Escaper *visitor = NULL;
    MtmErrorCode result = initEscaper(visitor, email, faculty, skill_level);
    if (result != MTM_SUCCESS){
        return result;
    }
    if(setIsIn(sys->escapers, visitor)){
        resetEscaper(visitor);
        return MTM_EMAIL_ALREADY_EXISTS;
    }
    SetResult setResult = setAdd(sys->escapers, visitor);
    if(setResult != SET_SUCCESS){
        return errorHandel(HANDEL_SET, (void*)setResult, ESCAPER,
                           (void*)visitor);
    }
    return MTM_SUCCESS;
}

MtmErrorCode escaperRemove(EscapeTechnion sys, char* email){
    Escaper visitor = findEscaperInSet(sys->escapers, email);
    if(visitor == NULL){
        return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
    }
    setRemove(sys->escapers, visitor);
    return MTM_SUCCESS;
}

MtmErrorCode escaperOrder(EscapeTechnion sys, char* email,
                          TechnionFaculty faculty, int id, int* time,
                          int num_ppl){
    Escaper visitor = findEscaperInSet(sys->escapers, email);
    if(visitor == NULL){
        return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
    }

}

MtmErrorCode escaperRecommend(EscapeTechnion sys, char* email, int num_ppl);

MtmErrorCode reportDay(EscapeTechnion sys);

MtmErrorCode reportBest(EscapeTechnion sys);

bool orderExistForRoom(List orders, Room room){
    int size = listGetSize(orders);
    Order curr_order = listGetFirst(orders);
    Room orderRoom;
    for (int i = 0; i < size; ++i) {
        orderRoom = getOrderRoom(curr_order);
        if(roomGetId(orderRoom) == roomGetId(room)){
            return true;
        }
        curr_order = listGetNext(orders);
    }
    return false;
}

void resetSystem(EscapeTechnion sys){
    setDestroy(sys->escapers);
    listDestroy(sys->orderList);
    setDestroy(sys->companies);
    free(sys);
}
