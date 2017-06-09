#include "EscapeTechnion.h"


struct escape_technion_t {
    Set companies;
    Set escapers;
    List orderList;
    int time_log; // counts days
};

/*!
 * This function caculate the recomand score for a specific room
 * @param room - points to a room ADT
 * @param visitor - points to a Escaper ADT
 * @param num_ppl - the amount of people that requier the room
 * @return the caclculated score.
 */
static int score_calc(Room room, Escaper visitor, int num_ppl);

/*!
 * This function compare the difference between the visitor's Faculty and two
 * given room.
 * @param sys - the system in which to reace the second room
 * @param company - the first room's company
 * @param room - the second room
 * @param visitor - the Escaper's ADT
 * @return SMALLER - if the diffreance between the first room's faculty is
 *                  smaller than the second room's faculty
 *          EQUAL - if the diffrence is equal
 *          BIGGER - if the diffreance between the second room's faculty is
 *                  smaller than the first room's faculty
 */
static int compareFaculties(EscapeTechnion sys, Company company, Room room,
                            Escaper visitor);

/*!
 * This function chaecks if the best score for a room reservation needs to be
 * updated, and if so, updates it.
 */
static void update(EscapeTechnion sys, Company company, Room room,
                   Room *recommanded_room, Escaper visitor, int num_ppl,
                   int *best_score);

MtmErrorCode createEscapeTechnion(EscapeTechnion *sys){
    EscapeTechnion new_system = malloc(sizeof(EscapeTechnion));
    if(!new_system ){
        return MTM_OUT_OF_MEMORY;
    }
    new_system->companies = setCreate(copyCompany, destroyCompany,
                                      compareCompany);
    if(new_system->companies == NULL){
        free(new_system);
        return MTM_OUT_OF_MEMORY;
    }
    new_system->escapers = setCreate(copyEscaper, destroyEscaper,
                                     compareEscaper);
    if(new_system->escapers == NULL){
        setDestroy(new_system->companies);
        free(new_system);
        return MTM_OUT_OF_MEMORY;
    }
    new_system->orderList = listCreate(copyOrder, destroyOrder);
    if(new_system->orderList == NULL){
        setDestroy(new_system->escapers);
        setDestroy(new_system->companies);
        free(new_system);
        return MTM_OUT_OF_MEMORY;
    }
    new_system->time_log = 0;
    *sys = new_system;
    return MTM_SUCCESS;
}

MtmErrorCode companyAdd(EscapeTechnion sys, char* email,
                        TechnionFaculty faculty){
    Company new_company = createCompany();
    if(!new_company){
        return MTM_OUT_OF_MEMORY;
    }
    CompanyError result = initCompany(new_company, email, faculty);
    if(result != COMPANY_SUCCESS){
        return errorHandel(HANDEL_COMPANY, (void*)result, COMPANY, new_company);
    }
    SetResult setResult = setAdd(sys->companies, (void*)new_company);
    if(setResult != SET_SUCCESS){
        return errorHandel(HANDEL_SET, (void*)setResult, COMPANY, new_company);
    }
    return MTM_SUCCESS;
}

Company findCompanyByEmail(Set companies, const char *email){
    int set_size = setGetSize(companies);
    Company curr_company = setGetFirst(companies);
    bool found = false;
    for (int i = 0; i < set_size ; ++i) {
        if(strcmp(getCompanyEmail(curr_company), email) == 0){
            found = true;
            break;
        }
        curr_company = setGetNext(companies);
    }
    if(found){
        return curr_company;
    }
    return NULL;
}

Company findCompanyByFaculty(Set companies, TechnionFaculty faculty){
    int set_size = setGetSize(companies);
    Company curr_company = setGetFirst(companies);
    bool found = false;
    for (int i = 0; i < set_size ; ++i) {
        if(getCompanyFaculty(curr_company) == faculty){
            found = true;
            break;
        }
        curr_company = setGetNext(companies);
    }
    if(found){
        return curr_company;
    }
    return NULL;
}

Escaper findEscaperInSet(Set escapers, char *email){
    int set_size = setGetSize(escapers);
    Escaper curr_escaper = setGetFirst(escapers);
    bool found = false;
    for (int i = 0; i < set_size ; ++i) {
        if(strcmp(getEscaperEmail(curr_escaper), email) == 0){
            found = true;
            break;
        }
        curr_escaper = setGetNext(escapers);
    }
    if(found){
        return curr_escaper;
    }
    return NULL;
}


MtmErrorCode companyRemove(EscapeTechnion sys, char* email){
    Company company = findCompanyByEmail(sys->companies, email);
    if(company != NULL){
        setRemove(sys->companies, company);
        return MTM_SUCCESS;
    }
    return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
}

MtmErrorCode roomAdd(EscapeTechnion sys, char* email, int id, int price,
                     int num_ppl, char* working_hrs, int difficulty){
    Company company = findCompanyByEmail(sys->companies, email);
    if(company == NULL){
        return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
    }
    Room new_room = createRoom();
    RoomError result = initRoom(new_room, getCompanyEmail(company), id,
                                   num_ppl, working_hrs, difficulty, price);
    if(result != ROOM_SUCCESS){
        return errorHandel(HANDEL_ROOM, (void*)result, ROOM, new_room);
    }
    CompanyError company_result = addRoomCompany(company, new_room);
    if(company_result != COMPANY_SUCCESS){
        return errorHandel(HANDEL_COMPANY, (void*)company_result,
                           ESCAPE_TECHNION, sys);
    }
    return MTM_SUCCESS;
}

MtmErrorCode roomRemove(EscapeTechnion sys, TechnionFaculty faculty, int id){
    Company company = findCompanyByFaculty(sys->companies, faculty);
    if(company == NULL){
        return MTM_INVALID_PARAMETER;
    }
    Room room = findRoomInCompany(company, id);
    if(room == NULL){
        return MTM_ID_DOES_NOT_EXIST;
    }
    if(orderExistForRoom(sys->orderList, roomGetId(room))){
        return MTM_RESERVATION_EXISTS;
    }
    CompanyError result =  removeRoomCompany(company, room);
    if(result != COMPANY_SUCCESS){
        return errorHandel(HANDEL_COMPANY, (void*)result, ESCAPE_TECHNION, sys);
    }
    return MTM_SUCCESS;
}

MtmErrorCode escaperAdd(EscapeTechnion sys, char* email,
                        TechnionFaculty faculty, int skill_level){
    Escaper visitor = createEscaper();
    if (!visitor){
        return MTM_OUT_OF_MEMORY;
    }
    EscaperError result = initEscaper(visitor, email, faculty, skill_level);
    if (result != ESCAPER_SUCCESS){
        return errorHandel(HANDEL_ESCAPER, (void*)result, ESCAPER, visitor);
    }
    if(setIsIn(sys->escapers, visitor)){
        destroyEscaper(visitor);
        return MTM_EMAIL_ALREADY_EXISTS;
    }
    SetResult setResult = setAdd(sys->escapers, visitor);
    if(setResult != SET_SUCCESS){
        return errorHandel(HANDEL_SET, (void*)setResult, ESCAPER, visitor);
    }
    return MTM_SUCCESS;
}

MtmErrorCode escaperRemove(EscapeTechnion sys, char* email){
    Escaper visitor = findEscaperInSet(sys->escapers, email);
    if(visitor == NULL){
        return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
    }
    setRemove(sys->escapers, visitor);
    return MTM_SUCCESS;
}

MtmErrorCode escaperOrder(EscapeTechnion sys, char* email,
                          TechnionFaculty faculty, int id, char* time,
                          int num_ppl) {
    int due_in[HOURS_FORMAT];
    bool good_time = translateHours(time, due_in, true);
    if (!good_time) {
        return MTM_INVALID_PARAMETER;
    }
    return escaperOrderAux(sys, email, faculty, id, due_in, num_ppl);
}

MtmErrorCode escaperOrderAux(EscapeTechnion sys, char* email,
                             TechnionFaculty faculty, int id,
                             int due_in[HOURS_FORMAT], int num_ppl){
    Order new_order = createOrder();
    if (!new_order) {
        return MTM_OUT_OF_MEMORY;
    }
    Room *order_room = NULL;
    Company *order_company = NULL;
    bool discount = false;
    MtmErrorCode result = isGoodOrder(&discount, sys, email, faculty, id, due_in,
                                      order_room, order_company);
    if(result != MTM_SUCCESS){
        destroyOrder(new_order);
        return result;
    }
    assert(order_company != NULL && order_room != NULL);
    OrderError order_result = initOrder(new_order, id,
                                        getCompanyEmail(*order_company),
                                        email, due_in, num_ppl,
                                        roomGetPrice(*order_room), faculty);
    if (order_result != ORDER_SUCCESS) {
        return errorHandel(HANDEL_ORDER, (void *) order_result, ORDER,
                           new_order);
    }
    order_result = setDiscountOrder(new_order);
    if (order_result != ORDER_SUCCESS) {
        return errorHandel(HANDEL_ORDER, (void *) order_result, ORDER,
                           new_order);
    }
    ListResult list_result = listInsertLast(sys->orderList, new_order);
    if (list_result != LIST_SUCCESS) {
        return errorHandel(HANDEL_LIST, (void *) list_result, ESCAPE_TECHNION,
                           sys->orderList);
    }
    return MTM_SUCCESS;
}

MtmErrorCode isGoodOrder(bool* discount, EscapeTechnion sys, char* email,
                         TechnionFaculty faculty, int id,
                         int due_in[HOURS_FORMAT], Room *room, Company *company){
    Escaper visitor = findEscaperInSet(sys->escapers, email);
    if (visitor == NULL) {
        return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
    }
    *discount = false;
    if (faculty == getEscaperFaculty(visitor)) {
        *discount = true;
    }
    MtmErrorCode room_result = isRoomAvailable(sys, faculty, id, due_in, room,
                                               company);
    if(room_result != MTM_SUCCESS){
        return room_result;
    }
    MtmErrorCode client_result = isClientAvailable(sys, visitor, due_in);
    if(client_result != MTM_SUCCESS){
        return client_result;
    }
    return MTM_SUCCESS;
}

MtmErrorCode isRoomAvailable(EscapeTechnion sys, TechnionFaculty faculty, int id,
                             int due_in[HOURS_FORMAT], Room *room,
                             Company *company){
    bool found = false;
    List faculty_order_list = listCreate(copyOrder, destroyOrder);
    if(!faculty_order_list){
        return MTM_OUT_OF_MEMORY;
    }
    faculty_order_list = listFilter(sys->orderList, orderForFaculty,
                                    (void*)faculty);
    for (Order curr_order = listGetFirst(faculty_order_list); curr_order != NULL;
         curr_order = listGetNext(faculty_order_list)) {
        if(getOrderRoomID(curr_order) == id){
            *company = findCompanyByEmail(sys->companies,
                                         getOrderCompanyEmail(curr_order));
            *room = findRoomInCompany((*company), id);
            found = true;
            if(getDaysOrder(curr_order) == due_in[DAYS] &&
               getHoursOrder(curr_order) == due_in[HOURS]){
                return MTM_ROOM_NOT_AVAILABLE;
            }
        }
    }
    if(!found){
        return MTM_ID_DOES_NOT_EXIST;
    }
    listClear(faculty_order_list);
    listDestroy(faculty_order_list);
    return MTM_SUCCESS;
}

MtmErrorCode isClientAvailable(EscapeTechnion sys, Escaper visitor,
                               int due_in[HOURS_FORMAT]){
    List client_order_list = listCreate(copyOrder, destroyOrder);
    if(!client_order_list){
        return MTM_OUT_OF_MEMORY;
    }
    client_order_list = listFilter(sys->orderList, orderForEscaper,
                                    (void*)getEscaperEmail(visitor));
    for (Order curr_order = listGetFirst(client_order_list); curr_order != NULL;
         curr_order = listGetNext(client_order_list)) {
        if(getDaysOrder(curr_order) == due_in[DAYS] &&
           getHoursOrder(curr_order) == due_in[HOURS]){
            return MTM_CLIENT_IN_ROOM;
        }
    }
    listClear(client_order_list);
    listDestroy(client_order_list);
    return MTM_SUCCESS;
}

MtmErrorCode escaperRecommend(EscapeTechnion sys, char* email, int num_ppl) {
    assert(sys != NULL);
    if (!emailCheck(email) || num_ppl < 1) {
        return MTM_INVALID_PARAMETER;
    }
    Escaper visitor = findEscaperInSet(sys->escapers, email);
    if (visitor == NULL) {
        return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
    }
    Room recommended_room = NULL;
    MtmErrorCode result = searchRecommended(sys, num_ppl, &recommended_room,
                                            visitor);
    if(result != MTM_SUCCESS){
        return result;
    }
    int time[HOURS_FORMAT] = {0};
    int days = 0, hour = roomGetOpenTime(recommended_room);
    result = escaperOrderAux(sys, email, getEscaperFaculty(visitor),
                                          roomGetId(recommended_room), time,
                                          num_ppl);
    assert(result == MTM_SUCCESS || result == MTM_ROOM_NOT_AVAILABLE);
    while (result == MTM_ROOM_NOT_AVAILABLE) {
        time[HOURS] = ++hour;
        if (hour >= roomGetCloseTime(recommended_room)) {
            time[DAYS] = ++days;
            hour = roomGetOpenTime(recommended_room);
            time[HOURS] = hour;
        }
        result = escaperOrderAux(sys, email, getEscaperFaculty(visitor),
                                 roomGetId(recommended_room), time, num_ppl);
    }
    return result;
}

MtmErrorCode searchRecommended(EscapeTechnion sys, int num_ppl,
                               Room *recommended_room, Escaper visitor){
    int company_set_size = setGetSize(sys->companies);
    Company curr_company = setGetFirst(sys->companies);
    Room curr_room = setGetFirst(getCompanyRooms(curr_company));
    *recommended_room = curr_room;
    int curr_score = score_calc(curr_room, visitor, num_ppl);
    int best_score = curr_score;
    for (int i = 0; i < company_set_size; ++i) {
        int room_set_size = setGetSize(getCompanyRooms(curr_company));
        for (int j = 0; j < room_set_size; ++j) {
            update(sys, curr_company, curr_room, recommended_room, visitor,
                   num_ppl, &best_score);
            curr_room = setGetNext(getCompanyRooms(curr_company));
        }
        curr_company = setGetNext(sys->companies);
    }
    if (*recommended_room == NULL) {
        return MTM_NO_ROOMS_AVAILABLE;
    }
    return MTM_SUCCESS;
}

MtmErrorCode reportDay(EscapeTechnion sys, FILE* errorChannel,
                       FILE* outputChannel){
    List today_events = listCreate(copyOrder, destroyOrder);
    today_events = listFilter(sys->orderList, orderAtDay, 0);
    int events = listGetSize(today_events);
    mtmPrintDayHeader(outputChannel, sys->time_log, events);
}

MtmErrorCode reportBest(EscapeTechnion sys, FILE* errorChannel,
                        FILE* outputChannel);

bool orderExistForRoom(List orders, int room_id){
    int size = listGetSize(orders);
    Order curr_order = listGetFirst(orders);
    for (int i = 0; i < size; ++i) {
        if(getOrderRoomID(curr_order) == room_id){
            return true;
        }
        curr_order = listGetNext(orders);
    }
    return false;
}

void resetSystem(EscapeTechnion sys){
    setClear(sys->escapers);
    setDestroy(sys->escapers);
    listClear(sys->orderList);
    listDestroy(sys->orderList);
    setClear(sys->companies);
    setDestroy(sys->companies);
    free(sys);
}

static int score_calc(Room room, Escaper visitor, int num_ppl){
    int people = roomGetNumPpl(room) - num_ppl;
    int level = roomGetDifficulty(room) - getEscaperSkillLevel(visitor);
    return (people)^2 + (level)^2;
}

static int compareFaculties(EscapeTechnion sys, Company company, Room room,
                            Escaper visitor){
    int curr_diff = abs(getEscaperFaculty(visitor) - getCompanyFaculty(company));
    int best_diff = abs(getEscaperFaculty(visitor) -
                                getCompanyFaculty(findCompanyByEmail(
                                        sys->companies, roomGetEmail(room))));
    if(curr_diff < best_diff){
        return SMALLER;
    }
    if(curr_diff == best_diff){
        return EQUAL;
    }
    return BIGGER;
}

static void update(EscapeTechnion sys, Company company, Room room,
                   Room *recommanded_room, Escaper visitor, int num_ppl,
                   int *best_score){
    int curr_score = score_calc(room, visitor, num_ppl);
    if(curr_score <= *best_score){
        if(curr_score < *best_score){
            *best_score = curr_score;
            *recommanded_room = room;
        }else{
            int result = compareFaculties(sys, company,
                                          *recommanded_room, visitor);
            if(result == SMALLER){
                *best_score = curr_score;
                *recommanded_room = room;
            }
            else if(result == EQUAL){
                if(roomGetId(room) < roomGetId(*recommanded_room)){
                    *best_score = curr_score;
                    *recommanded_room = room;
                }
            }
        }
    }
}