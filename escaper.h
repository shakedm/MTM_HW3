#include "mtm_ex3.h"
#ifndef HW3WET_ESCAPER_H
#define HW3WET_ESCAPER_H



typedef struct escaper_t* Escaper;

MtmErrorCode initEscaper(Escaper *visitor, char* email, TechnionFaculty faculty,
                            int skill_level);

void resetEscaper(Escaper visitor);

MtmErrorCode getEscaperEmail(Escaper visitor, char** email);

MtmErrorCode getEscaperFaculty(Escaper visitor, TechnionFaculty* faculty);

MtmErrorCode getEscaperSkillLevel(Escaper visitor, int* skill_level);

int compareEscaper(Escaper visitor1, Escaper visitor2);


#endif //HW3WET_ESCAPER_H
