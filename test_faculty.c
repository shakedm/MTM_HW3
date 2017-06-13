#include "test_utilities.h"
#include "faculty.h"


static bool testInitFaculty(){
    Faculty faculty=createFaculty();
    Faculty faculty1=createFaculty();
    ASSERT_TEST(initFaculty(faculty,(TechnionFaculty)13)==FACULTY_SUCCESS);
    ASSERT_TEST(initFaculty(faculty1,102120)==FACULTY_INVALID_PARAMETER);
    ASSERT_TEST(initFaculty(faculty1,-1)==FACULTY_INVALID_PARAMETER);
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
    initRoom(room1,"k",3,6,"10-16",6,40);
    initRoom(room,"asd",2,2,"11-23",3,4);
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

}
