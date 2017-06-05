#include "escaper.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "usefullFunctions.h"

struct escaper_t {
    char *email;
    TechnionFaculty faculty;
    int skill_level;
};


MtmErrorCode initEscaper(Escaper *visitor, char* email, TechnionFaculty faculty,
                         int skill_level){
    assert( visitor != NULL );
    if (email == NULL){
        return MTM_NULL_PARAMETER;
    }
    if (skill_level > MAX_SKILL || skill_level < MIN_SKILL || !emailCheck(email)){
        return MTM_INVALID_PARAMETER;
    }
    Escaper new_escaper = malloc(sizeof(Escaper));
    if (!new_escaper){
        return MTM_OUT_OF_MEMORY;
    }
    *visitor = new_escaper;
    char* email_copy = malloc(strlen(email) + 1);
    if (!email_copy){
        free(new_escaper);
        return MTM_OUT_OF_MEMORY;
    }
    strcpy(email_copy, email);
    (*visitor)->email = email_copy;
    (*visitor)->faculty = faculty;
    (*visitor)->skill_level = skill_level;
    return MTM_SUCCESS;
}

void resetEscaper(Escaper visitor){
    if(visitor == NULL )
        return;
    free(visitor->email);
    visitor->faculty = UNKNOWN;
    visitor->skill_level = 0;
    free(visitor);
}

MtmErrorCode getEscaperEmail(Escaper visitor, char** email){
    assert(visitor != NULL);
    *email = visitor->email;
    return MTM_SUCCESS;
}

MtmErrorCode getEscaperFaculty(Escaper visitor, TechnionFaculty* faculty){
    assert(visitor != NULL);
    *faculty = visitor->faculty;
    return MTM_SUCCESS;
}

int getEscaperSkillLevel(Escaper visitor){
    assert(visitor != NULL);
    return visitor->skill_level;
}
bool compareEscaper(Escaper visitor1, Escaper visitor2){
    if (visitor1 == NULL || visitor2 == NULL)
        return false;
    return  !(strcmp(visitor1->email, visitor2->email));
}