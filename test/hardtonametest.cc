#include <gtest/gtest.h>
#include "../src/hardtoname.h"

using namespace std;

TEST(HttpRequestTest, getSimpleJsonbyHttpRequest)
{
    //main 함수에 직접 구현된 simple json을 요청하는 기능을 테스트 할 수 있는 방법이 없다.
    //Testablity 가 높은 구조로 변경해 보자

    EXPECT_TRUE(true);
}

TEST(HttpRequestTest, parseSimpleJson)
{
    //main 함수에 직접 구현된 json parsing 기능을 테스트 할 수 있는 방법이 없다.
    //Testablity 가 높은 구조로 변경해 보자

    EXPECT_TRUE(true);
}

TEST(HttpRequestTest, composeSimpleJson)
{
    //main 함수에 직접 구현된 json composing 기능을 테스트 할 수 있는 방법이 없다.
    //Testablity 가 높은 구조로 변경해 보자

    EXPECT_TRUE(true);
}

TEST(HttpRequestTest, getArrayJsonbyHttpRequest)
{
    //서버에 영향이 없는 독립적인 테스트를 구현해 보세요.
    string expectedStr = "[{\"message\":\"Welcome to Best Reviewer 0\"},{\"message\":\"Welcome to Best Reviewer 1\"},{\"message\":\"Welcome to Best Reviewer 2\"}]";

    EXPECT_STREQ(expectedStr.c_str(), getHttpRequestforArrayJson().c_str());
}

TEST(HttpRequestTest, parseArrayJson)
{
    string arrayJson = "[{\"message\":\"Welcome to Best Reviewer 0\"},{\"message\":\"Welcome to Best Reviewer 1\"},{\"message\":\"Welcome to Best Reviewer 2\"}]";

    printArrayJson(arrayJson);

    //printArrayJson는 cout을 이용해 바로 출력하고 있어, 원하는 동작을 Verify 하는 것이 어렵다.
    //Testablity 가 높은 구조로 변경해 보자

    EXPECT_TRUE(true);
}

TEST(HttpRequestTest, composeArrayJson)
{
    //Testablity 가 높은 구조로 변경해 보자

    EXPECT_TRUE(true);
}