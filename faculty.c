#include "faculty.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct faculty_t {
    TechnionFaculty faculty_ID;
    Set rooms;
    Set companies;
    int revenue;
};

/* * This Function handels cases in which a set action fails according to the
 * error masseges
 * @param result the error result the action returned
 * @param sender_ID signefies the ADT from which the action was taken.
 * @param ADT points to the ADT to handel
 * @return the correct error massege after handeling the fault.
 */
static FacultyError setErrorHandel(SetResult result, int sender_ID,
                                          void* ADT);

/* * This Function handels a memory fault in allocation. frees all priviously
 * allocated space
 * @param sender_ID to ID the ADT to handel
 * @param ADT points to the ADT to free
 * @return MTM_OUT_OF_MEMORY after freeing
 */
static FacultyError memoryFaultHandel(int sender_ID, void* ADT);


Faculty createFaculty(){
    return malloc(sizeof(Faculty));
}

void destroyFaculty(void* faculty){
    if(faculty == NULL){
        return;
    }
    resetFaculty(faculty);
    free(faculty);
}


FacultyError initFaculty(Faculty faculty, TechnionFaculty faculty_ID){
    if(!faculty ){
        return FACULTY_INVALID_PARAMETER;
    }
    if (faculty_ID == UNKNOWN){
        return FACULTY_INVALID_PARAMETER;
    }
    faculty = createFaculty();
    if(faculty == NULL){
        return FACULTY_OUT_OF_MEMORY;
    }
    Set rooms = setCreate(copyRoom, destroyRoom, compareRoom);
    if (!rooms){
        free(faculty);
        return FACULTY_OUT_OF_MEMORY;
    }
    Set companies = setCreate(copyCompany, destroyCompany, compareCompany);
    if (!companies){
        setClear(rooms);
        setDestroy(rooms);
        free(faculty);
        return FACULTY_OUT_OF_MEMORY;
    }
    faculty->companies = companies;
    faculty->rooms = rooms;
    faculty->faculty_ID = faculty_ID;
    faculty->revenue = 0;
    return FACULTY_SUCCESS;
}


void resetFaculty(void* faculty){
    if(faculty == NULL){
        return;
    }
    setClear(((Faculty)faculty)->rooms);
    setDestroy(((Faculty)faculty)->rooms);
    setClear(((Faculty)faculty)->companies);
    setDestroy(((Faculty)faculty)->companies);
    ((Faculty)faculty)->companies = NULL;
    ((Faculty)faculty)->rooms = NULL;
}


Room findRoomInFaculty(Faculty faculty, int id){
    int set_size = setGetSize(faculty->rooms);
    bool found = false;
    Room *curr_room = setGetFirst(faculty->rooms);
    for (int i = 0; i < set_size ; ++i) {
        if(roomGetId(*curr_room) == id){
            found = true;
            break;
        }
        curr_room = setGetNext(faculty->rooms);
    }
    if(found){
        return *curr_room;
    }
    return NULL;
}


Company findCompanyInFaculty(Faculty faculty, char* email){
    int set_size = setGetSize(faculty->companies);
    Company *curr_company = setGetFirst(faculty->companies);
    bool found = false;
    for (int i = 0; i < set_size ; ++i) {
        if(strcmp(getCompanyEmail(*curr_company), email) == 0){
            found = true;
            break;
        }
        *curr_company = setGetNext(faculty->companies);
    }
    if(found){
        return *curr_company;
    }
    return NULL;
}


FacultyError addFacultyCompany(Faculty faculty, Company company){
    assert(faculty != NULL);
    SetResult result = setAdd(faculty->companies, (void*)company);
    if(result != SET_SUCCESS){
        return setErrorHandel(result, COMPANY, company);
    }
    return FACULTY_SUCCESS;
}

FacultyError removeFacultyCompany(Faculty faculty, Company company){
    if(faculty == NULL || company == NULL){
        return FACULTY_NULL_PARAMETER;
    }
    SetResult result = setRemove(faculty->companies, company);
    if (result != SET_SUCCESS){
        return setErrorHandel(result, COMPANY, company);
    }
    return FACULTY_SUCCESS;
}

FacultyError addFacultyRoom(Faculty faculty, Room room){
    assert(faculty != NULL);
    SetResult result = setAdd(faculty->rooms, (void*)room);
    if(result != SET_SUCCESS){
        return setErrorHandel(result, ROOM, room);
    }
    return FACULTY_SUCCESS;
}

FacultyError removeFacultyRoom(Faculty faculty, Room room){
    if(faculty == NULL || room == NULL){
        return FACULTY_NULL_PARAMETER;
    }
    SetResult result = setRemove(faculty->rooms, room);
    if (result != SET_SUCCESS){
        return setErrorHandel(result, ROOM, room);
    }
    return FACULTY_SUCCESS;
}

int compareFaculty(void* faculty1, void* faculty2){
    return ((((Faculty)faculty1)->faculty_ID) -
            (((Faculty)faculty2)->faculty_ID));
}

void* copyFaculty(void* faculty){
    if (faculty == NULL){
        return NULL;
    }
    Faculty faculty_copy = createFaculty();
    if(!faculty_copy){
        return NULL;
    }
    FacultyError result = initFaculty(faculty_copy,
                                      ((Faculty)faculty)->faculty_ID);
    if(result != FACULTY_SUCCESS){
        free(faculty_copy);
        return NULL;
    }
    faculty_copy->rooms = setCopy(((Faculty)faculty)->rooms);
    if (faculty_copy->rooms == NULL){
        destroyFaculty(faculty_copy);
        return NULL;
    }
    faculty_copy->companies = setCopy(((Faculty)faculty)->companies);
    if(faculty_copy->companies){
        setClear(faculty_copy->rooms);
        setDestroy(faculty_copy->rooms);
        destroyFaculty(faculty_copy);
        return NULL;
    }
    faculty_copy->revenue = ((Faculty)faculty)->revenue;
    return faculty_copy;
}

void collectRevenue(Faculty faculty){
    assert(faculty != NULL);
    SET_FOREACH(Company*, curr_copmany, faculty->companies){
        faculty->revenue += getCompanyRevenue(*curr_copmany);
    }
}

TechnionFaculty getFacultyID (Faculty faculty){
    if(!faculty){
        return UNKNOWN;
    }
    return faculty->faculty_ID;
}

int getFacultyRevenue (Faculty faculty){
    if(!faculty){
        return -1;
    }
    return faculty->revenue;
}

static FacultyError setErrorHandel(SetResult result, int sender_ID,
                                          void* ADT){
    switch (result){
        case SET_OUT_OF_MEMORY :
            return memoryFaultHandel(sender_ID, ADT);
        case SET_NULL_ARGUMENT:
            return FACULTY_NULL_PARAMETER;
        case SET_ITEM_ALREADY_EXISTS:
            switch (sender_ID){
                case COMPANY:
                    return FACULTY_EMAIL_ALREADY_EXISTS;
                case ROOM:
                    return FACULTY_ID_ALREADY_EXIST;
                default:
                    return FACULTY_INVALID_PARAMETER;
            }
        case SET_ITEM_DOES_NOT_EXIST:
            switch (sender_ID){
                case COMPANY:
                    return FACULTY_COMPANY_EMAIL_DOES_NOT_EXIST;
                case ROOM:
                    return FACULTY_ID_DOES_NOT_EXIST;
                default:
                    return FACULTY_INVALID_PARAMETER;
            }
        default:
            return FACULTY_INVALID_PARAMETER;
    }
}

static FacultyError memoryFaultHandel(int sender_ID, void* ADT){
    switch (sender_ID){
        case ROOM:
            destroyRoom(ADT);
            break;
        case COMPANY:
            destroyCompany(ADT);
            break;
        default:
            return FACULTY_OUT_OF_MEMORY;
    }
    return FACULTY_OUT_OF_MEMORY;
}