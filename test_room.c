#include "test_utilities.h"
#include "room.h"


static bool testInitRoom(){
    Room room= createRoom();
    ASSERT_TEST(initRoom(NULL,NULL,0,0,NULL,0,0)
                == MTM_INVALID_PARAMETER);
    ASSERT_TEST(initRoom(&room,"asd",22,23,"10-23",3,40)==MTM_INVALID_PARAMETER);
    ASSERT_TEST(initRoom(&room,"sha@s",23,2 ,"100-20",2,20)
                ==MTM_INVALID_PARAMETER);
    ASSERT_TEST(initRoom(&room,"sha@s",23,2 ,"20-10",2,20)
                ==MTM_INVALID_PARAMETER);
    ASSERT_TEST(initRoom(&room,"sha@s",23,2 ,"10-20",2,20)==MTM_SUCCESS);
    resetRoom(room);
    destroyRoom(room);
    return true;
}
static bool testResetRoom(){
    /*will be checked with valgrind, assuming "free" works as expected
     * and will not return error*/
    return true;
}

static bool testGetId(){
    Room room= createRoom();
    initRoom(&room,"sha@s",23,2 ,"10-20",2,20);
    ASSERT_TEST(roomGetId(room)==23);
    resetRoom(room);
    ASSERT_TEST(roomGetId(room)!=23);
    destroyRoom(room);
    return true;
}
static bool testGetNumPpl(){
    Room room= createRoom();
    initRoom(&room,"sha@s",23,2 ,"10-20",2,20);
    ASSERT_TEST(roomGetNumPpl(room)==2);
    resetRoom(room);
    ASSERT_TEST(roomGetNumPpl(room)!=2);
    destroyRoom(room);
    return  true;
}
static bool testGetDiffucalty(){
    Room room= createRoom();
    Room room1= createRoom();
    Room room2= createRoom();
    initRoom(&room,"sha@s",21,2 ,"10-20",2,20);
    initRoom(&room1,"sha@sa",22,2 ,"10-20",1,20);
    initRoom(&room2,"sha@sass",24,2 ,"10-20",10,20);
    ASSERT_TEST(roomGetDifficulty(room)==2);
    ASSERT_TEST(roomGetDifficulty(room1)==1);
    ASSERT_TEST(roomGetDifficulty(room2)==10);
    resetRoom(room);
    resetRoom(room1);
    resetRoom(room2);
    destroyRoom(room);
    destroyRoom(room1);
    destroyRoom(room2);
    return true;
}

static bool testGetWorkingHours(){
    Room room= createRoom();
    Room room1= createRoom();
    int time[2];
    initRoom(&room,"sha@s",23,2 ,"10-20",2,20);
    (roomGetWorkingHours(room,time));
    ASSERT_TEST(time[0]==10);
    ASSERT_TEST(time[1]==20);
    initRoom(&room1,"sha@s",23,2 ,"01-09",2,20);
    roomGetWorkingHours(room1,time);
    ASSERT_TEST(time[0]==1);
    ASSERT_TEST(time[1]==9);
    resetRoom(room);
    resetRoom(room1);
    destroyRoom(room);
    destroyRoom(room1);
    return true;
}
static bool testGetPrice(){
    Room room= createRoom();
    Room room1= createRoom();
    initRoom(&room,"sha@s",23,2 ,"10-20",2,20);
    ASSERT_TEST(roomGetPrice(room)==20);
    initRoom(&room1,"sha@s",23,2 ,"10-20",2,24);
    ASSERT_TEST(roomGetPrice(room1)==24);
    resetRoom(room);
    resetRoom(room1);
    destroyRoom(room);
    destroyRoom(room1);
    return true;
}
static bool testGetEmail(){
    Room room= createRoom();
    Room room1= createRoom();
    initRoom(&room,"sha@s",23,2 ,"10-20",2,20);
    ASSERT_TEST(strcmp(roomGetEmail(room),"sha@s")==0);
    initRoom(&room1,"sha@",23,2 ,"10-20",2,20);
    ASSERT_TEST(strcmp(roomGetEmail(room1),"sha@")==0);
    resetRoom(room);
    resetRoom(room1);
    return true;
}

static bool testCompareRoom(){
    Room room= createRoom();
    Room room1= createRoom();
    Room room2= createRoom();
    Room room3= createRoom();
    initRoom(&room,"sha@s",23,2 ,"10-20",2,24);
    initRoom(&room1,"sha@s",23,2 ,"10-20",2,24);
    initRoom(&room2,"sha@s",25,2 ,"10-20",2,24);
    initRoom(&room3,"sha@s",22,2 ,"10-20",2,24);
    ASSERT_TEST(compareRoom(room,room1)==0);
    ASSERT_TEST(compareRoom(room,room2)<0);
    ASSERT_TEST(compareRoom(room1,room3)>0);
    ASSERT_TEST(compareRoom(room3,room)<0);
    resetRoom(room);
    resetRoom(room1);
    resetRoom(room2);
    resetRoom(room3);
    destroyRoom(room);
    destroyRoom(room1);
    destroyRoom(room2);
    destroyRoom(room3);
    return true;
}
static bool testCopyRoom(){
    Room room= createRoom();
    Room room1= createRoom();
    initRoom(&room,"shsa@s",22,3 ,"11-20",3,20);
    initRoom(&room1,"sha@s",23,2 ,"10-20",2,24);
    Room copy = copyRoom(room);
    Room copy1 = copyRoom(room1);
    ASSERT_TEST(compareRoom(room,copy)==0);
    ASSERT_TEST(compareRoom(room1,copy1)==0);
    ASSERT_TEST(strcmp(roomGetEmail(room),roomGetEmail(copy))==0);
    ASSERT_TEST(strcmp(roomGetEmail(room1),roomGetEmail(copy1))==0);
    ASSERT_TEST(roomGetPrice(room)==roomGetPrice(copy));
    ASSERT_TEST(roomGetPrice(room1)==roomGetPrice(copy1));
    resetRoom(room);
    resetRoom(room1);
    destroyRoom(room);
    destroyRoom(room1);
    ASSERT_TEST(compareRoom(copy,copy1)<0);
    resetRoom(copy);
    resetRoom(copy1);
    destroyRoom(copy);
    destroyRoom(copy1);
    return true;

}

int main(int argv, char **argc){
    RUN_TEST(testResetRoom);
    RUN_TEST(testInitRoom);
    RUN_TEST(testGetWorkingHours);
    RUN_TEST(testGetPrice);
    RUN_TEST(testGetNumPpl);
    RUN_TEST(testGetId);
    RUN_TEST(testGetEmail);
    RUN_TEST(testGetDiffucalty);
    RUN_TEST(testCopyRoom);
    RUN_TEST(testCompareRoom);
    return 0;
}