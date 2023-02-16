#include <string>
#include <memory>
#include <random>

#include "gtest/gtest.h"
#include "../src/command/cache.h"
#include "../src/command/invoker.h"

#include "../src/command/quit.h"
#include "../src/command/parameter_validator.h"
#include "../src/command/factory/command_creator.h"

#include "../src/common/exception/command/invalid_command_exception.h"

using namespace std;

#define CHAT_QUIT "q"
#define CHAT_LONG_QUIT "quit"

random_device dev;
mt19937 rng(dev());
uniform_int_distribution<mt19937::result_type> dist1000(1, 1000);
static std::string id = "fifo_" + to_string(dist1000(rng));

class GothroughTest : public testing::Test
{
protected:
    void SetUp() override
    {
        ParameterValidator validator(1, {});
        cache_.SetBaseUrl(validator.GetBaseUrl());
        string base_url = cache_.GetValue(Cache::vBaseUrl);

        invoker_ = make_unique<Invoker>(cache_);

        cache_.SetTestID(id);
        cache_.SetTestPassword("password");
        cache_.SetTestNonce("5");
        cache_.SetSessionID("");
    }

    void MakeCommands()
    {
        AnsiColor color;
        string base_url = cache_.GetValue(Cache::vBaseUrl);
        invoker_->SetOnInvoke(move(make_unique<Quit>(CHAT_QUIT, "Quit Application")));
        invoker_->SetOnInvoke(move(make_unique<Quit>(CHAT_LONG_QUIT, "Quit Application")));

        try
        {
            const std::unique_ptr<CommandCreator> userCreator = make_unique<UserCommandCreator>(cache_);
            invoker_->SetOnInvoke(move(userCreator->CreateCommand(CommandType::kSignup, "Sign up for the program")));
            invoker_->SetOnInvoke(move(userCreator->CreateCommand(CommandType::kLogin, "Log in to the program")));
            invoker_->SetOnInvoke(move(userCreator->CreateCommand(CommandType::kLogout, "Log  out of the program")));

            invoker_->SetOnInvoke(move(userCreator->CreateCommand(CommandType::kWrongCommand, "Wrong Command Test")));

            const std::unique_ptr<CommandCreator> roomCreator = make_unique<RoomCommandCreator>(cache_);
            invoker_->SetOnInvoke(move(roomCreator->CreateCommand(CommandType::kListRooms, "List all rooms")));
            invoker_->SetOnInvoke(move(roomCreator->CreateCommand(CommandType::kCreateRoom, "Create a room")));

            invoker_->SetOnInvoke(move(roomCreator->CreateCommand(CommandType::kWrongCommand, "Wrong Command Test")));

            const std::unique_ptr<CommandCreator> chatCreator = make_unique<ChatCommandCreator>(cache_);
            invoker_->SetOnInvoke(move(chatCreator->CreateCommand(CommandType::kJoinRoom, "Join a room")));

            invoker_->SetOnInvoke(move(chatCreator->CreateCommand(CommandType::kWrongCommand, "Wrong Command Test")));
        }
        catch (const InvalidCommandException &ex)
        {
            color.ImportantWithLineFeed(ex.what());
        }
    }

    unique_ptr<Invoker> invoker_;
    Cache cache_;
};

TEST_F(GothroughTest, MakeCommandsTest)
{
    MakeCommands();
    EXPECT_EQ(invoker_->PrintCommands(), 8);
}

TEST_F(GothroughTest, NoCommandTest)
{
    MakeCommands();
    EXPECT_THROW(invoker_->Invoke("500"), InvalidCommandException);
}

TEST_F(GothroughTest, SignupTest)
{
    MakeCommands();
    EXPECT_NO_THROW(invoker_->Invoke("50"));
}

TEST_F(GothroughTest, SignupFailureTest)
{
    MakeCommands();
    EXPECT_THROW(invoker_->Invoke("50"), InvalidCommandException);
}

TEST_F(GothroughTest, LoginTest)
{
    MakeCommands();

    invoker_->Invoke("51");
    EXPECT_FALSE(cache_.GetValue(Cache::vSessionID).empty());
}

TEST_F(GothroughTest, LoginFailureTest)
{
    MakeCommands();

    cache_.SetTestID("thisidisnotexists_fifo");
    EXPECT_THROW(invoker_->Invoke("51"), InvalidCommandException);
}

TEST_F(GothroughTest, LogoutTest)
{
    MakeCommands();
    
    invoker_->Invoke("51");
    EXPECT_FALSE(cache_.GetValue(Cache::vSessionID).empty());

    invoker_->Invoke("52");
    EXPECT_TRUE(cache_.GetValue(Cache::vSessionID).empty());
}