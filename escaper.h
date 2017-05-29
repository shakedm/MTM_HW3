#include "mtm_ex3.h"
#ifndef HW3WET_ESCAPER_H
#define HW3WET_ESCAPER_H



typedef struct escaper_t* Escaper;

MtmErrorCode initEscaper(Escaper visitor, char* email, TechnionFaculty faculty,
                            int skill_level);

MtmErrorCode resetEscaper(Escaper visitor);

MtmErrorCode getEscaperEmail(Escaper visitor, char** email);

MtmErrorCode getEscaperFaculty(Escaper visitor, TechnionFaculty* faculty);

MtmErrorCode getEscaperSkillLevel(Escaper visitor, int* skill_level);


#endif //HW3WET_ESCAPER_H
