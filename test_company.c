#include "company.h"
#include "test_utilities.h"

static bool testInitCompny(){
    Company company=createCompany();
    ASSERT_TEST(company!=NULL);
    ASSERT_TEST(initCompany(NULL,NULL,UNKNOWN)==COMPANY_NULL_ARGUMENT);
    ASSERT_TEST(initCompany(company,NULL,UNKNOWN)==COMPANY_INVALID_ARGUMENT);
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
};
