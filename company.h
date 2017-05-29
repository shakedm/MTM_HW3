#ifndef HW3WET_COMPANY_H
#define HW3WET_COMPANY_H

#include "room.h"
#include "mtm_ex3.h"

typedef struct company_t* Company;

MtmErrorCode initCompany(Company company, char* email, TechnionFaculty faculty);
MtmErrorCode resetCompany(Company company);
MtmErrorCode getCompanyFaculty(Company company, TechnionFaculty* faculty);
MtmErrorCode getCompanyRevenue(Company company, int* revenue);
MtmErrorCode addRoomCompany(Company company, Room* room);


#endif //HW3WET_COMPANY_H
