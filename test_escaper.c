#include "escaper.h"
#include "test_utilities.h"



static bool testInitEscaper(){
    Escaper escaper=createEscaper();
    ASSERT_TEST(initEscaper(escaper,NULL,0,0) == ESCAPER_NULL_PARAMETER);
    ASSERT_TEST(initEscaper(escaper,"as@a",3,-3)==ESCAPER_INVALID_PARAMETER);
    ASSERT_TEST(initEscaper(escaper,"as@as",4,3)==ESCAPER_SUCCESS);
    destroyEscaper(escaper);
    return true;
}
static bool testDestroyEscaper(){
    Escaper escaper=createEscaper();
    Escaper escaper1=NULL;
    destroyEscaper(escaper);
    destroyEscaper(escaper1);
    return true;
}
static bool testGetEscaperEmail(){
    Escaper escaper=createEscaper();
    initEscaper(escaper,"asd@s",13,2);
    ASSERT_TEST(strcmp(getEscaperEmail(escaper),"asd@s")==0);
    destroyEscaper(escaper);
    return true;
}
static bool testGetEscaperFaculty(){
    Escaper escaper=createEscaper();
    Escaper escaper1=createEscaper();
    initEscaper(escaper,"as@a",13,2);
    initEscaper(escaper1,"sas@a",12,2);
    ASSERT_TEST(getEscaperFaculty(escaper)==13);
    ASSERT_TEST(getEscaperFaculty(escaper1)==12);
    destroyEscaper(escaper);
    destroyEscaper(escaper1);
    return true;
}
static bool testGetEscaperSkill(){
    Escaper escaper=createEscaper();
    initEscaper(escaper,"as@a",13,3);
    ASSERT_TEST(getEscaperSkillLevel(escaper)==3);
    destroyEscaper(escaper);
    return true;
}
static bool testCompareEscaper(){
    Escaper escaper=createEscaper();
    Escaper escaper1=createEscaper();
    initEscaper(escaper,"aswe@a",12,2);
    initEscaper(escaper1,"aswe@a",13,1);
    ASSERT_TEST(compareEscaper(escaper,escaper1)==0);
    destroyEscaper(escaper);
    destroyEscaper(escaper1);
    return true;
}
static bool testCopyEscaper(){
    Escaper escaper=createEscaper();
    initEscaper(escaper,"assd@a",12,2);
    Escaper escaper1=copyEscaper(escaper);
    ASSERT_TEST(compareEscaper(escaper,escaper1)==0);
    destroyEscaper(escaper);
    destroyEscaper(escaper1);
    return true;
}


int main(){
    RUN_TEST(testInitEscaper);
    RUN_TEST(testGetEscaperSkill);
    RUN_TEST(testGetEscaperFaculty);
    RUN_TEST(testGetEscaperEmail);
    RUN_TEST(testDestroyEscaper);
    RUN_TEST(testCopyEscaper);
    RUN_TEST(testCompareEscaper);
    return 0;
}