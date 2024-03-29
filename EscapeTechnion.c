#include "EscapeTechnion.h"

//struct implentation:
struct escape_technion_t {
    Set companies;
    Set escapers;
    List orderList;
    int time_log; // counts days
    int total_revenue;
};

/*!
 * This function calculate the reccomend score for a specific room
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
                            Escaper visitor, int *best_diff);

/*!
 * This function chaecks if the best score for a room reservation needs to be
 * updated, and if so, updates it.
 */
static void update(EscapeTechnion sys, Company company, Room room,
                   Room *recommanded_room, Escaper visitor, int num_ppl,
                   int *best_score, int *best_diff);

/*!
 * This function updates the best companies of the day
 * @param top_companies - array of companies ADTs
 * @param top_revenue - array the matches the top companies array for revenue.
 * @param curr_company - the company to infuse into array
 * @param iterator - where to infuse
 */
static void chainReaction(TechnionFaculty *top_faculties, int *top_revenue,
                          TechnionFaculty curr_faculty, int iterator,
                          int *revenues);

/*!
 * This function creates the actual order
 * @return ESCAPE_INVALID_PARAMETE if one of the parameters is invalid
 *          ESCAPE_CLIENT_EMAIL_DAOES_NOT_EXIST if the email doesn't match
 */
static EscapeTechnionError escaperOrderAux(EscapeTechnion sys, char* email,
                                    TechnionFaculty faculty, int id,
                                    int due_in[HOURS_FORMAT], int num_ppl);

/*!
 * Function searches the best room to match an order
 * @param sys - points to the system in which to check
 * @param num_ppl - the number of peaple for which to reserve
 * @param recommended_room - return val is the best room. NULL if error
 * @param visitor - points to the visitor for which the order.
 * @return MTM_SUCESS if a room was found
 *          MTM_NO_ROOMS_AVILABLE - if there where no matches
 */
static EscapeTechnionError searchRecommended(EscapeTechnion sys, int num_ppl,
                                      Room *recommended_room, Escaper visitor);

/*!
 * Function checks if the given parameters allow a creatin of an order
 * @return ESCAPE_INVALID - if param is invalid
 *          ESCAPE_CLIENT_EMAIL_DOES_NOT_EXIST - if email is not in sys
 *          ESCAPE_CLIENT_IN_ROOM if client has an existing order at the time
 *          ESCAPE_ID_DOES_NOT_EXIST - if there is no room matching the given ID
 *          ESCAPE_ROOM_NOT_AVAILABLE - if there is an exiting order for the
 *          room at the time
 */
static EscapeTechnionError isGoodOrder(bool* discount, EscapeTechnion sys,
                                       char* email,
                                       TechnionFaculty faculty, int id,
                                       int due_in[HOURS_FORMAT],
                                       Company *company);

/*!
 * Function checks if the given room doesnt have an existing order at the time
 * @return ESCAPE_INVALID - if param is invalid
 *          ESCAPE_ID_DOES_NOT_EXIST - if there is no room matching the given ID
 *          ESCAPE_ROOM_NOT_AVAILABLE - if there is an exiting order for the
 *          room at the time
 */
static EscapeTechnionError isRoomAvailable(EscapeTechnion sys, TechnionFaculty faculty,
                                           int id, int due_in[HOURS_FORMAT],
                                           Company *company);

/*!
 * Function checks if the given room doesnt have an existing order at the time
 * @return ESCAPE_INVALID - if param is invalid
 *          ESCAPE_CLIENT_EMAIL_DOES_NOT_EXIST - if email is not in sys
 *          ESCAPE_CLIENT_IN_ROOM if client has an existing order at the time
 */
static EscapeTechnionError isClientAvailable(EscapeTechnion sys, Escaper visitor,
                                      int due_in[HOURS_FORMAT]);

//Function returns company in set by mail search. returns NULL is not found.
static Company findCompanyByEmail(Set companies, const char *email);

//Function removes all of today's orders and advences the time log.
static void endDayProtocol(EscapeTechnion sys);

//Function returns company in set by Faculty search. returns NULL is not found.
static Company findCompanyByFaculty(Set companies, TechnionFaculty faculty);

//Function returns escaper in set by mail search. returns NULL is not found.
static Escaper findEscaperInSet(Set escapers, char *email);

//function filters system orders and returns a sorted list of today's orders
static EscapeTechnionError getTodayList(EscapeTechnion sys, List* list);

//function checks if there is a standing order for given room at given time
static bool orderExistForRoom(List orders, int room_id);

static Room findRoomByFaculty(EscapeTechnion sys, TechnionFaculty faculty,
                              int id,Company* company);


/* * This Function handels cases in which a set action fails according to the
 * error masseges
 * @param result the error result the action returned
 * @param sender_ID signefies the ADT from which the action was taken.
 * @param ADT points to the ADT to handel
 * @return the correct error massege after handeling the fault.
 */
static EscapeTechnionError setErrorHandel(SetResult result, int sender_ID,
                                   void* ADT);

/* * This Function handels cases in which a list action fails according to the
 * error masseges
 * @param result the error result the action returned
 * @param sender_ID signefies the ADT from which the action was taken.
 * @param ADT points to the ADT to handel
 * @return the correct error massege after handeling the fault.
 */
static EscapeTechnionError listErrorHandel(ListResult result, int sender_ID,
                                    void* ADT);

/* * This Function handels cases in which a order action fails according to the
 * error masseges
 * @param result the error result the action returned
 * @param sender_ID signefies the ADT from which the action was taken.
 * @param ADT points to the ADT to handel
 * @return the correct error massege after handeling the fault.
 */
static EscapeTechnionError orderErrorHandel(OrderError result, int sender_ID,
                                     void* ADT);

/* * This Function handels cases in which a escaper action fails according to
 * error masseges
 * @param result the error result the action returned
 * @param sender_ID signefies the ADT from which the action was taken.
 * @param ADT points to the ADT to handel
 * @return the correct error massege after handeling the fault.
 */
static EscapeTechnionError escaperErrorHandel(EscaperError result, int sender_ID,
                                       void* ADT);

/* * This Function handels cases in which a room action fails according to the
 * error masseges
 * @param result the error result the action returned
 * @param sender_ID signefies the ADT from which the action was taken.
 * @param ADT points to the ADT to handel
 * @return the correct error massege after handeling the fault.
 */
static EscapeTechnionError roomErrorHandel(RoomError result, int sender_ID,
                                    void* ADT);

/* * This Function handels cases in which a company action fails according to
 * error masseges
 * @param result the error result the action returned
 * @param sender_ID signefies the ADT from which the action was taken.
 * @param ADT points to the ADT to handel
 * @return the correct error massege after handeling the fault.
 */
static EscapeTechnionError companyErrorHandel(CompanyError result, int sender_ID,
                                       void* ADT);

/* * This Function handels a memory fault in allocation. frees all priviously
 * allocated space
 * @param sender_ID to ID the ADT to handel
 * @param ADT points to the ADT to free
 * @return MTM_OUT_OF_MEMORY after freeing
 */
static EscapeTechnionError memoryFaultHandel(int sender_ID, void* ADT);

/* * This Function handels cases in which a set action fails according to the
 * error masseges
 * @param GdtId - to sort for List or Set hadel functions
 * @param result the error result the action returned
 * @param sender_ID signefies the ADT from which the action was taken.
 * @param ADT points to the ADT to handel
 * @return the correct error massege after handeling the fault.
 */
static EscapeTechnionError errorHandel(int GdtId, void* result, int sender_ID,
                                void* ADT);

/*
 * H-File functions:
 */

EscapeTechnionError createEscapeTechnion(EscapeTechnion *sys){
    EscapeTechnion new_system = malloc(sizeof(*new_system));
    if(!new_system ){
        return ESCAPE_OUT_OF_MEMORY;
    }
    new_system->companies = setCreate(copyCompany, destroyCompany,
                                      compareCompany);
    if(new_system->companies == NULL){
        free(new_system);
        return ESCAPE_OUT_OF_MEMORY;
    }
    new_system->escapers = setCreate(copyEscaper, destroyEscaper,
                                     compareEscaper);
    if(new_system->escapers == NULL){
        setDestroy(new_system->companies);
        free(new_system);
        return ESCAPE_OUT_OF_MEMORY;
    }
    new_system->orderList = listCreate(copyOrder, destroyOrder);
    if(new_system->orderList == NULL){
        setDestroy(new_system->escapers);
        setDestroy(new_system->companies);
        free(new_system);
        return ESCAPE_OUT_OF_MEMORY;
    }
    new_system->time_log = 0;
    new_system->total_revenue = 0;
    *sys = new_system;
    return ESCAPE_SUCCESS;
}

EscapeTechnionError companyAdd(EscapeTechnion sys, char* email,
                        TechnionFaculty faculty){
    Company new_company = createCompany();
    CompanyError result = initCompany(new_company, email, faculty);
    if(result != COMPANY_SUCCESS){
        return errorHandel(HANDEL_COMPANY, (void*)result, COMPANY, new_company);
    }
    if(!new_company){
        return ESCAPE_OUT_OF_MEMORY;
    }
    Company companyHasEmail = findCompanyByEmail(sys->companies, email);
    Escaper visitorHasTheMail = findEscaperInSet(sys->escapers, email);
    if(companyHasEmail || visitorHasTheMail){
        return ESCAPE_EMAIL_ALREADY_EXISTS;
    }
    SetResult setResult = setAdd(sys->companies, new_company);
    if(setResult != SET_SUCCESS){
        return errorHandel(HANDEL_SET, (void*)setResult, COMPANY, new_company);
    }
    destroyCompany(new_company);
    return ESCAPE_SUCCESS;
}


static Company findCompanyByEmail(Set companies, const char *email){
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

static Company findCompanyByFaculty(Set companies, TechnionFaculty faculty){
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

static Escaper findEscaperInSet(Set escapers, char *email){
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


EscapeTechnionError companyRemove(EscapeTechnion sys, char* email){
    if(!email || !sys){
        return ESCAPE_NULL_PARAMETER;
    }
    if(!emailCheck(email)){
        return ESCAPE_INVALID_PARAMETER;
    }
    Company company = findCompanyByEmail(sys->companies, email);
    if(company == NULL){
        return ESCAPE_COMPANY_EMAIL_DOES_NOT_EXIST;

    }
    List orders_for_company = listFilter(sys->orderList, orderForCompany, email);
    int size = listGetSize(orders_for_company);
    if(orders_for_company != NULL && size > 0){
        listClear(orders_for_company);
        listDestroy(orders_for_company);
        return ESCAPE_RESERVATION_EXISTS;
    }
    listClear(orders_for_company);
    listDestroy(orders_for_company);
    setRemove(sys->companies, company);
    return ESCAPE_SUCCESS;
}

EscapeTechnionError roomAdd(EscapeTechnion sys, char* email, int id, int price,
                     int num_ppl, char* working_hrs, int difficulty){
    Room new_room = createRoom();
    RoomError result = initRoom(new_room, email, id,
                                num_ppl, working_hrs, difficulty, price);
    if(result != ROOM_SUCCESS){
        return errorHandel(HANDEL_ROOM, (void*)result, ROOM, new_room);
    }
    Company company = findCompanyByEmail(sys->companies, email);
    if(company == NULL){
        return ESCAPE_COMPANY_EMAIL_DOES_NOT_EXIST;
    }
    CompanyError company_result = addRoomCompany(company, new_room);
    if(company_result != COMPANY_SUCCESS){
        return errorHandel(HANDEL_COMPANY, (void*)company_result,
                           ROOM, new_room);
    }
    destroyRoom(new_room);
    /*Room sysRoom =  findRoomInCompany(company, id);
    if(!sysRoom){
        return ESCAPE_ID_DOES_NOT_EXIST;
    }*/
    return ESCAPE_SUCCESS;
}

EscapeTechnionError roomRemove(EscapeTechnion sys, TechnionFaculty faculty,
                               int id){
    if(faculty < (TechnionFaculty)0 || faculty >= UNKNOWN || id < 1){
        return ESCAPE_INVALID_PARAMETER;
    }
    Company company = findCompanyByFaculty(sys->companies, faculty);
    if(company == NULL){
        return ESCAPE_ID_DOES_NOT_EXIST;
    }
    Room room = findRoomInCompany(company, id);
    if(room == NULL){
        return ESCAPE_ID_DOES_NOT_EXIST;
    }
    if(orderExistForRoom(sys->orderList, roomGetId(room))){
        return ESCAPE_RESERVATION_EXISTS;
    }
    CompanyError result =  removeRoomCompany(company, room);
    if(result != COMPANY_SUCCESS){
        return errorHandel(HANDEL_COMPANY, (void*)result, ESCAPE_TECHNION, sys);
    }
    return ESCAPE_SUCCESS;
}

EscapeTechnionError escaperAdd(EscapeTechnion sys, char* email,
                        TechnionFaculty faculty, int skill_level){
    Escaper visitor = createEscaper();
    if (!visitor){
        return ESCAPE_OUT_OF_MEMORY;
    }
    EscaperError result = initEscaper(visitor, email, faculty, skill_level);
    if (result != ESCAPER_SUCCESS){
        return errorHandel(HANDEL_ESCAPER, (void*)result, ESCAPER, visitor);
    }
    if(setIsIn(sys->escapers, visitor)){
        destroyEscaper(visitor);
        return ESCAPE_EMAIL_ALREADY_EXISTS;
    }
    SetResult setResult = setAdd(sys->escapers, visitor);
    if(setResult != SET_SUCCESS){
        return errorHandel(HANDEL_SET, (void*)setResult, ESCAPER, visitor);
    }
    destroyEscaper(visitor);
    return ESCAPE_SUCCESS;
}

EscapeTechnionError escaperRemove(EscapeTechnion sys, char* email){
    if(sys == NULL){
        return ESCAPE_NULL_PARAMETER;
    }
    if(!emailCheck(email)){
        return ESCAPE_INVALID_PARAMETER;
    }
    Escaper visitor = findEscaperInSet(sys->escapers, email);
    if(visitor == NULL){
        return ESCAPE_CLIENT_EMAIL_DOES_NOT_EXIST;
    }
    int size = listGetSize(sys->orderList);
    if(size == 0){
        setRemove(sys->escapers, visitor);
        return ESCAPE_SUCCESS;
    }
    Order curr_order = listGetFirst(sys->orderList);
    for (int i = 0; i <= size; ++i) {
        if(orderForEscaper(curr_order, getEscaperEmail(visitor))){
            ListResult result = listRemoveCurrent(sys->orderList);
            if (result != LIST_SUCCESS){
                return ESCAPE_INVALID_PARAMETER;
            }
            i = 0;
            size--;
            curr_order = listGetFirst(sys->orderList);
            continue;
        }
        curr_order = listGetNext(sys->orderList);
    }
    setRemove(sys->escapers, visitor);
    return ESCAPE_SUCCESS;
}

EscapeTechnionError escaperOrder(EscapeTechnion sys, char* email,
                          TechnionFaculty faculty, int id, char* time,
                          int num_ppl) {
    if(sys == NULL){
        return ESCAPE_NULL_PARAMETER;
    }
    if(!emailCheck(email) || faculty >= UNKNOWN || faculty < (TechnionFaculty)0
       || id <= 0 || num_ppl < 0){
        return ESCAPE_INVALID_PARAMETER;
    }
    int due_in[HOURS_FORMAT] = {0};
    bool good_time = translateHours(time, due_in, true);
    if (!good_time) {
        return ESCAPE_INVALID_PARAMETER;
    }
    return escaperOrderAux(sys, email, faculty, id, due_in, num_ppl);
}

static EscapeTechnionError escaperOrderAux(EscapeTechnion sys, char* email,
                             TechnionFaculty faculty, int id,
                             int due_in[HOURS_FORMAT], int num_ppl){
    Order new_order = createOrder();
    if (!new_order) {
        return ESCAPE_OUT_OF_MEMORY;
    }
    Company company = NULL;
    bool discount = false;
    EscapeTechnionError result = isGoodOrder(&discount, sys, email, faculty, id,
                                             due_in, &company);
    if(result != ESCAPE_SUCCESS){
        free(new_order);//order has now yet been set to parameters.
        return result;
    }
    assert(order_company != NULL && order_room != NULL);
    OrderError order_result = initOrder(new_order, id,
                                        getCompanyEmail(company),
                                        email, due_in, num_ppl,
                                        roomGetPrice(
                                        findRoomByFaculty(sys, faculty, id,&company))
                                                , faculty, discount);
    if (order_result != ORDER_SUCCESS) {
        return errorHandel(HANDEL_ORDER, (void *) order_result, ORDER,
                           new_order);
    }
    ListResult list_result = listInsertLast(sys->orderList, new_order);
    if (list_result != LIST_SUCCESS) {
        return errorHandel(HANDEL_LIST, (void *) list_result, ESCAPE_TECHNION,
                           sys->orderList);
    }
    destroyOrder(new_order);
    return ESCAPE_SUCCESS;
}

static EscapeTechnionError isGoodOrder(bool* discount, EscapeTechnion sys, char* email,
                         TechnionFaculty faculty, int id,
                         int due_in[HOURS_FORMAT], Company *company){
    Escaper visitor = findEscaperInSet(sys->escapers, email);
    if (visitor == NULL) {
        return ESCAPE_CLIENT_EMAIL_DOES_NOT_EXIST;
    }
    *discount = false;
    if (faculty == getEscaperFaculty(visitor)) {
        *discount = true;
    }
    EscapeTechnionError room_result = isRoomAvailable(sys, faculty, id, due_in,
                                                       company);
    if(room_result != ESCAPE_SUCCESS){
        return room_result;
    }
    EscapeTechnionError client_result = isClientAvailable(sys, visitor, due_in);
    if(client_result != ESCAPE_SUCCESS){
        return client_result;
    }
    return ESCAPE_SUCCESS;
}

static EscapeTechnionError isRoomAvailable(EscapeTechnion sys, TechnionFaculty faculty,
                                           int id, int due_in[HOURS_FORMAT],
                                           Company *company){
    Room room = findRoomByFaculty(sys, faculty, id,company);
    if (!(room)){
        return ESCAPE_ID_DOES_NOT_EXIST;
    }
    List faculty_order_list = listFilter(sys->orderList, orderForFaculty,
                                         (void*)faculty);
    if(!faculty_order_list){
        return ESCAPE_OUT_OF_MEMORY;
    }
    for (Order curr_order = listGetFirst(faculty_order_list); curr_order != NULL;
         curr_order = listGetNext(faculty_order_list)) {
        if(getOrderRoomId(curr_order) == id &&
                getOrderFaculty(curr_order) == faculty){
            if(getDaysOrder(curr_order) == due_in[DAYS] &&
               getHoursOrder(curr_order) == due_in[HOURS]){
                listClear(faculty_order_list);
                listDestroy(faculty_order_list);
                return ESCAPE_ROOM_NOT_AVAILABLE;
            }
        }
    }
    listClear(faculty_order_list);
    listDestroy(faculty_order_list);
    return ESCAPE_SUCCESS;
}

static EscapeTechnionError isClientAvailable(EscapeTechnion sys, Escaper visitor,
                               int due_in[HOURS_FORMAT]){
    List client_order_list = listFilter(sys->orderList, orderForEscaper,
                                        (void*)getEscaperEmail(visitor));
    if(!client_order_list){
        return ESCAPE_OUT_OF_MEMORY;
    }
    for (Order curr_order = listGetFirst(client_order_list); curr_order != NULL;
         curr_order = listGetNext(client_order_list)) {
        if(getDaysOrder(curr_order) == due_in[DAYS] &&
           getHoursOrder(curr_order) == due_in[HOURS]){
            listClear(client_order_list);
            listDestroy(client_order_list);
            return ESCAPE_CLIENT_IN_ROOM;
        }
    }
    listClear(client_order_list);
    listDestroy(client_order_list);
    return ESCAPE_SUCCESS;
}

EscapeTechnionError escaperRecommend(EscapeTechnion sys, char* email, int num_ppl) {
    assert(sys != NULL);
    if (!emailCheck(email) || num_ppl < 1) {
        return ESCAPE_INVALID_PARAMETER;
    }
    Escaper visitor = findEscaperInSet(sys->escapers, email);
    if (visitor == NULL) {
        return ESCAPE_CLIENT_EMAIL_DOES_NOT_EXIST;
    }
    Room recommended_room = NULL;
    EscapeTechnionError result = searchRecommended(sys, num_ppl,
                                                   &recommended_room, visitor);
    if(result != ESCAPE_SUCCESS){
        return result;
    }
    int time[HOURS_FORMAT] = {0};
    time[HOURS] = roomGetOpenTime(recommended_room);
    int days = 0, hour = roomGetOpenTime(recommended_room);
    Company recommanded_company = findCompanyByEmail(sys->companies,
                                                     roomGetEmail(recommended_room));
    result = escaperOrderAux(sys, email, getCompanyFaculty(recommanded_company),
                                          roomGetId(recommended_room), time,
                                          num_ppl);
    assert(result == ESCAPE_SUCCESS || result == ESCAPE_ROOM_NOT_AVAILABLE);
    while (result != ESCAPE_SUCCESS && result != ESCAPE_NO_ROOMS_AVAILABLE) {
        time[HOURS] = ++hour;
        if (hour >= roomGetCloseTime(recommended_room)) {
            time[DAYS] = ++days;
            hour = roomGetOpenTime(recommended_room);
            time[HOURS] = hour;
        }
        result = escaperOrderAux(sys, email,
                                 getCompanyFaculty(recommanded_company),
                                 roomGetId(recommended_room), time, num_ppl);
    }
    return result;
}

static EscapeTechnionError searchRecommended(EscapeTechnion sys, int num_ppl,
                               Room *recommended_room, Escaper visitor){
    int company_set_size = setGetSize(sys->companies);
    Company curr_company = setGetFirst(sys->companies);
    Room curr_room = setGetFirst(getCompanyRooms(curr_company));
    *recommended_room = curr_room;
    int room_set_size = setGetSize(getCompanyRooms(curr_company));
    int best_diff = abs(getEscaperFaculty(visitor) -
                                getCompanyFaculty(curr_company));
    if(room_set_size == 0){
        while (!room_set_size && company_set_size){
            curr_company = setGetNext(sys->companies);
            room_set_size = setGetSize(getCompanyRooms(curr_company));
            company_set_size--;
        }
        if(!company_set_size){
            return ESCAPE_NO_ROOMS_AVAILABLE;
        }
    }
    int curr_score = score_calc(curr_room, visitor, num_ppl);
    int best_score = curr_score;
    for (int i = 0; i < company_set_size; ++i) {
        room_set_size = setGetSize(getCompanyRooms(curr_company));
        if(room_set_size != 0){
            curr_room = setGetFirst(getCompanyRooms(curr_company));
        }
        for (int j = 0; j < room_set_size; ++j) {
            curr_score = score_calc(curr_room, visitor, num_ppl);
            if (curr_score <= best_score){
                update(sys, curr_company, curr_room, recommended_room, visitor,
                       num_ppl, &best_score, &best_diff);
                best_diff = abs(getEscaperFaculty(visitor) -
                                    getCompanyFaculty(curr_company));
            }
            curr_room = setGetNext(getCompanyRooms(curr_company));
        }
        curr_company = setGetNext(sys->companies);
    }
    if (*recommended_room == NULL) {
        return ESCAPE_NO_ROOMS_AVAILABLE;
    }
    return ESCAPE_SUCCESS;
}

EscapeTechnionError reportDay(EscapeTechnion sys, FILE* outputChannel){
    List today_events = listCreate(copyOrder, destroyOrder);
    if(!today_events){
        return ESCAPE_OUT_OF_MEMORY;
    }
    EscapeTechnionError result = getTodayList(sys, &today_events);
    if(result != ESCAPE_SUCCESS){
        return result;
    }
    int events = listGetSize(today_events);
    mtmPrintDayHeader(outputChannel, sys->time_log, events);
    Escaper order_visitor = NULL;
    Company order_company = NULL;
    Room order_room = NULL;
    LIST_FOREACH(Order, curr_order, today_events){
        order_visitor = findEscaperInSet(sys->escapers,
                                         getOrderEscaperEmail(curr_order));
        order_company = findCompanyByEmail(sys->companies,
                                           getOrderCompanyEmail(curr_order));
        order_room = findRoomInCompany(order_company, getOrderRoomId(curr_order));
        if(sameFacultyDiscount(curr_order)){
            setDiscountOrder(curr_order);
        }
        mtmPrintOrder(outputChannel, getOrderEscaperEmail(curr_order),
                      getEscaperSkillLevel(order_visitor),
                      getEscaperFaculty(order_visitor),
                      getOrderCompanyEmail(curr_order),
                      getOrderFaculty(curr_order), getOrderRoomId(curr_order),
                      getHoursOrder(curr_order), roomGetDifficulty(order_room),
                      getNumOfVisitors(curr_order), getCost(curr_order));
        addCompanyRevenue(order_company, getCost(curr_order));
        sys->total_revenue += getCost(curr_order);
    }
    mtmPrintDayFooter(outputChannel, sys->time_log);
    endDayProtocol(sys);
    listClear(today_events);
    listDestroy(today_events);
    return ESCAPE_SUCCESS;
}

void endDayProtocol(EscapeTechnion sys){
    Order curr_order = listGetFirst(sys->orderList);
    int size = listGetSize(sys->orderList);
    int removed = 0;
    for (int i = 0; i < size; ++i) {
        if(getDaysOrder(curr_order) != TODAY){
            decreaseDay(curr_order);
        } else {
            listRemoveCurrent(sys->orderList);
            removed++;
            size--;
            curr_order = listGetFirst(sys->orderList);
            for (int j = 0; j <= i - removed; ++j) {
                curr_order = listGetNext(sys->orderList);
            }
            continue;
        }
        curr_order = listGetNext(sys->orderList);
    }
    sys->time_log = (sys->time_log + 1);
}
int getSystemRevenue(EscapeTechnion sys){
    if(sys == NULL){
        return -1;
    }
    return sys->total_revenue;
}

int getSystemTimeLog(EscapeTechnion sys){
    if(sys == NULL){
        return -1;
    }
    return sys->time_log;
}

EscapeTechnionError reportBest(EscapeTechnion sys, TechnionFaculty* top_faculties,
                               int* top_revenue, int* faculties_revenue){
    SET_FOREACH(Company, curr_company, sys->companies){
        faculties_revenue[(int)getCompanyFaculty(curr_company)] +=
                getCompanyRevenue(curr_company);
    }
    for (int k = 0; k < TOP; ++k) {
        top_faculties[k] = (TechnionFaculty)k;
    }
    int counted = 0;
    for (int i=0; i<(int)UNKNOWN; i++) {
        for (int j = 0; j < TOP; j++) {
            if (faculties_revenue[i] >= top_revenue[j]) {
                if (faculties_revenue[i] > top_revenue[j]) {
                    chainReaction(top_faculties, top_revenue,
                                  (TechnionFaculty) i,
                                  j, faculties_revenue);
                    counted++;
                    break;
                } else if (top_faculties[j] != (TechnionFaculty)0 ){
                    if((TechnionFaculty)i < top_faculties[j]) {
                        chainReaction(top_faculties, top_revenue,
                                      (TechnionFaculty) i, j,
                                      faculties_revenue);
                    }
                    break;
                }else{
                    break;
                }
            } else {
                continue;
            }
        }
    }
    return ESCAPE_SUCCESS;
}

static EscapeTechnionError getTodayList(EscapeTechnion sys, List* sorted){
    List list = listFilter(sys->orderList, orderAtDay, TODAY);
    if(!list){
        return ESCAPE_OUT_OF_MEMORY;
    }
    ListResult result = listSort(list, compareOrderByTime);
    if(result != LIST_SUCCESS){
        return errorHandel(HANDEL_LIST, (void*)result, ESCAPE_TECHNION, list);
    }
    Order curr_order = listGetFirst(list);
    int list_size = listGetSize(list);
    for (int i = 0; i <= list_size && list_size; ++i) {
        result = listInsertLast(*sorted, curr_order);
        if(result != LIST_SUCCESS){
            return errorHandel(HANDEL_LIST, (void*)result, ESCAPE_TECHNION, list);
        }
        if(i < list_size){
            Order next = listGetNext(list);
            if(!next){
                break;
            }
            if(getHoursOrder(curr_order) == getHoursOrder(next)){
                curr_order = next;
                int compare = compareOrderByFaculty(curr_order,
                                                    listGetCurrent(list));
                if(compare >= 0){
                    if(compare > 0){
                        result = listInsertBeforeCurrent(*sorted,
                                                         listGetCurrent(list));
                        if(result != LIST_SUCCESS){
                            return errorHandel(HANDEL_LIST, (void*)result,
                                               ESCAPE_TECHNION, list);
                        }
                        listGetNext(list);
                    } else {
                        if (compareOrderByRoomId(curr_order,
                                                 listGetCurrent(list)) > 0){
                            result = listInsertBeforeCurrent(*sorted,
                                                             listGetNext(list));
                            if(result != LIST_SUCCESS){
                                return errorHandel(HANDEL_LIST, (void*)result,
                                                   ESCAPE_TECHNION, list);
                            }
                            listGetNext(list);
                        }
                    }
                }
                continue;
            }
            curr_order = next;
            continue;
        }
        listGetNext(list);
    }
    listGetFirst(*sorted);
    listClear(list);
    listDestroy(list);
    return ESCAPE_SUCCESS;
}

bool orderExistForRoom(List orders, int room_id){
    int size = listGetSize(orders);
    Order curr_order = listGetFirst(orders);
    for (int i = 0; i < size; ++i) {
        if(getOrderRoomId(curr_order) == room_id){
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
    return ((people)*(people)) + ((level)*(level));
}

static int compareFaculties(EscapeTechnion sys, Company company, Room room,
                            Escaper visitor, int *best_diff){
    int curr_diff = abs(getEscaperFaculty(visitor) - getCompanyFaculty(company));
    if(curr_diff < *best_diff){
        return SMALLER;
    }
    if(curr_diff == *best_diff){
        return EQUAL;
    }
    return BIGGER;
}

static void update(EscapeTechnion sys, Company company, Room room,
                   Room *recommanded_room, Escaper visitor, int num_ppl,
                   int *best_score, int *best_diff){
    int curr_score = score_calc(room, visitor, num_ppl);
    if(curr_score <= *best_score){
        if(curr_score < *best_score){
            *best_score = curr_score;
            *recommanded_room = room;
        }else{
            int result = compareFaculties(sys, company,
                                          *recommanded_room, visitor, best_diff);
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

static void chainReaction(TechnionFaculty *top_faculties, int *top_revenue,
                          TechnionFaculty curr_faculty, int iterator,
                          int *revenues){
    int temp_revenue[TOP] = {0};
    TechnionFaculty temp_top[TOP] = {(TechnionFaculty)0};
    for (int i = iterator; i < TOP; ++i) {
        temp_top[i] = top_faculties[i];
        temp_revenue[i] = top_revenue[i];
    }
    top_faculties[iterator] = curr_faculty;
    top_revenue[iterator] = revenues[(int)curr_faculty];
    for (int j = iterator + 1; j < TOP; ++j) {
        top_faculties[j] = temp_top[j - 1];
        top_revenue[j] = temp_revenue[j - 1];
    }
}

static EscapeTechnionError setErrorHandel(SetResult result, int sender_ID,
                                          void* ADT){
    switch (result){
        case SET_OUT_OF_MEMORY :
            return memoryFaultHandel(sender_ID, ADT);
        case SET_NULL_ARGUMENT:
            return ESCAPE_NULL_PARAMETER;
        case SET_ITEM_ALREADY_EXISTS:
            switch (sender_ID){
                case COMPANY:
                    return ESCAPE_EMAIL_ALREADY_EXISTS;
                case ROOM:
                    return ESCAPE_ID_ALREADY_EXIST;
                case ESCAPER:
                    return ESCAPE_EMAIL_ALREADY_EXISTS;
                default:
                    return ESCAPE_INVALID_PARAMETER;
            }
        case SET_ITEM_DOES_NOT_EXIST:
            switch (sender_ID){
                case COMPANY:
                    return ESCAPE_COMPANY_EMAIL_DOES_NOT_EXIST;
                case ROOM:
                    return ESCAPE_ID_DOES_NOT_EXIST;
                case ESCAPER:
                    return ESCAPE_CLIENT_EMAIL_DOES_NOT_EXIST;
                default:
                    return ESCAPE_INVALID_PARAMETER;
            }
        default:
            return ESCAPE_INVALID_PARAMETER;
    }
}


static EscapeTechnionError memoryFaultHandel(int sender_ID, void* ADT){
    switch (sender_ID){
        case ROOM:
            destroyRoom(ADT);
            break;
        case ESCAPER:
            destroyEscaper(ADT);
            break;
        case COMPANY:
            destroyCompany(ADT);
            break;
        case ESCAPE_TECHNION:
            resetSystem((EscapeTechnion)ADT);
            break;
        default:
            return ESCAPE_OUT_OF_MEMORY;
    }
    return ESCAPE_OUT_OF_MEMORY;
}


static EscapeTechnionError errorHandel(int GdtId, void* result, int sender_ID,
                                void* ADT){
    switch (GdtId){
        case HANDEL_SET:
            return setErrorHandel((SetResult)result, sender_ID, ADT);
        case HANDEL_LIST:
            return listErrorHandel((ListResult)result, sender_ID, ADT);
        case HANDEL_ORDER:
            return orderErrorHandel((OrderError)result, sender_ID, ADT);
        case HANDEL_ROOM:
            return roomErrorHandel((RoomError)result, sender_ID, ADT);
        case HANDEL_COMPANY:
            return companyErrorHandel((CompanyError)result, sender_ID, ADT);
        case HANDEL_ESCAPER:
            return escaperErrorHandel((EscaperError)result, sender_ID, ADT);
        default:
            return ESCAPE_INVALID_PARAMETER;
    }
}



static EscapeTechnionError listErrorHandel(ListResult result, int sender_ID,
                                    void* ADT){
    switch (result){
        case LIST_OUT_OF_MEMORY :
            return memoryFaultHandel(sender_ID, ADT);
        case LIST_NULL_ARGUMENT:
            return ESCAPE_NULL_PARAMETER;
        case LIST_INVALID_CURRENT:
            return ESCAPE_INVALID_PARAMETER;
        default:
            return ESCAPE_INVALID_PARAMETER;
    }
}


static EscapeTechnionError orderErrorHandel(OrderError result, int sender_ID,
                                     void* ADT){
    switch (result){
        case ORDER_OUT_OF_MEMORY :
            return memoryFaultHandel(sender_ID, ADT);
        case ORDER_NULL_PARAMETER:{
            free(ADT);
            return ESCAPE_NULL_PARAMETER;
        }
        case ORDER_INVALID_PARAMETER:{
            free(ADT);
            return ESCAPE_INVALID_PARAMETER;
        }
        default:
            return ESCAPE_INVALID_PARAMETER;
    }
}

static EscapeTechnionError roomErrorHandel(RoomError result, int sender_ID,
                                           void* ADT){
    switch (result){
        case ROOM_OUT_OF_MEMORY :
            return memoryFaultHandel(sender_ID, ADT);
        case ROOM_NULL_PARAMETER:{
            free(ADT);
            return ESCAPE_NULL_PARAMETER;
        }
        case ROOM_INVALID_PARAMETER:{
            free(ADT);
            return ESCAPE_INVALID_PARAMETER;
        }
        default:
            return ESCAPE_INVALID_PARAMETER;
    }
}

static EscapeTechnionError companyErrorHandel(CompanyError result, int sender_ID,
                                       void* ADT){
    switch (result){
        case COMPANY_OUT_OF_MEMORY:
            return memoryFaultHandel(sender_ID, ADT);
        case COMPANY_NULL_ARGUMENT:{
            free(ADT);
            return ESCAPE_NULL_PARAMETER;
        }
        case COMPANY_INVALID_ARGUMENT:{
            free(ADT);
            return ESCAPE_INVALID_PARAMETER;
        }
        case COMPANY_ID_ALREADY_EXIST:{
            free(ADT);
            return ESCAPE_ID_ALREADY_EXIST;
        }
        case COMPANY_ID_DOES_NOT_EXIST:
            return ESCAPE_ID_DOES_NOT_EXIST;
        default:
            return ESCAPE_INVALID_PARAMETER;
    }
}

static EscapeTechnionError escaperErrorHandel(EscaperError result, int sender_ID,
                                       void* ADT){
    switch (result){
        case ESCAPER_OUT_OF_MEMORY :
            return memoryFaultHandel(sender_ID, ADT);
        case ESCAPER_NULL_PARAMETER:{
            free(ADT);
            return ESCAPE_ID_DOES_NOT_EXIST;
        }
        case ESCAPER_INVALID_PARAMETER:{
            free(ADT);
            return ESCAPE_INVALID_PARAMETER;
        }
        default:
            return ESCAPE_INVALID_PARAMETER;
    }
}

static Room findRoomByFaculty(EscapeTechnion sys, TechnionFaculty faculty, int id,
                                Company* company){
    Room room = NULL;
    SET_FOREACH(Company, curr_company, sys->companies){
        if(getCompanyFaculty(curr_company) == faculty){
            room = findRoomInCompany(curr_company, id);
            if(room != NULL){
                *company=curr_company;
                return room;
            }
        }

    }
    *company=NULL;
    return NULL;
}
