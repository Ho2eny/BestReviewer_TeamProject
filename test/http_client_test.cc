#include <iostream>
#include <random>
#include <json/json.h>
#include <gtest/gtest.h>

#include "../src/http/http_client.h"
#include "../src/http/dto/request.h"
#include "../src/http/dto/response.h"
#include "../src/http/exception/network/authentication_failure_exception.h"
#include "../src/http/exception/network/connection_failure_exception.h"
#include "../src/http/exception/network/dns_resolving_failure_exception.h"

using namespace std;

static string GetHashCode(const string &password)
{
    long long hash = 5381;
    int c;
    const char *c_str = password.c_str();
    while (c = *c_str++)
    {
        hash = (((hash << 5) + hash) + c) % 1000000007;
    }
    long long result = hash % 1000000007;

    stringstream stream;
    stream << result;
    return stream.str();
}

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
    EXPECT_TRUE(response.IsSuccess());
} 

TEST_F(HttpClientTest, HttpGetWithInvalidPath)
{
    HttpClient client;

    request->SetPath("/1234");
    
    auto response = client.Get(*request);
    EXPECT_EQ(404, response.GetStatusCode());
    EXPECT_FALSE(response.IsSuccess());
} 

TEST_F(HttpClientTest, HttpPost)
{
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist1000(1, 1000);

    Json::Value data;
    data["id"] = "fifo_" + to_string(dist1000(rng));
    data["password"] = GetHashCode("password");

    Json::StreamWriterBuilder jsonBuilder;
    string jsonData = Json::writeString(jsonBuilder, data);
    
    request->SetPath("/chat/account");
    request->SetBody(jsonData.c_str());


    HttpClient client;
    auto response = client.Post(*request);

    EXPECT_EQ(200, response.GetStatusCode());
    EXPECT_EQ("", response.GetErrorMessage());
} 

TEST_F(HttpClientTest, HttpConnectionFailure)
{
    HttpClient client;

    Request invalid_request("http://1234");

    EXPECT_THROW(client.Get(invalid_request), ConnectionFailureException);
} 

TEST_F(HttpClientTest, HttpDnsResolvingFailure)
{
    HttpClient client;

    Request invalid_request("http://efef.efef.eff.com");

    EXPECT_THROW(client.Get(invalid_request), DnsResolvingFailureException);
} 

#if 0
TEST_F(HttpClientTest, HttpAuthenticationFailure)
{
    HttpClient client;

    Request invalid_request("https://jigsaw.w3.org/HTTP/Basic/");
    
    EXPECT_THROW(client.Get(invalid_request), AuthenticationFailureException);
} 
#endif

TEST_F(HttpClientTest, HttpDelete)
{
    HttpClient client;

    request->SetPath("/chat/session?session_id=invalidsessionid");
   
    auto response = client.Delete(*request);
    EXPECT_EQ(403, response.GetStatusCode());
    EXPECT_EQ("Not a valid session ID", response.GetBody());
}

