#include "company.h"
#include "set.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define GOOD_AMOUNT 1
#define FAKE_ID -1

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
    int counter = 0;
    int index = 0;
    while (email[index] != '/0'){
        if(email[index] == '@'){
            counter++;
        }
        index++;
    }
    if (counter != GOOD_AMOUNT ){
        return MTM_INVALID_PARAMETER;
    }
    char* email_copy = malloc(strlen(email) + 1);
    if (!email_copy){
        return MTM_OUT_OF_MEMORY;
    }
    Set rooms = setCreate()
    strcpy(email_copy, email);
    company->email = email_copy;
    company->faculty = faculty;

}

MtmErrorCode resetCompany(Company company);

MtmErrorCode getCompanyFaculty(Company company, TechnionFaculty* faculty);

MtmErrorCode getCompanyRevenue(Company company, int* revenue);

MtmErrorCode addRoomCompany(Company company, Room* room);