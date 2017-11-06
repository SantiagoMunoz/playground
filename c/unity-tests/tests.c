#include "Unity/src/unity.h"
#include "functions.h"

void test_addition_works(void){
    TEST_ASSERT_EQUAL_HEX16(6,add_three_bytes(1,2,3));
    TEST_ASSERT_EQUAL_HEX16(65,add_three_bytes(0, 50, 15));
}

int main(){
    UNITY_BEGIN();
    RUN_TEST(test_addition_works);
    return UNITY_END();
}
