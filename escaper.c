#include "escaper.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "usefullFunctions.h"

#define GOOD_AMOUNT 1



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

MtmErrorCode resetEscaper(Escaper visitor){
    assert(visitor != NULL);
    free(visitor->email);
    visitor->faculty = UNKNOWN;
    visitor->skill_level = 0;
    return MTM_SUCCESS;
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

MtmErrorCode getEscaperSkillLevel(Escaper visitor, int* skill_level){
    assert(visitor != NULL);
    *skill_level = visitor->skill_level;
    return MTM_SUCCESS;
}
