#include "escaper.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
//#include "usefullFunctions.h"

struct escaper_t {
    char *email;
    TechnionFaculty faculty;
    int skill_level;
};

Escaper createEscaper(){
    Escaper new_escaper = malloc(sizeof(*new_escaper));
    return new_escaper;
}

void destroyEscaper(void* escaper){
    if( escaper == NULL){
        return;
    }
    resetEscaper(escaper);
    free(escaper);
}

EscaperError initEscaper(Escaper visitor, char* email, TechnionFaculty faculty,
                         int skill_level){
    assert( visitor != NULL );
    if (email == NULL){
        return ESCAPER_NULL_PARAMETER;
    }
    if (skill_level > MAX_SKILL || skill_level < MIN_SKILL || !emailCheck(email)
        || faculty >= UNKNOWN || faculty < (TechnionFaculty)0){
        return ESCAPER_INVALID_PARAMETER;
    }
    char* email_copy = malloc(strlen(email) + 1);
    if (!email_copy){
        return ESCAPER_OUT_OF_MEMORY;
    }
    strcpy(email_copy, email);
    visitor->email = email_copy;
    visitor->faculty = faculty;
    visitor->skill_level = skill_level;
    return ESCAPER_SUCCESS;
}

void resetEscaper(void* visitor){
    if(visitor == NULL )
        return;
    Escaper escaper = visitor;
    if(escaper->email != NULL){
        free(escaper->email);
        escaper->email = NULL;
    }
    escaper->faculty = UNKNOWN;
    escaper->skill_level = 0;
}

char* getEscaperEmail(Escaper visitor){
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
    Escaper first = visitor1;
    Escaper second = visitor2;
    return  (strcmp(first->email, second->email));
}

void* copyEscaper(void* escaper){
    if (escaper == NULL)
        return NULL;
    Escaper new_escaper = createEscaper();
    if(!new_escaper){
        return NULL;
    }
    if(initEscaper(new_escaper,getEscaperEmail(escaper),
                getEscaperFaculty(escaper), getEscaperSkillLevel(escaper))
            != ESCAPER_SUCCESS)
        return NULL;
    return new_escaper;
}

