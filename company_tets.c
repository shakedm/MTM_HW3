#include "test_utilities.h"
#include "company.h"
#include "usefullFunctions.h"

#include <stdbool.h>
#include <assert.h>

static bool testInitCompany(){
    Company* company;
    char* email= {"notleagal"};
    char* email2={"is@legal"};
    ASSERT_TEST(initCompany(NULL,NULL,NULL)==MTM_NULL_PARAMETER);
    ASSERT_TEST(initCompany(company,email,UNKNOWN)==MTM_INVALID_PARAMETER);

}

