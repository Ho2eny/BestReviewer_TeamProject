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
    EXPECT_EQ("", response.GetErrorMessage());
} 

TEST_F(HttpClientTest, HttpGetWithInvalidPath)
{
    HttpClient client;

    request->SetPath("/1234");
    
    auto response = client.Get(*request);
    EXPECT_EQ(404, response.GetStatusCode());
} 

TEST_F(HttpClientTest, HttpGetWithInvalidUrl)
{
    HttpClient client;

    Request invalid_request("http://1234");
    
    auto response = client.Get(invalid_request);
    EXPECT_EQ(0, response.GetStatusCode());
    EXPECT_EQ("error response : 7", response.GetErrorMessage());
    EXPECT_EQ("", response.GetBody());
} 