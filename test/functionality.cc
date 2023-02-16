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
uniform_int_distribution<mt19937::result_type> dist(1, 100000);
static std::string id = "fifo_" + to_string(dist(rng));
static std::string chat_name = "fifo_chatRoom_" + to_string(dist(rng));

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
        cache_.SetTestRoomName(chat_name);

        Factory factory;
        factory.MakeCommands(invoker_, cache_);
    }

    unique_ptr<Invoker>
        invoker_;
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

TEST_F(GothroughTest, quit)
{
    EXPECT_FALSE(invoker_->Invoke("Q"));
    EXPECT_FALSE(invoker_->Invoke("quit"));
    EXPECT_FALSE(invoker_->Invoke("q"));
}

TEST_F(GothroughTest, CreateChatRoomTest)
{   
    invoker_->Invoke("51");
    EXPECT_FALSE(cache_.GetValue(Cache::vSessionID).empty());

    invoker_->Invoke("61");
    EXPECT_FALSE(cache_.GetValue(Cache::vChatRoomName).empty());
}

TEST_F(GothroughTest, CreateChatRoomFailureTest)
{
    EXPECT_THROW(invoker_->Invoke("61"), InvalidCommandException);
}

TEST_F(GothroughTest, ListChatRoomTest)
{     
    invoker_->Invoke("51");
    EXPECT_FALSE(cache_.GetValue(Cache::vSessionID).empty());

    invoker_->Invoke("60");
    EXPECT_FALSE(cache_.GetRooms().empty());
}
