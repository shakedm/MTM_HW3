#include "mtm_ex3.h"


#ifndef HW3WET_COMPANY_H
#define HW3WET_COMPANY_H

#include "room.h"

typedef struct company_t* Company;

MtmErrorCode initCompany(Company company, char* email, TechnionFaculty faculty);

void resetCompany(void* company);

TechnionFaculty getCompanyFaculty(Company company);

int getCompanyRevenue(Company company);

MtmErrorCode addRoomCompany(Company company, Room room);

int compareCompany(void* company1, void* company2);

void* copyCompany(void* company);

char* getCompanyEmail(Company company);

#endif //HW3WET_COMPANY_H
