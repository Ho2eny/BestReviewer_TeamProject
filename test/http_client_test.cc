#include <gtest/gtest.h>
#include "../src/http_client.h"
#include "../src/request.h"
#include "../src/response.h"

using namespace std;

class HttpClientTest : public ::testing::Test {
    protected:
    void SetUp() override {
        request = new Request("http://10.241.114.152:34568");
    }
    
    void TearDown() override {
        delete request;
    }

    Request *request;
};

TEST_F(HttpClientTest, HttpGet)
{
    HttpClient client;

    request->SetPath("/chat/welcome_arrayJson");
    
    auto response = client.Get(*request);
    EXPECT_EQ(200, response.GetStatusCode());
} 