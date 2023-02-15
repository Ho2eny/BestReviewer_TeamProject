#include <iostream>
#include <curl/curl.h>
#include <json/json.h>
#include <bits/stdc++.h>
#include "common/exception/base_exception.h"
#include "hardtoname.h"
#include "command/invoker.h"
#include "command/cache.h"
#include "command/receiver/login_receiver.h"
#include "command/receiver/create_receiver.h"
#include "command/receiver/join_receiver.h"
#include "command/receiver/list_receiver.h"
#include "command/login.h"
#include "command/signup.h"
#include "command/createchatroom.h"
#include "command/joinchatroom.h"
#include "command/listchatrooms.h"
#include "command/parameter_validator.h"
#include "command/quit.h"
#include "http_client.h"

#define CHAT_QUIT "q"
#define CHAT_LONG_QUIT "quit"

using namespace std;

int main(int argc, char *argv[])
{
    ParameterValidator validator(argc, argv);
  
    Cache cache;  
    Invoker *invoker = new Invoker(cache);
    invoker->SetOnInvoke(new Quit(CHAT_QUIT, "Quit Application"));
    invoker->SetOnInvoke(new Quit(CHAT_LONG_QUIT, "Quit Application"));
    invoker->SetOnInvoke(new Login(CommandType::kLogin, "Login", new LoginReceiver(cache)));
    // invoker->SetOnInvoke(new Signup(CommandType::kSignup, "Signup", new Receiver()));
    //invoker->SetOnInvoke(new ListChatRooms(CommandType::kListRooms, "List Chat Rooms", new ListReceiver(cache)));
    //invoker->SetOnInvoke(new CreateChatRoom(CommandType::kCreateRoom, "Create Chat Room", new CreateReceiver(cache)));
    //invoker->SetOnInvoke(new JoinChatRoom(CommandType::kJoinRoom, "Join Chat Room", new JoinReceiver(cache)));

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
