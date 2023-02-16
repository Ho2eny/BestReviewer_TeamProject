#include <memory>

#include "command/command.h"
#include "command/invoker.h"
#include "command/cache.h"

#include "command/quit.h"
#include "command/parameter_validator.h"
#include "command/factory/command_creator.h"

#define CHAT_QUIT "q"
#define CHAT_LONG_QUIT "quit"

using namespace std;

void MakeCommands(const unique_ptr<Invoker> &invoker, Cache &cache)
{

    AnsiColor color;
    string base_url = cache.GetValue(Cache::vBaseUrl);
    invoker->SetOnInvoke(move(make_unique<Quit>(CHAT_QUIT, "Quit Application")));
    invoker->SetOnInvoke(move(make_unique<Quit>(CHAT_LONG_QUIT, "Quit Application")));

    try {
        const std::unique_ptr<CommandCreator> userCreator = make_unique<UserCommandCreator>(cache);
        invoker->SetOnInvoke(move(userCreator->CreateCommand(CommandType::kSignup, "Sign up for the program")));
        invoker->SetOnInvoke(move(userCreator->CreateCommand(CommandType::kLogin, "Log in to the program")));
        invoker->SetOnInvoke(move(userCreator->CreateCommand(CommandType::kLogout, "Log  out of the program")));

        const std::unique_ptr<CommandCreator> roomCreator = make_unique<RoomCommandCreator>(cache);
        invoker->SetOnInvoke(move(roomCreator->CreateCommand(CommandType::kListRooms, "List all rooms")));
        invoker->SetOnInvoke(move(roomCreator->CreateCommand(CommandType::kCreateRoom, "Create a room")));
        invoker->SetOnInvoke(move(roomCreator->CreateCommand(CommandType::kJoinRoom, "Join a room")));
    }
    catch (const InvalidCommandException& ex) 
    {
        color.ImportantWithLineFeed(ex.what());
    }
}

int main(int argc, char *argv[])
{
    ParameterValidator validator(argc, argv);
    string base_url = validator.GetBaseUrl();

    Cache cache;
    cache.SetBaseUrl(base_url);

    unique_ptr<Invoker> invoker = make_unique<Invoker>(cache);
    MakeCommands(invoker, cache);

    AnsiColor color;
    color.Title("======================================");
    color.Title("========== FIFO Chat Client ==========");
    color.Title("======================================");
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
        catch (const InvalidCommandException &ex)
        {
            color.ErrorWithLineFeed(ex.what());
        }
        catch (const BaseException &ex)
        {
            color.ErrorWithLineFeed(ex.what());
        }

    } while (receive_commands);

    color.Title("======================================");
}
