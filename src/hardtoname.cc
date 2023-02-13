#include <iostream>
#include <curl/curl.h>
#include <json/json.h>

using namespace std;

static size_t curl_callback(void *contents, size_t size, size_t nmemb, void *userp) {
	char* str = static_cast<char*>(contents);
	size_t realsize = size * nmemb;
	string& res = *(static_cast<std::string*>(userp));
	res.append(str, realsize);
	return realsize;
}

string getHttpRequestforArrayJson(void) {
    string resultOfGetRequest;
    CURL *curl;

    long responseCode;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:34568/chat/welcome_arrayJson");
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resultOfGetRequest);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        resultOfGetRequest.append("error response : ").append(to_string(res));
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return resultOfGetRequest;
}

void printArrayJson(string arrayJson) {

    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();
    Json::Value root;
    std::string errors;

    bool result = reader->parse(arrayJson.c_str(), arrayJson.c_str() + arrayJson.size(), &root, &errors);
    delete reader;

    for ( int index = 0; index < root.size(); ++index ) {
        cout << root[index] << endl;
        cout << "detailed message with forLoop: " << root[index]["message"].asString() << endl;
    }

    for( Json::Value::const_iterator itr = root.begin() ; itr != root.end() ; itr++ ) {
        cout << itr.key() << ": " << *itr << endl;
        cout << "detailed message with ItrLoop: " << (*itr)["message"].asString() << endl;
    }
}