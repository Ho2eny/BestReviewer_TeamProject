#include <iostream>
#include <curl/curl.h>
#include <json/json.h>
#include "hardtoname.h"
#include "command/invoker.h"
#include "command/command.h"
#include "command/receiver.h"

#define CHAT_WELCOME_SIMPLE_JSON "11"
#define CHAT_PARSE_SIMPLE_JSON "12"
#define CHAT_WELCOME_ARRAY_JSON "21"
#define CHAT_QUIT "q"

using namespace std;

static size_t curl_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    char *str = static_cast<char *>(contents);
    size_t realsize = size * nmemb;
    string &res = *(static_cast<std::string *>(userp));
    res.append(str, realsize);
    return realsize;
}

int main(int argc, char *argv[])
{
    // Command Pattern Test Code
    Invoker *invoker = new Invoker;
    invoker->SetOnInvoke(new SimpleWelcomeCommand(CHAT_WELCOME_SIMPLE_JSON, "welcome_simpleJson"));
    invoker->SetOnInvoke(new ChatParseSimpleJsonCommand(CHAT_PARSE_SIMPLE_JSON, "parse json"));
    invoker->SetOnInvoke(new JsonComposeCommand("13", "assemble json", new Receiver(Json::objectValue)));

    /*
    if (argc != 3) {
        cout << "usage: chat_client.exe localhost 34568" << endl;
        return 0;
    }*/

    string userSelection;
    string response;

    do
    {
        invoker->PrintCommands();

        cout << "21.welcome_arrayJson, 22.parse json, 33.assemble json" << endl;
        cout << "Enter command(q for quit) : ";
        cin >> userSelection;

        // 아래 부분은 그냥 원본의 나머지입니다. 모두 삭제되고 요구사항의 커맨드로 대체되어야 합니다.
        if (userSelection == CHAT_WELCOME_ARRAY_JSON)
        {

            cout << getHttpRequestforArrayJson() << endl;
        }
        else if (userSelection == "22")
        {

            printArrayJson(getHttpRequestforArrayJson());
        }
        else if (userSelection == "23")
        {
        }
        else if (userSelection == CHAT_QUIT || userSelection == "quit" || userSelection == "Q")
        {
            break;
        }
        else
        {
            Json::Value data;
            data["message"] = "Easy to compose JSON string";
            invoker->Invoke(userSelection, data);
        }
    } while (true);
}
