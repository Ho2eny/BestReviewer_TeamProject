#include <iostream>
#include <curl/curl.h>
#include <json/json.h>
#include "hardtoname.h"

#define CHAT_WELCOME_SIMPLE_JSON "11"
#define CHAT_PARSE_SIMPLE_JSON "12"
#define CHAT_WELCOME_ARRAY_JSON "21"
#define CHAT_QUIT    "q"

using namespace std;

static size_t curl_callback(void *contents, size_t size, size_t nmemb, void *userp) {
	char* str = static_cast<char*>(contents);
	size_t realsize = size * nmemb;
	string& res = *(static_cast<std::string*>(userp));
	res.append(str, realsize);
	return realsize;
}



int main(int argc, char* argv[]) {

    /*
    if (argc != 3) {
        cout << "usage: chat_client.exe localhost 34568" << endl;
        return 0;
    }*/

    string userSelection;
    string response;

    do {

        cout << "11.welcome_simpleJson, 12.parse json, 13.assemble json" << endl;
        cout << "21.welcome_arrayJson, 22.parse json, 33.assemble json" << endl;
        cout << "Enter command(q for quit) : ";
        cin >> userSelection;

        //TODO : 많은 if ~ else if 가 생기고, 내부의 코드가 많아 질것 같은데 더 좋을 방법은 생각해보시기 바랍니다.
        if(userSelection == "11") {

            CURL *curl;

            long responseCode;

            response.clear();

            /*TODO
              - curl 을 사용하는 과정이 계속 반복되는데 좋은 코드 품질을 가지도록 구현해보세요.
              - 서버의 동작여부와 상관 없이 Client 의 기능이 잘 동작한다는 것을 보장하는 테스트를 만들어 보세요.
            */
            curl_global_init(CURL_GLOBAL_ALL);
            curl = curl_easy_init();
            curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:34568/chat/welcome_simpleJson");
            curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

            CURLcode res = curl_easy_perform(curl);

            if (res == CURLE_OK) {
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
                cout << "OK to curl : " << responseCode << ", " << response << endl << endl;
            } else {
                cout << "error response : " << res << endl << endl;
            }

            curl_easy_cleanup(curl);
            curl_global_cleanup();

        } else if (userSelection == CHAT_PARSE_SIMPLE_JSON) {
            /* TODO
              test framework 을 통해서 Json 을 사용하는 방법을 간단하게 설명하고
              chatting client 가 원하는대로 외부 모듈인 json 이 동작하는지를 확인하는 방법을 test를 통해 구현해 보세요.
            */

            Json::CharReaderBuilder builder;
            Json::CharReader* reader = builder.newCharReader();
            Json::Value root;
            std::string errors;

            bool result = reader->parse(response.c_str(), response.c_str() + response.size(), &root, &errors);
            delete reader;

            cout << root["message"].asString() << endl;

        } else if (userSelection == "13") {

            Json::Value root;

            root["message"] = "Easy to compose JSON string";

            cout << root["message"].asString() << endl;

            Json::StreamWriterBuilder jsonBuilder;
            std::string jsonStr = Json::writeString(jsonBuilder, root);
            cout << jsonStr << endl;

        } else if (userSelection == CHAT_WELCOME_ARRAY_JSON) {

            cout << getHttpRequestforArrayJson() << endl;

        } else if (userSelection == "22") {

            printArrayJson(getHttpRequestforArrayJson());

        } else if (userSelection == "23") {
        } else if (userSelection == CHAT_QUIT || userSelection == "quit" || userSelection =="Q") {
            break;
        } else {
            cout << "Wrong command" << endl;
        }
    } while(true);
}
