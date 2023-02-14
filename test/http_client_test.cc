#include <random>
#include <json/json.h> // for test
#include <gtest/gtest.h>

#include "../src/http_client.h"
#include "../src/request.h"
#include "../src/response.h"

using namespace std;

string GetHashCode(const string &password)
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

TEST_F(HttpClientTest, HttpPost)
{
    HttpClient client;

    request->SetPath("/chat/welcome_arrayJson");

    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist1000(1, 1000);

    Json::Value data;
    data["id"] = "fifo_" + to_string(dist1000(rng));
    data["password"] = GetHashCode("password");

    Json::StreamWriterBuilder jsonBuilder;
    string jsonData = Json::writeString(jsonBuilder, data);

    request->SetBody(jsonData.c_str());
    
    auto response = client.Get(*request);
    EXPECT_EQ(200, response.GetStatusCode());
    EXPECT_EQ("", response.GetErrorMessage());
} 