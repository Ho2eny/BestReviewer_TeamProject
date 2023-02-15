#include <iostream>
#include <curl/curl.h>
#include <json/json.h>
#include <bits/stdc++.h>
#include "common/exception/base_exception.h"
#include "hardtoname.h"
#include "command/invoker.h"
#include "command/cache.h"
#include "command/receiver/login_receiver.h"
#include "command/login.h"
#include "command/signup.h"
#include "command/parameter_validator.h"
#include "command/quit.h"
#include "command/createchatroom.h"
#include "command/joinchatroom.h"
#include "command/listchatrooms.h"

#include "http_client.h"

#define CHAT_QUIT "q"
#define CHAT_LONG_QUIT "quit"

using namespace std;

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

    invoker->PrintCommands();
    bool receive_commands = true;

    do
    {
        string baseUrl = validator.GetBaseUrl();
        string userSelection;
        cin >> userSelection;

        try
        {
            receive_commands = invoker->Invoke(userSelection);
        }
        catch (invalid_argument)
        {
            cout << "Command Not Found" << endl;
        }

    } while (receive_commands);
}
