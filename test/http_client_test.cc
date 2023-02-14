#include <gtest/gtest.h>
#include "../src/http_client.h"
#include "../src/request.h"
#include "../src/response.h"

using namespace std;

class HttpClientTest : public ::testing::Test {
    protected:
    void SetUp() override {
        request = new Request("http://testurl.com");
    }
    
    void TearDown() override {
        delete request;
    }

    Request *request;
};

TEST_F(HttpClientTest, HttpGet)
{
    HttpClient client;
    auto response = client.Get(*request);
    EXPECT_EQ(200, response.GetStatusCode());
} 