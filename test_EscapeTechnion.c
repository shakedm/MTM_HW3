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

}

