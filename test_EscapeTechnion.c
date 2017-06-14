#include "test_utilities.h"
#include "EscapeTechnion.h"


static bool testCreateEscapeTechnion(){
    EscapeTechnion system;
    ASSERT_TEST(createEscapeTechnion(&system)==ESCAPE_SUCCESS);
    resetSystem(system);
    return true;
}
static bool testCompanyAdd(){
    EscapeTechnion system;
    createEscapeTechnion(&system);
    ASSERT_TEST(companyAdd(system,"as@s",PHYSICS)==ESCAPE_SUCCESS);
    ASSERT_TEST(companyAdd(system,"as@s",PHYSICS)==ESCAPE_EMAIL_ALREADY_EXISTS);
    resetSystem(system);
    return true;
}
static bool testCompanyRemove(){
    EscapeTechnion system;
    createEscapeTechnion(&system);
    companyAdd(system,"as@s",PHYSICS);
    companyAdd(system,"ad@a",PHYSICS);
    ASSERT_TEST(companyRemove(system,"as@s")==ESCAPE_SUCCESS);
    ASSERT_TEST(companyRemove(system,"as@s")==ESCAPE_COMPANY_EMAIL_DOES_NOT_EXIST);
    ASSERT_TEST(companyRemove(system,"ad@a")==ESCAPE_SUCCESS);
    resetSystem(system);
    return true;
}
static bool testRoomAdd(){
    EscapeTechnion system;
    createEscapeTechnion(&system);
    ASSERT_TEST(roomAdd(system,"as@s",2,4,2,"10-14",4)==ESCAPE_SUCCESS);
    ASSERT_TEST(roomAdd(system,"as@s",2,4,2,"11-15",4)==ESCAPE_EMAIL_ALREADY_EXISTS);
    ASSERT_TEST(roomAdd(system,"asd@s",3,4,2,"10-14",4)==ESCAPE_SUCCESS);
    resetSystem(system);
    return true;

}
static bool testRoomRemove(){
    EscapeTechnion system;
    createEscapeTechnion(&system);
    companyAdd(system,"asd@a",COMPUTER_SCIENCE);
    roomAdd(system,"asd@a",3,4,2,"10-20",4);
    ASSERT_TEST(roomRemove(system,COMPUTER_SCIENCE,3)==ESCAPE_SUCCESS);
    resetSystem(system);
    return true;
}
static bool testEscaperAdd(){
    EscapeTechnion system;
    createEscapeTechnion(&system);
    ASSERT_TEST(escaperAdd(system,"asd@s",PHYSICS,4)==ESCAPE_SUCCESS);
    ASSERT_TEST(escaperAdd(system,"asd@s",COMPUTER_SCIENCE,4)==ESCAPE_EMAIL_ALREADY_EXISTS);
    resetSystem(system);
    return true;
}
static bool testEscaperRemove(){
    EscapeTechnion system;
    createEscapeTechnion(&system);
    escaperAdd(system,"as@sa",PHYSICS,4);
    ASSERT_TEST(escaperRemove(system,"as@sa")==ESCAPE_SUCCESS);
    ASSERT_TEST(escaperRemove(system,"as@sa")==ESCAPE_CLIENT_EMAIL_DOES_NOT_EXIST);
    resetSystem(system);
    return true;
}
static bool test

