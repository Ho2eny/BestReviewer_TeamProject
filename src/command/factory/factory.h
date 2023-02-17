#include "../command.h"
#include "../invoker.h"
#include "../cache.h"
#include "../quit.h"
#include "../parameter_validator.h"
#include "../factory/command_creator.h"

#define CHAT_QUIT "q"
#define CHAT_LONG_QUIT "quit"

class Factory
{
public:
    void MakeCommands(const unique_ptr<Invoker> &invoker, Cache &cache)
    {

        AnsiColor color;
        string base_url = cache.GetValue(Cache::vBaseUrl);
        invoker->SetOnInvoke(move(make_unique<Quit>(CHAT_QUIT, "Quit Application")));
        invoker->SetOnInvoke(move(make_unique<Quit>(CHAT_LONG_QUIT, "Quit Application")));
        
        const std::unique_ptr<CommandCreator> userCreator = make_unique<UserCommandCreator>(cache);
        invoker->SetOnInvoke(move(userCreator->CreateCommand(CommandType::kSignup, "Sign up for the program")));
        invoker->SetOnInvoke(move(userCreator->CreateCommand(CommandType::kLogin, "Log in to the program")));
        invoker->SetOnInvoke(move(userCreator->CreateCommand(CommandType::kLogout, "Log  out of the program")));

        const std::unique_ptr<CommandCreator> roomCreator = make_unique<RoomCommandCreator>(cache);
        invoker->SetOnInvoke(move(roomCreator->CreateCommand(CommandType::kListRooms, "List all rooms")));
        invoker->SetOnInvoke(move(roomCreator->CreateCommand(CommandType::kCreateRoom, "Create a room")));

        const std::unique_ptr<CommandCreator> chatCreator = make_unique<ChatCommandCreator>(cache);
        invoker->SetOnInvoke(move(chatCreator->CreateCommand(CommandType::kJoinRoom, "Join a room")));
    }
};