#include <random>
#include <iostream>
#include <string>
#include <sstream>
#include <gtest/gtest.h>
#include "../src/command/invoker.h"
#include "../src/command/receiver.h"
#include "../src/command/login.h"

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

string GetNonce()
{
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist9(1, 9);
    return to_string(dist9(rng));
}

string GetPasswordWithNonce(const string &password, const string &nonce)
{
    string new_password = GetHashCode(password);
    return GetHashCode(new_password + nonce);
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    cout << "WriteCallback " << endl;
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

static size_t header_callback(char *buffer, size_t size,
                              size_t nitems, void *userdata)
{
    cout << "Header Callback " << endl;
    strcpy((char *)userdata, buffer);

    std::cout << (char *)userdata; // This prints the headers correctly

    return nitems * size;
}

TEST(ApiTest, DISABLED_signup)
{
    string server = "http://10.241.114.152:34568/chat/account";

    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist1000(1, 1000);

    Json::Value data;
    data["id"] = "fifo_" + to_string(dist1000(rng));
    data["password"] = GetHashCode("password");
    cout << data << endl;

    CURL *curl;
    CURLcode res;
    string readBuffer;

    Json::StreamWriterBuilder jsonBuilder;
    string jsonData = Json::writeString(jsonBuilder, data);

    curl = curl_easy_init();
    struct curl_slist *list = NULL;
    if (curl)
    {
        list = curl_slist_append(list, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
        curl_easy_setopt(curl, CURLOPT_URL, server.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &jsonData);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK)
        {
            cout << "Failed to perform the request. "
                 << "Return code: " << res
                 << endl;
        }
        else
        {
            cout << "Succeed" << endl;
        }

        std::cout << jsonData << std::endl;
    }

    EXPECT_EQ(res, CURLE_OK);
}

TEST(ApiTest, TestHash)
{
    string password = "testtest";
    EXPECT_EQ(GetPasswordWithNonce(password, "5"), "527851963");
}

TEST(ApiTest, login)
{
    // main 함수에 직접 구현된 simple json을 요청하는 기능을 테스트 할 수 있는 방법이 없다.
    // Testablity 가 높은 구조로 변경해 보자

    string server = "http://10.241.114.152:34568/chat/login";
    string nounce = GetNonce();

    Json::Value data;
    data["id"] = "fifo_274";
    data["nonce"] = nounce;
    data["password"] = GetPasswordWithNonce("password", nounce);
    cout << data << endl;

    CURL *curl;
    CURLcode res;
    string readBuffer;
    std::string headers;

    Json::StreamWriterBuilder jsonBuilder;
    string jsonData = Json::writeString(jsonBuilder, data);

    curl = curl_easy_init();
    struct curl_slist *list = NULL;
    if (curl)
    {
        list = curl_slist_append(list, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
        curl_easy_setopt(curl, CURLOPT_URL, server.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &jsonData);
        res = curl_easy_perform(curl);
        curl_slist_free_all(list);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK)
        {
            cout << "Failed to perform the request. "
                 << "Return code: " << res
                 << endl;
        }
        else
        {
            cout << "Succeed" << endl;
        }

        cout << jsonData << endl;
    }

    EXPECT_EQ(res, CURLE_OK);
}
