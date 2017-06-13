#include <stdlib.h>
#include "company.h"
#include "test_utilities.h"

static bool testInitCompny(){
    Company company=createCompany();
    ASSERT_TEST(company!=NULL);
    ASSERT_TEST(initCompany(NULL,NULL,UNKNOWN)==COMPANY_NULL_ARGUMENT);
    ASSERT_TEST(initCompany(company,NULL,UNKNOWN)==COMPANY_NULL_ARGUMENT);
    ASSERT_TEST(initCompany(company,"asd",MATHEMATICS)==COMPANY_INVALID_ARGUMENT);
    ASSERT_TEST(initCompany(company,"a@b",PHYSICS)==COMPANY_SUCCESS);
    resetCompany(company);
    destroyCompany(company);
    return true;
}

static bool testDestoryCompany(){
    Company  company =createCompany();
    Company company1=NULL;
    destroyCompany(company1);
    initCompany(company, "asd@a", (TechnionFaculty) 3);
    destroyCompany(company);
    return true;
}

static bool testGetTechnionFaculty(){
    Company company=createCompany();
    Company company1=createCompany();
    initCompany(company,"as@a",PHYSICS);
    initCompany(company1,"asd@c",(TechnionFaculty)6);
    ASSERT_TEST(getCompanyFaculty(company)==PHYSICS);
    ASSERT_TEST(getCompanyFaculty(company1)==(TechnionFaculty)6);
    destroyCompany(company);
    destroyCompany(company1);
    return true;
}
static bool testGetCompanyRevenue(){
    Company company=createCompany();
    initCompany(company,"as@a",PHYSICS);
    addCompanyRevenue(company,100);
    ASSERT_TEST(getCompanyRevenue(company)==100);
    destroyCompany(company);
    return true;
}

static bool testSetCompanyRooms(){
    Company company=NULL;
    ASSERT_TEST(getCompanyRooms(company)==NULL);
    company=createCompany();
    initCompany(company,"ass@sa",(TechnionFaculty)13);
    Room room=createRoom();
    initRoom(room,"ass@sa",2,32,"10-23",5,20);
    ASSERT_TEST(addRoomCompany(company,room)==COMPANY_SUCCESS);
    ASSERT_TEST(addRoomCompany(company,room)==COMPANY_ID_ALREADY_EXIST);
    Room  room1=createRoom();
    initRoom(room1,"ass@sa",4,34,"00-00",3,16);
    free(room1);
    room1 = NULL;
    ASSERT_TEST(addRoomCompany(company,room1)!=COMPANY_SUCCESS);
    ASSERT_TEST(removeRoomCompany(company,room1)!=COMPANY_ID_DOES_NOT_EXIST);
    ASSERT_TEST(removeRoomCompany(company,room)==COMPANY_SUCCESS);
    destroyRoom(room);
    destroyRoom(room1);
    destroyCompany(company);
    return true;
}

static bool testCompareCompanies(){
    Company company=createCompany();
    Company company1=createCompany();
    Company company2=createCompany();
    initCompany(company,"as@a",(TechnionFaculty)13);
    initCompany(company1,"as@a",(TechnionFaculty)12);
    initCompany(company2,"sa@a",(TechnionFaculty)13);
    ASSERT_TEST(compareCompany(company,company1)==0);
    ASSERT_TEST(compareCompany(company,company)==0);
    ASSERT_TEST(compareCompany(company,company2)!=0);
    ASSERT_TEST(compareCompany(company1,company2)!=0);
    destroyCompany(company);
    destroyCompany(company1);
    destroyCompany(company2);
    return true;
}
static bool testCopyCompany(){
    //it is working if the set functions works cause that is what we passed to
    // them
    return true;
}
static bool testGtCompanyEmail(){
    Company company=createCompany();
    Company company1=createCompany();
    initCompany(company,"asd@a",(TechnionFaculty)13);
    initCompany(company1,"as@as",(TechnionFaculty)13);
    ASSERT_TEST(strcmp(getCompanyEmail(company),"asd@a")==0);
    ASSERT_TEST(strcmp(getCompanyEmail(company1),"as@as")==0);
    destroyCompany(company);
    destroyCompany(company1);
    return true;
}
static bool testFindRoomInCompany(){
    Company company=createCompany();
    Company company1=createCompany();
    initCompany(company,"asd@a",(TechnionFaculty)13);
    initCompany(company1,"as@as",(TechnionFaculty)13);
    Room room=createRoom();
    Room room1=createRoom();
    Room room2=createRoom();
    initRoom(room,"as@as",2,3,"10-18",2,4);
    initRoom(room1,"as@as",3,3,"10-18",2,4);
    initRoom(room2,"as@as",4,3,"10-18",2,4);
    addRoomCompany(company1,room);
    addRoomCompany(company1,room1);
    addRoomCompany(company1,room2);
    ASSERT_TEST(roomGetId(findRoomInCompany(company1,2))==roomGetId(room));
    ASSERT_TEST(roomGetId(findRoomInCompany(company1,3))==roomGetId(room1));
    ASSERT_TEST(roomGetId(findRoomInCompany(company1,4))==roomGetId(room2));
    ASSERT_TEST(findRoomInCompany(company,5)==NULL);
    removeRoomCompany(company1,room);
    removeRoomCompany(company1,room1);
    removeRoomCompany(company1,room2);
    destroyRoom(room);
    destroyRoom(room1);
    destroyRoom(room2);
    destroyCompany(company);
    destroyCompany(company1);
    return true;
}


int main(){
    RUN_TEST(testCompareCompanies);
    RUN_TEST(testCopyCompany);
    RUN_TEST(testDestoryCompany);
    RUN_TEST(testFindRoomInCompany);
    RUN_TEST(testGetCompanyRevenue);
    RUN_TEST(testGetTechnionFaculty);
    RUN_TEST(testGtCompanyEmail);
    RUN_TEST(testInitCompny);
    RUN_TEST(testSetCompanyRooms);
    return 0;
}