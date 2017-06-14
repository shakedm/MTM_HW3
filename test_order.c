#include "test_utilities.h"
#include "order.h"

static bool testInitOrder(){
    Order order=createOrder();
    int time[2]= {1,234};
    ASSERT_TEST(initOrder(order,2,"sdf@a",NULL,time,0,0,UNKNOWN)==ORDER_NULL_PARAMETER);
    ASSERT_TEST(initOrder(order,2,NULL,"as@sa",time,3,23,(TechnionFaculty)2)
                ==ORDER_NULL_PARAMETER);
    ASSERT_TEST(initOrder(order,2,"asd@we","as@sa",time,3,23,(TechnionFaculty)2)
                ==ORDER_INVALID_PARAMETER);
    time[1]=20;
    ASSERT_TEST(initOrder(order,2,"asd@we","as@sa",time,3,23,(TechnionFaculty)2)
                ==ORDER_INVALID_PARAMETER);
    ASSERT_TEST(initOrder(order,2,"asd@we","as@sa",time,3,20,UNKNOWN)==ORDER_INVALID_PARAMETER);
    ASSERT_TEST(initOrder(order,2,"asd@we","as@sa",time,3,20,(TechnionFaculty)2)
                ==ORDER_SUCCESS);
    destroyOrder(order);
    return  true;
}
static bool testCopyOrder(){
    Order order=createOrder();
    int time[2]={1, 10};
    initOrder(order,2,"asd@we","asd@w",time,2,40,(TechnionFaculty)13);
    Order order1=copyOrder(order);
    ASSERT_TEST(compareOrderByFaculty(order,order1)==0);
    ASSERT_TEST(compareOrderByRoomId(order,order1)==0);
    ASSERT_TEST(compareOrderByTime(order,order1)==0);
    destroyOrder(order);
    destroyOrder(order1);
    return true;
}

static bool testGetCost(){
    Order order=createOrder();
    int time[2]={1,20};
    Order order1=createOrder();
    initOrder(order,23,"as@d","a@sds",time,2,20,PHYSICS);
    initOrder(order1,22,"a@sd","d@s",time,2,100,(TechnionFaculty)13);
    ASSERT_TEST(getCost(order)==40);
    ASSERT_TEST(getCost(order1)==200);
    destroyOrder(order);
    destroyOrder(order1);
    return true;
}
static bool testGetNmOfVisitors(){
    Order order=createOrder();
    int time[2]={1,20};
    initOrder(order,23,"as@d","as@ds",time,23,20,PHYSICS);
    ASSERT_TEST(getNumOfVisitors(order)==23);
    destroyOrder(order);
    return true;
}
static bool testGetDaysOrder(){
    Order order=createOrder();
    int time[2]={1,20};
    initOrder(order,23,"as@d","as@ds",time,23,20,PHYSICS);
    ASSERT_TEST(getDaysOrder(order)==1);
    destroyOrder(order);
    return true;
}
static bool testGetHoursOrder(){
    Order order=createOrder();
    int time[2]={1,20};
    initOrder(order,23,"as@d","asd@s",time,23,20,(TechnionFaculty)13);
    ASSERT_TEST(getHoursOrder(order)==20);
    destroyOrder(order);
    return true;
}
static bool testDeacreseDay(){
    Order order=createOrder();
    int time[2]={1,20};
    initOrder(order,23,"as@d","as@ds",time,23,20,PHYSICS);
    decreaseDay(order);
    ASSERT_TEST(getDaysOrder(order)==0);
    decreaseDay(order);
    ASSERT_TEST(getDaysOrder(order)==0);
    destroyOrder(order);
    return true;
}
static bool testGetOrderRoomId(){
    Order order=createOrder();
    int time[2]={1,20};
    initOrder(order,23,"as@d","as@ds",time,3,20,PHYSICS);
    ASSERT_TEST(getOrderRoomId(order)==23);
    destroyOrder(order);
    return true;
}
static bool testGetOrderEscapeEmail(){
    Order order=createOrder();
    Order order1=createOrder();
    int time[2]={1,20};
    initOrder(order,23,"as@d","a@sds",time,23,20,PHYSICS);
    initOrder(order1,2,"as@d","as@ds",time,2,20,PHYSICS);
    ASSERT_TEST(strcmp(getOrderEscaperEmail(order),getOrderEscaperEmail(order1))!=0);
    ASSERT_TEST(strcmp(getOrderEscaperEmail(order),"a@sds")==0);
    ASSERT_TEST(strcmp(getOrderEscaperEmail(order1),"as@ds")==0);
    destroyOrder(order);
    destroyOrder(order1);
    return true;
}
static bool testGetOrderCompanyEmail(){
    Order order=createOrder();
    Order order1=createOrder();
    int time[2]={1,20};
    initOrder(order,23,"as@d","a@sds",time,23,20,PHYSICS);
    initOrder(order1,2,"a@sd","@asds",time,2,20,PHYSICS);
    ASSERT_TEST(strcmp(getOrderCompanyEmail(order),getOrderCompanyEmail(order1))!=0);
    ASSERT_TEST(strcmp(getOrderCompanyEmail(order),"as@d")==0);
    ASSERT_TEST(strcmp(getOrderCompanyEmail(order1),"a@sd")==0);
    destroyOrder(order);
    destroyOrder(order1);
    return true;
}
static bool testGetOrderFaculty(){
    Order order=createOrder();
    Order order1=createOrder();
    int time[2]={1,20};
    initOrder(order,23,"as@d","a@sds",time,23,20,PHYSICS);
    initOrder(order1,2,"@asd","asd@s",time,2,20,(TechnionFaculty)13);
    ASSERT_TEST(getOrderFaculty(order)==PHYSICS);
    ASSERT_TEST(getOrderFaculty(order1)==13);
    destroyOrder(order);
    destroyOrder(order1);
    return true;
}
static bool testSetDiscountOrder(){
    Order order=createOrder();
    Order order1=createOrder();
    int time[2]={1,20};
    initOrder(order,23,"as@d","a@sds",time,1,24,PHYSICS);
    initOrder(order1,2,"a@sd","asd@s",time,2,100,PHYSICS);
    setDiscountOrder(order);
    setDiscountOrder(order1);
    ASSERT_TEST(getCost(order)==18);
    ASSERT_TEST(getCost(order1)==150);
    destroyOrder(order);
    destroyOrder(order1);
    return true;
}
static bool testCompareOrderByTime(){
    Order order=createOrder();
    Order order1=createOrder();
    Order order2=createOrder();
    int time[2]={1,20};
    initOrder(order,23,"as@d","a@sds",time,23,20,PHYSICS);
    initOrder(order1,2,"as@d","as@ds",time,2,20,PHYSICS);
    time[1]=10;
    initOrder(order2,34,"@hf","hf@y",time,4,40,(TechnionFaculty)13);
    ASSERT_TEST(compareOrderByTime(order,order1)==0);
    ASSERT_TEST(compareOrderByTime(order,order)==0);
    ASSERT_TEST(compareOrderByTime(order,order2)>0);
    destroyOrder(order2);
    destroyOrder(order);
    destroyOrder(order1);
    return true;
}
static bool testCompareOrderByFaculty(){
    Order order=createOrder();
    Order order1=createOrder();
    Order order2=createOrder();
    int time[2]={1,20};
    initOrder(order,23,"as@d","a@sds",time,23,20,PHYSICS);
    initOrder(order1,2,"@asd","asd@s",time,2,20,PHYSICS);
    initOrder(order2,3,"@a","as@",time,2,20,(TechnionFaculty)13);
    ASSERT_TEST(compareOrderByFaculty(order,order1)==0);
    ASSERT_TEST(compareOrderByFaculty(order,order2)!=0);
    destroyOrder(order);
    destroyOrder(order1);
    destroyOrder(order2);
    return true;
}
static bool testCompareOrderByRoomId(){
    Order order=createOrder();
    Order order1=createOrder();
    Order order2=createOrder();
    int time[2]={1,20};
    initOrder(order,23,"as@d","a@sds",time,23,20,PHYSICS);
    initOrder(order1,23,"as@d","as@ds",time,2,20,PHYSICS);
    initOrder(order2,3,"@a","a@s",time,2,20,(TechnionFaculty)13);
    ASSERT_TEST(compareOrderByRoomId(order,order1)==0);
    ASSERT_TEST(compareOrderByRoomId(order,order2)!=0);
    destroyOrder(order);
    destroyOrder(order1);
    destroyOrder(order2);
    return true;
}
static bool testOrderForEscaper(){
    Order order=createOrder();
    Order order1=createOrder();
    Order order2=createOrder();
    int time[2]={1,20};
    initOrder(order,23,"as@d","a@sds",time,23,20,PHYSICS);
    initOrder(order1,23,"as@d","as@ds",time,2,20,PHYSICS);
    initOrder(order2,3,"@a","a@s",time,2,20,(TechnionFaculty)13);
    ASSERT_TEST(orderForEscaper(order,"a@sds")==true);
    ASSERT_TEST(orderForEscaper(order1,"as@ds")==true);
    ASSERT_TEST(orderForEscaper(order2,"@a")==false);
    destroyOrder(order);
    destroyOrder(order1);
    destroyOrder(order2);
    return true;
}
static bool testOrderAtDay(){
    Order order=createOrder();
    Order order1=createOrder();
    Order order2=createOrder();
    int time[2]={5,20};
    initOrder(order,23,"as@d","a@sds",time,23,20,PHYSICS);
    initOrder(order1,23,"as@d","as@ds",time,2,20,PHYSICS);
    initOrder(order2,3,"@a","a@s",time,2,20,(TechnionFaculty)13);
    int day=5;
    ASSERT_TEST(orderAtDay(order,day)==true);
    decreaseDay(order1);
    ASSERT_TEST(orderAtDay(order1,day)==false);
    day--;
    ASSERT_TEST(orderAtDay(order2,day)==false);
    destroyOrder(order);
    destroyOrder(order1);
    destroyOrder(order2);
    return true;
}
static bool testOrderForFaculty(){
    Order order=createOrder();
    Order order1=createOrder();
    Order order2=createOrder();
    int time[2]={1,20};
    initOrder(order,23,"as@d","a@sds",time,23,20,PHYSICS);
    initOrder(order1,23,"as@d","as@ds",time,2,20,PHYSICS);
    initOrder(order2,3,"@a","a@s",time,2,20,(TechnionFaculty)13);
    TechnionFaculty faculty=PHYSICS;
    ASSERT_TEST(orderForFaculty(order,faculty)==true);
    ASSERT_TEST(orderForFaculty(order1,faculty)==true);
    ASSERT_TEST(orderForFaculty(order2,faculty)==false);
    destroyOrder(order);
    destroyOrder(order1);
    destroyOrder(order2);
    return true;
}
int main(){
    RUN_TEST(testInitOrder);
    RUN_TEST(testCompareOrderByFaculty);
    RUN_TEST(testCompareOrderByRoomId);
    RUN_TEST(testCompareOrderByTime);
    RUN_TEST(testCopyOrder);
    RUN_TEST(testDeacreseDay);
    RUN_TEST(testGetCost);
    RUN_TEST(testGetDaysOrder);
    RUN_TEST(testGetHoursOrder);
    RUN_TEST(testGetNmOfVisitors);
    RUN_TEST(testGetOrderCompanyEmail);
    RUN_TEST(testGetOrderEscapeEmail);
    RUN_TEST(testGetOrderFaculty);
    RUN_TEST(testGetOrderRoomId);
    RUN_TEST(testOrderAtDay);
    RUN_TEST(testOrderForEscaper);
    RUN_TEST(testSetDiscountOrder);
    RUN_TEST(testOrderForFaculty);
    return 0;
}
