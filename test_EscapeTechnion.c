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
static bool testEscaperOrder(){
    EscapeTechnion system;
    createEscapeTechnion(&system);
    escaperAdd(system,"as@sa",PHYSICS,4);
    companyAdd(system,"asd@s",PHYSICS);
    roomAdd(system,"asd@s",3,12,4,"00-23",4);
    ASSERT_TEST(escaperOrder(system,"as@sa",PHYSICS,3,"0-10",3)==ESCAPE_SUCCESS);
    ASSERT_TEST(escaperOrder(system,"as",MATHEMATICS,2,"1-12",4)==ESCAPE_CLIENT_EMAIL_DOES_NOT_EXIST);
    resetSystem(system);
    return true;
}
static bool testEscaperReccomend(){
    EscapeTechnion sys;
    createEscapeTechnion(&sys);
    escaperAdd(sys,"as@sa",PHYSICS,4);
    companyAdd(sys,"asd@s",PHYSICS);
    roomAdd(sys,"asd@s",3,12,4,"00-23",4);
    companyAdd(sys,"asda@asa",COMPUTER_SCIENCE);
    roomAdd(sys,"asda@asa",4,4,6,"00-20",5);
    ASSERT_TEST(escaperRecommend(sys,"as@sa",5)==ESCAPE_SUCCESS);
    ASSERT_TEST(escaperRecommend(sys,"adsas",12)==ESCAPE_CLIENT_EMAIL_DOES_NOT_EXIST);
    resetSystem(sys);
    return true;
}
static bool testReportDay(){
    EscapeTechnion sys;
    createEscapeTechnion(&sys);
    escaperAdd(sys,"as@sa",PHYSICS,4);
    companyAdd(sys,"asd@s",PHYSICS);
    roomAdd(sys,"asd@s",3,12,4,"00-23",4);
    companyAdd(sys,"asda@asa",COMPUTER_SCIENCE);
    roomAdd(sys,"asda@asa",4,4,6,"00-20",5);
    escaperOrder(sys,"as@sa",PHYSICS,3,"0-10",3);
    escaperOrder(sys,"as@sa",PHYSICS,3,"1-10",3);
    ASSERT_TEST(reportDay(sys,stdout)==ESCAPE_SUCCESS);
    resetSystem(sys);
    return true;
}
static bool testReportBest(){
    EscapeTechnion sys;
    createEscapeTechnion(&sys);
    escaperAdd(sys,"as@sa",PHYSICS,4);
    companyAdd(sys,"asd@s",PHYSICS);
    roomAdd(sys,"asd@s",3,12,4,"00-23",4);
    companyAdd(sys,"asda@asa",COMPUTER_SCIENCE);
    roomAdd(sys,"asda@asa",4,4,6,"00-20",5);
    escaperOrder(sys,"as@sa",PHYSICS,3,"0-10",3);
    escaperOrder(sys,"as@sa",PHYSICS,3,"1-10",3);
    reportDay(sys,stdout);
    reportDay(sys,stdout);
    reportBest(sys,stdout);
    resetSystem(sys);
    return true;
}
int main(){
    RUN_TEST(testCompanyAdd);
    RUN_TEST(testCompanyRemove);
    RUN_TEST(testCreateEscapeTechnion);
    RUN_TEST(testEscaperAdd);
    RUN_TEST(testEscaperOrder);
    RUN_TEST(testEscaperReccomend);
    RUN_TEST(testEscaperRemove);
    RUN_TEST(testReportBest);
    RUN_TEST(testReportDay);
    RUN_TEST(testRoomAdd);
    RUN_TEST(testRoomRemove);
    return 0;
}
