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

void resetEscaper(void* visitor){
    if(visitor == NULL )
        return;
    free((*(Escaper*)visitor)->email);
    (*(Escaper*)visitor)->faculty = UNKNOWN;
    (*(Escaper*)visitor)->skill_level = 0;
    free(visitor);
}

const char* getEscaperEmail(Escaper visitor){
    assert(visitor != NULL);
    return visitor->email;
}

TechnionFaculty getEscaperFaculty(Escaper visitor){
    assert(visitor != NULL);
    return visitor->faculty;
}

int getEscaperSkillLevel(Escaper visitor){
    assert(visitor != NULL);
    return visitor->skill_level;
}
int compareEscaper(void* visitor1, void* visitor2){
    if (visitor1 == NULL || visitor2 == NULL)
        return false;
    return  (strcmp((*(Escaper*)visitor1)->email, (*(Escaper*)visitor2)->email));
}

void* copyEscaper(void* escaper){
    if (escaper == NULL)
        return NULL;
    Escaper* new_escaper = NULL;
    if(initEscaper(new_escaper,((Escaper)escaper)->email,
                ((Escaper)escaper)->faculty, ((Escaper)escaper)->skill_level)
            != MTM_SUCCESS)
        return NULL;
    return new_escaper;
}

