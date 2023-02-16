#include <string>
#include <memory>
#include <random>

#include "gtest/gtest.h"
#include "../src/command/factory/factory.h"
#include "../src/common/exception/command/invalid_command_exception.h"

using namespace std;

#define CHAT_QUIT "q"
#define CHAT_LONG_QUIT "quit"

random_device dev;
mt19937 rng(dev());
<<<<<<< HEAD
uniform_int_distribution<mt19937::result_type> dist(1, 100000);
static std::string id = "fifo_" + to_string(dist(rng));
=======
uniform_int_distribution<mt19937::result_type> dist1000(1, 1000);
static std::string id = "fifo_" + to_string(dist1000(rng));
static std::string chatName = "fifo_chatRoom_" + to_string(dist1000(rng));
>>>>>>> 616aa455e55e084ea2294e99311beca4b71a5e7b

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
<<<<<<< HEAD

        Factory factory;
        factory.MakeCommands(invoker_, cache_);
    }

    unique_ptr<Invoker>
        invoker_;
=======
        cache_.SetTestRoomName(chatName);
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

            const std::unique_ptr<CommandCreator> roomCreator = make_unique<RoomCommandCreator>(cache_);
            invoker_->SetOnInvoke(move(roomCreator->CreateCommand(CommandType::kListRooms, "List all rooms")));
            invoker_->SetOnInvoke(move(roomCreator->CreateCommand(CommandType::kCreateRoom, "Create a room")));

            const std::unique_ptr<CommandCreator> chatCreator = make_unique<ChatCommandCreator>(cache_);
            invoker_->SetOnInvoke(move(chatCreator->CreateCommand(CommandType::kJoinRoom, "Join a room")));

        }
        catch (const InvalidCommandException &ex)
        {
            color.ImportantWithLineFeed(ex.what());
        }
    }

    unique_ptr<Invoker> invoker_;
>>>>>>> 616aa455e55e084ea2294e99311beca4b71a5e7b
    Cache cache_;
};

TEST_F(GothroughTest, MakeCommandsTest)
{
    EXPECT_EQ(invoker_->PrintCommands(), 8);
}

TEST_F(GothroughTest, MakeWrongCommandTest)
{
    const std::unique_ptr<CommandCreator> userCreator = make_unique<UserCommandCreator>(cache_);
    EXPECT_THROW(
        invoker_->SetOnInvoke(move(userCreator->CreateCommand(CommandType::kWrongCommand, "Wrong Command Test"))),
        InvalidCommandException);
}

TEST_F(GothroughTest, NoCommandTest)
{

    EXPECT_THROW(invoker_->Invoke("500"), InvalidCommandException);
}

TEST_F(GothroughTest, SignupTest)
{
    EXPECT_NO_THROW(invoker_->Invoke("50"));
}

TEST_F(GothroughTest, SignupFailureTest)
{

    EXPECT_THROW(invoker_->Invoke("50"), InvalidCommandException);
}

TEST_F(GothroughTest, LoginTest)
{

    invoker_->Invoke("51");
    EXPECT_FALSE(cache_.GetValue(Cache::vSessionID).empty());
}

TEST_F(GothroughTest, LoginFailureTest)
{

    cache_.SetTestID("thisidisnotexists_fifo");
    EXPECT_THROW(invoker_->Invoke("51"), InvalidCommandException);
}

TEST_F(GothroughTest, LogoutTest)
{

    invoker_->Invoke("51");
    EXPECT_FALSE(cache_.GetValue(Cache::vSessionID).empty());

    invoker_->Invoke("52");
    EXPECT_TRUE(cache_.GetValue(Cache::vSessionID).empty());
}

<<<<<<< HEAD
TEST_F(GothroughTest, quit)
{
    EXPECT_FALSE(invoker_->Invoke("Q"));
    EXPECT_FALSE(invoker_->Invoke("quit"));
    EXPECT_FALSE(invoker_->Invoke("q"));
}
=======
TEST_F(GothroughTest, CreateChatRoomTest)
{
    MakeCommands();
    
    invoker_->Invoke("51");
    EXPECT_FALSE(cache_.GetValue(Cache::vSessionID).empty());

    invoker_->Invoke("61");
    EXPECT_FALSE(cache_.GetValue(Cache::vChatRoomName).empty());
}

TEST_F(GothroughTest, ListChatRoomTest)
{
    MakeCommands();
    
    invoker_->Invoke("51");
    EXPECT_FALSE(cache_.GetValue(Cache::vSessionID).empty());

    invoker_->Invoke("60");
    EXPECT_FALSE(cache_.GetRooms().empty());
}
>>>>>>> 616aa455e55e084ea2294e99311beca4b71a5e7b
