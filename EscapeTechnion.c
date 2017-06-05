#include "EscapeTechnion.h"


struct escape_technion_t {
    Set companies;
    List escaperList;
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
    new_system->escaperList = listCreate(copyEscaper, resetEscaper);
    if(new_system->escaperList == NULL){
        setDestroy(new_system->companies);
        free(new_system);
        return MTM_OUT_OF_MEMORY;
    }
    new_system->orderList = listCreate(copyOder, resetOrder);
    if(new_system->orderList == NULL){
        listDestroy(new_system->escaperList);
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

Company findCompanyInSet(Set companies, char *email){
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


MtmErrorCode companyRemove(EscapeTechnion sys, char* email){
    Company company = findCompanyInSet(sys->companies, email);
    if(company != NULL){
        setRemove(sys->companies, company);
        return MTM_SUCCESS;
    }
    return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
}

MtmErrorCode roomAdd(EscapeTechnion sys, char* email, int id, int price,
                     int num_ppl, char* working_hrs, int difficulty){
    Company company = findCompanyInSet(sys->companies, email);
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

MtmErrorCode roomRemove(EscapeTechnion sys, TechnionFaculty faculty, int id);

MtmErrorCode escaperAdd(EscapeTechnion sys, char* email,
                        TechnionFaculty faculty, int skill_level);

MtmErrorCode escaperRemove(EscapeTechnion sys, char* email);

MtmErrorCode escaperOrder(EscapeTechnion sys, char* email,
                          TechnionFaculty faculty, int id, int* time,
                          int num_ppl);

MtmErrorCode escaperRecommend(EscapeTechnion sys, char* email, int num_ppl);

MtmErrorCode reportDay(EscapeTechnion sys);

MtmErrorCode reportBest(EscapeTechnion sys);

void resetSystem(EscapeTechnion sys){
    listDestroy(sys->escaperList);
    listDestroy(sys->orderList);
    setDestroy(sys->companies);
    free(sys);
}
