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

Escaper createEscaper(){
    return malloc(sizeof(Escaper));
}

void destroyEscaper(void* escaper){
    if( escaper == NULL){
        return;
    }
    resetEscaper(escaper);
    free(*(Escaper*)escaper);
}

EscaperError initEscaper(Escaper visitor, const char* email, TechnionFaculty faculty,
                         int skill_level){
    assert( visitor != NULL );
    if (email == NULL){
        return ESCAPER_NULL_PARAMETER;
    }
    if (skill_level > MAX_SKILL || skill_level < MIN_SKILL || !emailCheck(email)){
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
    if((*(Escaper*)visitor)->email != NULL){
        free((*(Escaper*)visitor)->email);
        (*(Escaper*)visitor)->email = NULL;
    }
    (*(Escaper*)visitor)->faculty = UNKNOWN;
    (*(Escaper*)visitor)->skill_level = 0;
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

