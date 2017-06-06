#include "test_utilities.h"
#include "company.h"
#include "usefullFunctions.h"


static bool testInitCompany(){
    Company* company;
    char* email= {"notleagal"};
    char* email2={"is@legal"};
    ASSERT_TEST(initCompany(NULL,NULL,NULL)==MTM_NULL_PARAMETER);
    ASSERT_TEST(initCompany(company,email,UNKNOWN)==MTM_INVALID_PARAMETER);
    ASSERT_TEST(initCompany(company,email2,MATHEMATICS)==MTM_SUCCESS);
    resetCompany(company);
    return true;
}

static bool testResetCompany(){
    return true;
}
static bool testGetCompanyFaculty(){
    return true;
}
static bool testGetCompanyRevenu(){
    return true;
}
static bool testAddRoomCompany(){
    Room room;

}
