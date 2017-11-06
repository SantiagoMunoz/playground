#include "Unity/src/unity.h"
#include "functions.h"
#include "Unity/extras/fixture/src/unity_fixture.h"

TEST_GROUP(sample);

uint16_t a, b, c;

TEST_SETUP(sample)
{
    a=0;
    b=0;
    c=0;
}

TEST_TEAR_DOWN(sample)
{
}

TEST(sample, no_params)
{
    TEST_ASSERT_EQUAL_HEX16(0,add_three_bytes(a,b,c));
}

TEST(sample, one_param)
{
    a=5;
    TEST_ASSERT_EQUAL_HEX16(5,add_three_bytes(a,b,c));
}

TEST(sample, full_addition)
{
    a=5;
    b=1;
    c=4;
    TEST_ASSERT_EQUAL_HEX16(10,add_three_bytes(a,b,c));
}

TEST_GROUP_RUNNER(sample)
{
    RUN_TEST_CASE(sample, no_params);
    RUN_TEST_CASE(sample, one_param);
    RUN_TEST_CASE(sample, full_addition);

}
int main()
{
    UNITY_BEGIN();
    RUN_TEST_GROUP(sample);
    return UNITY_END();
}
