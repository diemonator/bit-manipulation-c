#include <string.h>
#include "unity.h"


void setUp(void)
{
    // This is run before EACH test
}

void tearDown(void)
{
    // This is run after EACH test
}

void test_EmptyTest(void)
{
    TEST_ASSERT_EQUAL(1, 1);
}

int main (int argc, char * argv[])
{   
    UnityBegin();
    return UnityEnd();
}
