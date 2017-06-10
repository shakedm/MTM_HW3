#ifndef HW3WET_ESCAPETECHNION_H
#define HW3WET_ESCAPETECHNION_H

#include "mtm_ex3.h"
#include "escaper.h"
#include "room.h"
#include "company.h"
#include "usefullFunctions.h"
#include "order.h"

#define SMALLER 1
#define EQUAL 2
#define BIGGER 3
#define TODAY 0
#define TOP 3

/* type to define the EscapeTechnion struct*/
typedef struct escape_technion_t* EscapeTechnion;

/*!
 * This function create a new ecape system
 * @param sys - return parameter points to the new system.
 * @return
 */
MtmErrorCode createEscapeTechnion(EscapeTechnion *sys);

MtmErrorCode companyAdd(EscapeTechnion sys, char* email,
                        TechnionFaculty faculty);

MtmErrorCode companyRemove(EscapeTechnion sys, char* email);

MtmErrorCode roomAdd(EscapeTechnion sys, char* email, int id, int price,
                     int num_ppl, char* working_hrs, int difficulty);

MtmErrorCode roomRemove(EscapeTechnion sys, TechnionFaculty faculty, int id);

MtmErrorCode escaperAdd(EscapeTechnion sys, char* email,
                        TechnionFaculty faculty, int skill_level);

MtmErrorCode escaperRemove(EscapeTechnion sys, char* email);

MtmErrorCode escaperOrder(EscapeTechnion sys, char* email,
                          TechnionFaculty faculty, int id, char* time,
                          int num_ppl);

MtmErrorCode escaperOrderAux(EscapeTechnion sys, char* email,
                             TechnionFaculty faculty, int id,
                             int due_in[HOURS_FORMAT], int num_ppl);

MtmErrorCode escaperRecommend(EscapeTechnion sys, char* email, int num_ppl);

MtmErrorCode searchRecommended(EscapeTechnion sys, int num_ppl,
                               Room *recommended_room, Escaper visitor);

MtmErrorCode reportDay(EscapeTechnion sys, FILE* outputChannel);

MtmErrorCode reportBest(EscapeTechnion sys, FILE* outputChannel);

MtmErrorCode isGoodOrder(bool* discount, EscapeTechnion sys, char* email,
                         TechnionFaculty faculty, int id,
                         int due_in[HOURS_FORMAT], Room *room, Company *company);

MtmErrorCode isRoomAvailable(EscapeTechnion sys, TechnionFaculty faculty, int id,
                             int due_in[HOURS_FORMAT], Room *room,
                             Company *company);

MtmErrorCode isClientAvailable(EscapeTechnion sys, Escaper visitor,
                               int due_in[HOURS_FORMAT]);

Company findCompanyByEmail(Set companies, const char *email);

void endDayProtocol(EscapeTechnion sys);

Company findCompanyByFaculty(Set companies, TechnionFaculty faculty);

Escaper findEscaperInSet(Set escapers, char *email);

MtmErrorCode getTodayList(EscapeTechnion sys, List* list);

bool orderExistForRoom(List orders, int room_id);

void resetSystem(EscapeTechnion sys);

#endif //HW3WET_ESCAPETECHNION_H
