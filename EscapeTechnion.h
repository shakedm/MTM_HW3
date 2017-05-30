#ifndef HW3WET_ESCAPETECHNION_H
#define HW3WET_ESCAPETECHNION_H

#include "mtm_ex3.h"
#include "escaper.h"
#include "room.h"
#include "company.h"

typedef struct escape_technion_t* EscapeTechnion;

MtmErrorCode createEscapeTechnion(EscapeTechnion *sys);

MtmErrorCode companyAdd(EscapeTechnion sys, char* email,
                        TechnionFaculty faculty);

MtmErrorCode companyRemove(EscapeTechnion sys, char* email);

MtmErrorCode roomAdd(EscapeTechnion sys, Company company, int price,
                     int num_ppl, char* working_hrs, int difficulty);

MtmErrorCode roomRemove(EscapeTechnion sys, TechnionFaculty faculty, int id);

MtmErrorCode escaperAdd(EscapeTechnion sys, char* email,
                        TechnionFaculty faculty, int skill_level);

MtmErrorCode escaperRemove(EscapeTechnion sys, char* email);

MtmErrorCode escaperOrder(EscapeTechnion sys, char* email,
                          TechnionFaculty faculty, int id, int* time,
                          int num_ppl);

MtmErrorCode escaperRecommend(EscapeTechnion sys, char* email, int num_ppl);

MtmErrorCode reportDay();

MtmErrorCode reportBest();

MtmErrorCode resetSystem(EscapeTechnion sys);

#endif //HW3WET_ESCAPETECHNION_H
