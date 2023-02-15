#include <memory>

#include "command/command.h"
#include "command/invoker.h"
#include "command/cache.h"

#include "command/receiver/signup_receiver.h"
#include "command/receiver/login_receiver.h"
#include "command/receiver/logout_receiver.h"

#include "http/repository/user_http_repository.h"
// #include "http/repository/chat_http_repository.h"

#include "command/receiver/create_receiver.h"
#include "command/receiver/join_receiver.h"
#include "command/receiver/list_receiver.h"
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

void MakeCommands(const unique_ptr<Invoker> &invoker, Cache &cache)
{
    string base_url = cache.GetValue(Cache::vBaseUrl);
    invoker->SetOnInvoke(move(make_unique<Quit>(CHAT_QUIT, "Quit Application")));
    invoker->SetOnInvoke(move(make_unique<Quit>(CHAT_LONG_QUIT, "Quit Application")));

    shared_ptr<UserHttpRepository> user_repo = make_shared<UserHttpRepository>(base_url);
    invoker->SetOnInvoke(move(make_unique<Login>(CommandType::kSignup, "Sign up for the program", move(make_unique<SignupReceiver>(cache, user_repo)))));
    invoker->SetOnInvoke(move(make_unique<Login>(CommandType::kLogin, "Log in to the program", move(make_unique<LoginReceiver>(cache, user_repo)))));
    invoker->SetOnInvoke(move(make_unique<Login>(CommandType::kLogout, "Log out of the program", move(make_unique<LogoutReceiver>(cache, user_repo)))));

    // shared_ptr<RoomHttpRepository> room_repo = make_shared<RoomHttpRepository>(base_url);
    // invoker->SetOnInvoke(move(make_unique<CreateChatRoom>(CommandType::kCreateRoom, "Create a room", move(make_unique<CreateReceiver>(cache, room_repo)))));
    // invoker->SetOnInvoke(move(make_unique<ListChatRooms>(CommandType::kListRooms, "List all rooms", move(make_unique<ListReceiver>(cache, room_repo)))));
    // invoker->SetOnInvoke(move(make_unique<JoinChatRoom>(CommandType::kJoinRoom, "Join a room", move(make_unique<JoinReceiver>(cache, room_repo)))));
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
    color.Title("===== FIFO Chat Client =====");
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
            color.ImportantWithLineFeed(ex.what());
        }
        catch (const GeneralNetworkException &ex)
        {
            color.ImportantWithLineFeed(ex.what());
        }

    } while (receive_commands);
}
