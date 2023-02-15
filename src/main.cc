#include <iostream>
#include <curl/curl.h>
#include <json/json.h>
#include <bits/stdc++.h>

#include "command/command.h"
#include "command/invoker.h"
#include "command/cache.h"
#include "command/receiver/login_receiver.h"
#include "command/login.h"
#include "command/signup.h"
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

    AnsiColor color;
    color.Title("===== Mini Chat Client =====");
    invoker->PrintCommands();
    bool receive_commands = true;

    do
    {
        string baseUrl = validator.GetBaseUrl();
        string userSelection;
        color.Text("\n> Waiting for a command... : ");
        cin >> userSelection;

        try
        {
            receive_commands = invoker->Invoke(userSelection);
        }
        catch (InvalidCommandException)
        {
            color.ImportantWithLineFeed("Command Not Found");
        }

    } while (receive_commands);
}
