#include "test_utilities.h"
#include "room.h"
#include "usefullFunctions.h"


static bool testInitRoom(){
    Room room;
    ASSERT_TEST(initRoom(NULL,NULL,NULL,NULL,NULL,NULL,NULL)
                == MTM_INVALID_PARAMETER);
    ASSERT_TEST(initRoom(&room,"asd",22,23,"10-23",3,40)==MTM_INVALID_PARAMETER);
    ASSERT_TEST(initRoom(&room,"sha@s",23,2 ,"100-20",2,20)
                ==MTM_INVALID_PARAMETER);
    ASSERT_TEST(initRoom(&room,"sha@s",23,2 ,"20-10",2,20)
                ==MTM_INVALID_PARAMETER);
    ASSERT_TEST(initRoom(&room,"sha@s",23,2 ,"10-20",2,20)==MTM_SUCCESS);
    resetRoom(room);
}
static bool testResetRoom(){
    return true;
}

static bool test