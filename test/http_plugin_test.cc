#include <iostream>
#include <cstdlib>
#include <thread>
#include <json/json.h>
#include <gtest/gtest.h>
#include <time.h>

#include "../src/http/http_plugin.h"
#include "../src/http/dto/request.h"
#include "../src/http/dto/response.h"
#include "../src/http/exception/network/connection_failure_exception.h"
#include "../src/http/exception/network/dns_resolving_failure_exception.h"
#include "../src/http/thirdparty/curl/curl_client.h"
#include "../src/utils.h"

using namespace std;

static string id = "";
static string session_id = "";

class HttpPluginTest : public ::testing::Test {
    protected:
    void SetUp() override {
        client = std::make_shared<CurlClient>();
        request = std::make_shared<Request>("http://10.241.114.152:34568");

        if (id.empty())
            id = CreateRandomId();
    }
    
    void TearDown() override {
    }

    shared_ptr<HttpPlugin> client;
    shared_ptr<Request> request;
    
    string CreateRandomId() {
        std::srand((unsigned)time(NULL));
        std::stringstream ss;
        ss << "fifo_" << std::rand() % 10000;
        cout << "Id: " << ss.str() << endl;
        return ss.str();
    }

    void SetSessionId(string raw_data) {
        auto position = raw_data.find(':');
        session_id = raw_data.substr(position + 2, raw_data.length() - position - 4);

        cout << "raw: " << raw_data << endl;
        cout << "sesion_id: " << session_id << endl;
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

TEST_F(HttpPluginTest, HttpPostWithIdAndPw)
{
    AuthorizationKey key(id, "password");
    Json::Value data;
    data["id"] = id;
    data["nonce"] = key.QueryNonce();
    data["password"] = key.QueryPasswordWithNonce();

    Json::StreamWriterBuilder jsonBuilder;
    string jsonData = Json::writeString(jsonBuilder, data);
    
    request->SetPath("/chat/login");
    request->SetBody(jsonData.c_str());

    auto response = client->Post(*request);
    SetSessionId(response.GetBody());

    EXPECT_EQ(200, response.GetStatusCode());
    EXPECT_FALSE(session_id.empty());
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
    request->SetPath("/chat/session?session_id=" + session_id);

    cout << request->GetFullUrl() << endl;;

    auto response = client->Delete(*request);

    EXPECT_EQ(200, response.GetStatusCode());
}

TEST_F(HttpPluginTest, HttpDeleteWithInavlidSessionId)
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