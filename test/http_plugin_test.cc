#include <iostream>
#include <cstdlib>
#include <thread>
#include <json/json.h>
#include <gtest/gtest.h>

#include "../src/http/http_plugin.h"
#include "../src/http/dto/request.h"
#include "../src/http/dto/response.h"
#include "../src/http/exception/network/connection_failure_exception.h"
#include "../src/http/exception/network/dns_resolving_failure_exception.h"
#include "../src/http/thirdparty/curl/curl_client.h"
#include "../src/utils.h"

using namespace std;

class HttpPluginTest : public ::testing::Test {
    protected:
    void SetUp() override {
        client = std::make_shared<CurlClient>();
        request = std::make_shared<Request>("http://10.241.114.152:34568");
    }
    
    void TearDown() override {
    }

    shared_ptr<HttpPlugin> client;
    shared_ptr<Request> request;

    string CreateRandomId() {
        std::srand(5323);
        std::stringstream ss;
        ss << "fifo_" << std::rand() % 1000;
        cout << "Id: " << ss.str() << endl;
        return ss.str();
    }
};

TEST_F(HttpPluginTest, HttpGet)
{
    request->SetPath("/chat/welcome_arrayJson");
    
    auto response = client->Get(*request);
    EXPECT_EQ(200, response.GetStatusCode());
    EXPECT_TRUE(response.IsSuccess());
} 

TEST_F(HttpPluginTest, HttpGetWithInvalidPath)
{
    request->SetPath("/1234");
    
    auto response = client->Get(*request);
    EXPECT_EQ(404, response.GetStatusCode());
    EXPECT_FALSE(response.IsSuccess());
} 

TEST_F(HttpPluginTest, HttpPost)
{
    string id = CreateRandomId();
    AuthorizationKey key(id, "password");
    Json::Value data;
    data["id"] = id;
    data["password"] = key.QueryPassword();

    Json::StreamWriterBuilder jsonBuilder;
    string jsonData = Json::writeString(jsonBuilder, data);
    
    request->SetPath("/chat/account");
    request->SetBody(jsonData.c_str());

    auto response = client->Post(*request);

    EXPECT_EQ(200, response.GetStatusCode());
} 

TEST_F(HttpPluginTest, HttpConnectionFailure)
{
    Request invalid_request("http://1234");

    EXPECT_THROW(client->Get(invalid_request), ConnectionFailureException);
} 

TEST_F(HttpPluginTest, HttpDnsResolvingFailure)
{
    Request invalid_request("http://efef.efef.eff.com");

    EXPECT_THROW(client->Get(invalid_request), DnsResolvingFailureException);
    EXPECT_THROW(client->Get(invalid_request), DnsResolvingFailureException);
} 

TEST_F(HttpPluginTest, HttpDelete)
{
    request->SetPath("/chat/session?session_id=invalidsessionid");
   
    auto response = client->Delete(*request);
    EXPECT_EQ(403, response.GetStatusCode());
    EXPECT_EQ("Not a valid session ID", response.GetBody());
}

TEST_F(HttpPluginTest, HttpPut)
{
    request->SetBody("test message");

    auto response = client->Put(*request);
    EXPECT_EQ(404, response.GetStatusCode());
}

TEST_F(HttpPluginTest, HttpThreadTest)
{
    request->SetPath("/chat/session?session_id=invalidsessionid");
    std::thread th1([&]() {
            auto response = client->Delete(*request);
            EXPECT_EQ(403, response.GetStatusCode());
            EXPECT_EQ("Not a valid session ID", response.GetBody());
        });

    std::thread th2([&]() {
            auto response = client->Delete(*request);
            EXPECT_EQ(403, response.GetStatusCode());
            EXPECT_EQ("Not a valid session ID", response.GetBody());
    });

    th1.join();
    th2.join();
}