#include "escaper.h"

struct company_t {
    char *email;
    TechnionFaculty faculty;
    int skill_level;
};


MtmErrorCode initEscaper(Escaper visitor, char* email, TechnionFaculty faculty,
                         int skill_level);

MtmErrorCode resetEscaper(Escaper visitor);

MtmErrorCode getEscaperEmail(Escaper visitor, char** email);

MtmErrorCode getEscaperFaculty(Escaper visitor, TechnionFaculty* faculty);

MtmErrorCode getEscaperSkillLevel(Escaper visitor, int* skill_level);
