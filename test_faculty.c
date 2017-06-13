#include "test_utilities.h"
#include "faculty.h"


static bool testInitFaculty(){
    Faculty faculty=createFaculty();
    Faculty faculty1=createFaculty();
    ASSERT_TEST(initFaculty(faculty,(TechnionFaculty)13)==FACULTY_SUCCESS);
    destroyFaculty(faculty);
    destroyFaculty(faculty1);
    return true;
}
static bool testFindRoomInFaculty(){
    Faculty faculty=createFaculty();
    Faculty faculty1=createFaculty();
    initFaculty(faculty,(TechnionFaculty)13);
    initFaculty(faculty1,(TechnionFaculty)12);
    Room room=createRoom();
    Room room1=createRoom();
    initRoom(room1,"@k",3,6,"10-16",6,40);
    initRoom(room,"as@d",2,2,"11-23",3,4);
    addFacultyRoom(faculty,room);
    addFacultyRoom(faculty,room1);
    ASSERT_TEST(findRoomInFaculty(faculty,2)==room);
    ASSERT_TEST(findRoomInFaculty(faculty,3)==room1);
    ASSERT_TEST(findRoomInFaculty(faculty1,2)==NULL);
    destroyRoom(room);
    destroyRoom(room1);
    destroyFaculty(faculty);
    destroyFaculty(faculty1);
    return true;

}
static bool testFindCompanyInFaculty(){
    Faculty faculty=createFaculty();
    Faculty faculty1=createFaculty();
    initFaculty(faculty,(TechnionFaculty)13);
    initFaculty(faculty1,(TechnionFaculty)12);
    Company company=createCompany();
    Company company1=createCompany();
    initCompany(company,"asd@s",(TechnionFaculty)13);
    initCompany(company1,"as@",(TechnionFaculty)13);
    ASSERT_TEST(findCompanyInFaculty(faculty,"as@")==company1);
    ASSERT_TEST(findCompanyInFaculty(faculty,"asd@s")==company);
    ASSERT_TEST(findCompanyInFaculty(faculty1,"as@")==NULL);
    destroyCompany(company);
    destroyCompany(company1);
    destroyFaculty(faculty);
    destroyFaculty(faculty1);
    return true;
}
static bool testAddFacultyCompany(){
    Faculty faculty=createFaculty();
    Company company=createCompany();
    initCompany(company,"as@a",(TechnionFaculty)13);
    initFaculty(faculty,(TechnionFaculty)13);
    ASSERT_TEST(addFacultyCompany(faculty,company)==FACULTY_SUCCESS);
    ASSERT_TEST(addFacultyCompany(faculty,company)==FACULTY_EMAIL_ALREADY_EXISTS);
    destroyCompany(company);
    destroyFaculty(faculty);
    return true;
}
static bool testRemoveFacultyCompany(){
    Faculty faculty=createFaculty();
    Company company=createCompany();
    initFaculty(faculty,MATHEMATICS);
    initCompany(company,"as@a",MATHEMATICS);
    addFacultyCompany(faculty,company);
    ASSERT_TEST(removeFacultyCompany(faculty,company)==FACULTY_SUCCESS);
    destroyFaculty(faculty);
    destroyCompany(company);
    return true;
}
static bool testAddFacultyRoom(){
    Faculty faculty=createFaculty();
    Room room=createRoom();
    initFaculty(faculty,EDUCATION_IN_TECH_AND_SCIENCE);
    initRoom(room,"as@a",23,2,"10-23",3,4);
    ASSERT_TEST(addFacultyRoom(faculty,room)==FACULTY_SUCCESS);
    ASSERT_TEST(addFacultyRoom(faculty,room)==FACULTY_ID_ALREADY_EXIST);
    destroyFaculty(faculty);
    destroyRoom(room);
    return true;
}
static bool testRemoveFacultyRoom(){
    Faculty faculty=createFaculty();
    Room room=createRoom();
    initFaculty(faculty,EDUCATION_IN_TECH_AND_SCIENCE);
    initRoom(room,"as@a",23,2,"10-23",3,4);
    ASSERT_TEST(addFacultyRoom(faculty,room)==FACULTY_SUCCESS);
    ASSERT_TEST(removeFacultyRoom(faculty,room)==FACULTY_SUCCESS);
    destroyRoom(room);
    destroyFaculty(faculty);
    return true;
}
static bool testCompareFaculty(){
    Faculty faculty=createFaculty();
    Faculty faculty1=createFaculty();
    initFaculty(faculty,COMPUTER_SCIENCE);
    initFaculty(faculty1,COMPUTER_SCIENCE);
    ASSERT_TEST(compareFaculty(faculty,faculty1)==0);
    destroyFaculty(faculty);
    destroyFaculty(faculty1);
    return true;
}
static bool testCopyFaculty(){
    Faculty faculty=createFaculty();
    Faculty faculty1=createFaculty();
    initFaculty(faculty,COMPUTER_SCIENCE);
    initFaculty(faculty1,PHYSICS);
    Faculty faculty2=copyFaculty(faculty);
    ASSERT_TEST(compareFaculty(faculty,faculty2)==0);
    ASSERT_TEST(compareFaculty(faculty1,faculty2)!=0);
    destroyFaculty(faculty);
    destroyFaculty(faculty1);
    destroyFaculty(faculty2);
    return true;
}
static bool testCollectRevenue(){
    Faculty faculty=createFaculty();
    initFaculty(faculty,COMPUTER_SCIENCE);
    Company company=createCompany();
    Company company1=createCompany();
    initCompany(company1,"asd@",COMPUTER_SCIENCE);
    initCompany(company,"as@",COMPUTER_SCIENCE);
    addFacultyCompany(faculty,company);
    addFacultyCompany(faculty,company1);
    addCompanyRevenue(company,100);
    addCompanyRevenue(company1,150);
    collectRevenue(faculty);
    ASSERT_TEST(getFacultyRevenue(faculty)==250);
    destroyCompany(company);
    destroyCompany(company1);
    destroyFaculty(faculty);
    return true;
}
static bool testGetFacultyId(){
    Faculty faculty=createFaculty();
    initFaculty(faculty,COMPUTER_SCIENCE);
    ASSERT_TEST(getFacultyID(faculty)==(int)COMPUTER_SCIENCE);
    destroyFaculty(faculty);
    return true;
}
int main(){
    RUN_TEST(testAddFacultyCompany);
    RUN_TEST(testAddFacultyRoom);
    RUN_TEST(testCollectRevenue);
    RUN_TEST(testCopyFaculty);
    RUN_TEST(testFindCompanyInFaculty);
    RUN_TEST(testFindRoomInFaculty);
    RUN_TEST(testGetFacultyId);
    RUN_TEST(testInitFaculty);
    RUN_TEST(testRemoveFacultyCompany);
    RUN_TEST(testRemoveFacultyRoom);
    RUN_TEST(testCompareFaculty);
    return 0;
}