#include <memory>

#include "command/command.h"
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

#define CHAT_QUIT "q"
#define CHAT_LONG_QUIT "quit"

using namespace std;

int main(int argc, char *argv[])
{
    ParameterValidator validator(argc, argv);

    Cache cache;
    unique_ptr<Invoker> invoker = make_unique<Invoker>(cache);
    invoker->SetOnInvoke(make_unique<Quit>(CHAT_QUIT, "Quit Application").get());
    invoker->SetOnInvoke(make_unique<Quit>(CHAT_LONG_QUIT, "Quit Application").get());
    invoker->SetOnInvoke(make_unique<Login>(CommandType::kLogin, "Login", make_unique<LoginReceiver>(cache).get()).get());
    // invoker->SetOnInvoke(new Signup(CommandType::kSignup, "Signup", new Receiver()));
    //invoker->SetOnInvoke(new ListChatRooms(CommandType::kListRooms, "List Chat Rooms", new ListReceiver(cache)));
    //invoker->SetOnInvoke(new CreateChatRoom(CommandType::kCreateRoom, "Create Chat Room", new CreateReceiver(cache)));
    //invoker->SetOnInvoke(new JoinChatRoom(CommandType::kJoinRoom, "Join Chat Room", new JoinReceiver(cache)));

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
