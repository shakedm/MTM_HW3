#include "company.h"
#include "set.h"
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


MtmErrorCode initCompany(Company *company, char* email, TechnionFaculty faculty){
    assert(company != NULL);
    if (email == NULL){
        return MTM_NULL_PARAMETER;
    }
    if (!(emailCheck(email))){
        return MTM_INVALID_PARAMETER;
    }
    Company new_company = malloc(sizeof(Company));
    if(!new_company){
        return MTM_OUT_OF_MEMORY;
    }
    *company = new_company;
    char* email_copy = malloc(strlen(email) + 1);
    if (!email_copy){
        free(company);
        return MTM_OUT_OF_MEMORY;
    }
    strcpy(email_copy, email);
    Set rooms = setCreate(copyRoom, resetRoom, compareRoom);
    if (!rooms){
        free(email_copy);
        return MTM_OUT_OF_MEMORY;
    }
    (*company)->email = email_copy;
    (*company)->faculty = faculty;
    (*company)->rooms = rooms;
    (*company)->revenue = 0;
    return MTM_SUCCESS;
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

MtmErrorCode addRoomCompany(Company company, Room room){
    assert(company != NULL);
    SetResult result = setAdd(company->rooms, (void*)room);
    if(result != SET_SUCCESS){
        return errorHandel(HANDEL_SET, (void*)result, COMPANY, (void*)company);
    }
    return MTM_SUCCESS;
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