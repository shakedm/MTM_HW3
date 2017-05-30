#include "company.h"
#include "set.h"
#include "room.h"
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


MtmErrorCode initCompany(Company company, char* email, TechnionFaculty faculty){
    assert(company != NULL);
    if (email == NULL){
        return MTM_NULL_PARAMETER;
    }
    if (!(emailCheck(email))){
        return MTM_INVALID_PARAMETER;
    }
    char* email_copy = malloc(strlen(email) + 1);
    if (!email_copy){
        return MTM_OUT_OF_MEMORY;
    }
    strcpy(email_copy, email);
    Set rooms = setCreate(copyRoom, resetRoom, compareRoom);
    if (!rooms){
        free(email_copy);
        return MTM_OUT_OF_MEMORY;
    }
    company->email = email_copy;
    company->faculty = faculty;
    company->rooms = rooms;
    company->revenue = 0;
    return MTM_SUCCESS;
}

void resetCompany(void* company);

MtmErrorCode getCompanyFaculty(Company company, TechnionFaculty* faculty);

MtmErrorCode getCompanyRevenue(Company company, int* revenue);

MtmErrorCode addRoomCompany(Company company, Room* room);