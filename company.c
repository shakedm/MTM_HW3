#include "company.h"
#include "set.h"

struct company_t {
    char *email;
    TechnionFaculty faculty;
    Set rooms;
    int revenue;
};


MtmErrorCode initCompany(Company company, char* email, TechnionFaculty faculty);

MtmErrorCode resetCompany(Company company);

MtmErrorCode getCompanyFaculty(Company company, TechnionFaculty* faculty);

MtmErrorCode getCompanyRevenue(Company company, int* revenue);

MtmErrorCode addRoomCompany(Company company, Room* room);