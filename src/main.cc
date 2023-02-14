#include <iostream>
#include <curl/curl.h>
#include <json/json.h>
#include <bits/stdc++.h>
#include "hardtoname.h"
#include "command/invoker.h"
#include "command/receiver.h"
#include "command/login.h"
#include "command/signup.h"
#include "command/createchatroom.h"
#include "command/joinchatroom.h"
#include "command/listchatrooms.h"

#include "http_client.h"

#define CHAT_WELCOME_SIMPLE_JSON "11"
#define CHAT_PARSE_SIMPLE_JSON "12"
#define CHAT_WELCOME_ARRAY_JSON "21"
#define CHAT_QUIT "q"

using namespace std;

// 참고: 공용 Server : http://10.241.14.74
std::string server = "http://10.241.114.152";
std::string port = "34568";

// void paramter_handler(int argc, char *argv[])
// {
//     if (argc > 1)
//     {
//         server = argv[1];
//     }

//     regex ipv4("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");

//     if (regex_match(server, ipv4))
//         std::cout << "Valid IPv4" << std::endl;
// }

int main(int argc, char *argv[])
{

    // paramter_handler(argc, argv);
    // Command Pattern Test Code
    Invoker *invoker = new Invoker;
    invoker->SetOnInvoke(new Signup(CommandType::kSignup, "Signup", new Receiver()));
    invoker->SetOnInvoke(new Login(CommandType::kLogin, "Login", new Receiver()));
    invoker->SetOnInvoke(new ListChatRooms(CommandType::kListRooms, "List Chat Rooms", new Receiver()));
    invoker->SetOnInvoke(new CreateChatRoom(CommandType::kCreateRoom, "Create Chat Room", new Receiver()));
    invoker->SetOnInvoke(new JoinChatRoom(CommandType::kJoinRoom, "Join Chat Room", new Receiver()));

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
        cin >> userSelection;

        Json::Value data;
        data["message"] = "Easy to compose JSON string";
        invoker->Invoke(userSelection, data);

    } while (true);
}
