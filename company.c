#include "company.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "usefullFunctions.h"


struct company_t {
    char *email;
    TechnionFaculty faculty;
    Set rooms;
    int revenue;
};


CompanyError initCompany(Company company, char* email, TechnionFaculty faculty){
    assert(company != NULL);
    if (email == NULL){
        return COMPANY_NULL_ARGUMENT;
    }
    if (!(emailCheck(email))){
        return COMPANY_INVALID_ARGUMENT;
    }
    char* email_copy = malloc(strlen(email) + 1);
    if (!email_copy){
        free(company);
        return COMPANY_OUT_OF_MEMORY;
    }
    strcpy(email_copy, email);
    Set rooms = setCreate(copyRoom, resetRoom, compareRoom);
    if (!rooms){
        free(email_copy);
        return COMPANY_OUT_OF_MEMORY;
    }
    company->email = email_copy;
    company->faculty = faculty;
    company->rooms = rooms;
    company->revenue = 0;
    return COMPANY_SUCCESS;
}

void resetCompany(void* company){
    assert(company != NULL);
    free((*(Company*)company)->email);
    (*(Company*)company)->revenue = 0;
    setDestroy((*(Company*)company)->rooms);
    (*(Company*)company)->faculty = UNKNOWN;
}

TechnionFaculty getCompanyFaculty(Company company){
    return company->faculty;
}

int getCompanyRevenue(Company company){
    return company->revenue;
}

CompanyError addRoomCompany(Company company, Room room){
    assert(company != NULL);
    SetResult result = setAdd(company->rooms, (void*)room);
    if(result != SET_SUCCESS){
        return errorHandel(HANDEL_SET, (void*)result, ROOM, (void*)room);
    }
    return COMPANY_SUCCESS;
}

CompanyError removeRoomCompany(Company company, Room room){
    assert(company != NULL);
    SetResult result = setRemove(company->rooms, room);
    if(result != SET_SUCCESS){
        return errorHandel(HANDEL_SET, (void*)result, ROOM, (void*)room);
    }
    return COMPANY_SUCCESS;
}

const char* getCompanyEmail(Company company){
    return company->email;
}

int compareCompany(void* company1, void* company2){
    return strcmp(getCompanyEmail((*(Company*)company1)),
                  getCompanyEmail((*(Company*)company2)));
}

void* copyCompany(void* company){
    assert(company != NULL);
    Company *new_company;
    MtmErrorCode result = initCompany(new_company,
                                      getCompanyEmail((*(Company*)company),
                                      getCompanyFaculty((*(Company*)company));
    if (result != MTM_SUCCESS){
        return NULL;
    }
    return new_company;
}

Room findRoomInCompany(Company company, int Id){
    int set_size = setGetSize(company->rooms);
    bool found = false;
    Room curr_room = setGetFirst(company->rooms);
    for (int i = 0; i < set_size ; ++i) {
        if(roomGetId(curr_room) == Id){
            found = true;
            break;
        }
        curr_room = setGetNext(company->rooms);
    }
    if(found){
        return curr_room;
    }
    return NULL;
}
