#include <iostream>
#include <curl/curl.h>
#include <json/json.h>
#include <bits/stdc++.h>
#include "common/exception/base_exception.h"
#include "hardtoname.h"
#include "command/invoker.h"
#include "command/receiver.h"
#include "command/login.h"
#include "command/signup.h"
#include "command/parameter_validator.h"
#include "http_client.h"

#define CHAT_QUIT "q"

using namespace std;

static Invoker *invoker = new Invoker;

int main(int argc, char *argv[])
{
    ParameterValidator validator(argc, argv);

    invoker->SetOnInvoke(new Login(CommandType::kLogin, "Login", new Receiver()));
    invoker->SetOnInvoke(new Signup(CommandType::kSignup, "Signup", new Receiver()));

    try
    {
        string baseUrl = validator.GetBaseUrl();
        string userSelection;

        do
        {
            invoker->PrintCommands();
            cin >> userSelection;

            Json::Value data;
            data["message"] = "Easy to compose JSON string";
            invoker->Invoke(userSelection, data);

        } while (true);
    }
    catch (BaseException *exception)
    {
        cout << exception->what() << endl;
    }
}
