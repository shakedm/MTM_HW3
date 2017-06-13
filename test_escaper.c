#include "escaper.h"
#include "test_utilities.h"



static bool testInitEscaper(){
    Escaper escaper=createEscaper();
    ASSERT_TEST(initEscaper(escaper,NULL,0,0)==ESCAPER_NULL_PARAMETER);

}

