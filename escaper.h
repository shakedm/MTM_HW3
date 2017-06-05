#include "mtm_ex3.h"
#ifndef HW3WET_ESCAPER_H
#define HW3WET_ESCAPER_H

#include <stdbool.h>

typedef struct escaper_t* Escaper;

MtmErrorCode initEscaper(Escaper *visitor, char* email, TechnionFaculty faculty,
                            int skill_level);

void resetEscaper(void* visitor);

char* getEscaperEmail(Escaper visitor);

TechnionFaculty getEscaperFaculty(Escaper visitor);

int getEscaperSkillLevel(Escaper visitor);

bool compareEscaper(Escaper visitor1, Escaper visitor2);


#endif //HW3WET_ESCAPER_H
