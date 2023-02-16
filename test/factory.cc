#include <string>
#include <memory>

#include "gtest/gtest.h"
#include "../src/command/cache.h"
#include "../src/command/invoker.h"

#include "../src/command/quit.h"
#include "../src/command/parameter_validator.h"
#include "../src/command/factory/command_creator.h"

using namespace std;

#define CHAT_QUIT "q"
#define CHAT_LONG_QUIT "quit"

class FactoryTest : public testing::Test
{
protected:
    void SetUp() override
    {
        ParameterValidator validator(1, {});
        Cache cache;
        cache.SetBaseUrl(validator.GetBaseUrl());
        string base_url = cache.GetValue(Cache::vBaseUrl);

        invoker = make_unique<Invoker>(cache);
        MakeCommands(invoker, cache);
    }

    void MakeCommands(const unique_ptr<Invoker> &invoker, Cache &cache)
    {

        AnsiColor color;
        string base_url = cache.GetValue(Cache::vBaseUrl);
        invoker->SetOnInvoke(move(make_unique<Quit>(CHAT_QUIT, "Quit Application")));
        invoker->SetOnInvoke(move(make_unique<Quit>(CHAT_LONG_QUIT, "Quit Application")));

        try
        {
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
        catch (const InvalidCommandException &ex)
        {
            color.ImportantWithLineFeed(ex.what());
        }
    }

    unique_ptr<Invoker> invoker;
};

TEST_F(FactoryTest, DefaultConstructor)
{
    EXPECT_EQ(invoker->PrintCommands(), 8);
}