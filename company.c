#include "company.h"

//#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
//#include "usefullFunctions.h"


struct company_t {
    char *email;
    TechnionFaculty faculty;
    Set rooms;
    int revenue;
};

/*!
 * This function translate the general error the ADT specific error
 * @param result - the general error code
 * @return the specific error code
 */
static CompanyError setErrorHandel(SetResult result, Room room);

Company createCompany(){
    Company new_company = malloc(sizeof(*new_company));
    return new_company;
}

void destroyCompany(void* company){
    if(company == NULL){
        return;
    }
    resetCompany(company);
    free(company);
}

CompanyError initCompany(Company company, char* email, TechnionFaculty faculty){
    if(company == NULL){
        return COMPANY_NULL_ARGUMENT;
    }
    if (email == NULL){
        return COMPANY_NULL_ARGUMENT;
    }
    if (!(emailCheck(email)) || faculty >= UNKNOWN ||
            faculty < (TechnionFaculty)0){
        return COMPANY_INVALID_ARGUMENT;
    }
    char* email_copy = malloc(strlen(email) + 1);
    if (!email_copy){
        free(company);
        return COMPANY_OUT_OF_MEMORY;
    }
    strcpy(email_copy, email);
    Set rooms = setCreate(copyRoom, destroyRoom, compareRoom);
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

void resetCompany(Company company){
    if(company == NULL)
        return;
    if (company->email != NULL){
        free(((Company)company)->email);
        ((Company)company)->email = NULL;
    }
    company->revenue = 0;
    setClear(company->rooms);
    setDestroy(company->rooms);
    company->rooms = NULL;
    company->faculty = UNKNOWN;
}

TechnionFaculty getCompanyFaculty(Company company){
    return company->faculty;
}

int getCompanyRevenue(Company company){
    return company->revenue;
}

CompanyError addRoomCompany(Company company, Room room){
    if(company == NULL){
        return COMPANY_NULL_ARGUMENT;
    }
    Room check = findRoomInCompany(company, roomGetId(room));
    if(check){
        return COMPANY_ID_ALREADY_EXIST;
    }
    SetResult result = setAdd(company->rooms, (void*)room);
    if(result != SET_SUCCESS){
        return setErrorHandel(result, room);
    }
    return COMPANY_SUCCESS;
}

CompanyError removeRoomCompany(Company company, Room room){
    assert(company != NULL);
    SetResult result = setRemove(company->rooms, room);
    if(result != SET_SUCCESS){
        return setErrorHandel(result, room);
    }
    return COMPANY_SUCCESS;
}

char* getCompanyEmail(Company company){
    return company->email;
}

int compareCompany(void* company1, void* company2){
    return strcmp(getCompanyEmail(((Company)company1)),
                  getCompanyEmail(((Company)company2)));
}

void* copyCompany(void* company){
    assert(company != NULL);
    Company new_company = createCompany();
    if(!new_company){
        return NULL;
    }
    CompanyError result = initCompany(new_company,
                                      getCompanyEmail((Company)company),
                                      getCompanyFaculty(((Company)company)));
    if (result != COMPANY_SUCCESS){
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

Set getCompanyRooms(Company company){
    if(company == NULL){
        return NULL;
    }
    return company->rooms;
}

void addCompanyRevenue(Company company, int revenue){
    assert(company != NULL);
    company->revenue += revenue;
}


static CompanyError setErrorHandel(SetResult result, Room room){
    switch (result){
        case SET_OUT_OF_MEMORY :
            resetRoom((void*)room);
            return COMPANY_OUT_OF_MEMORY;
        case SET_NULL_ARGUMENT:
            return COMPANY_NULL_ARGUMENT;
        case SET_ITEM_ALREADY_EXISTS:
            return COMPANY_ID_ALREADY_EXIST;
        case SET_ITEM_DOES_NOT_EXIST:
            return COMPANY_ID_DOES_NOT_EXIST;
        default:
            return COMPANY_INVALID_ARGUMENT;
    }
}