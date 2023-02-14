#include <gtest/gtest.h>
#include "../src/command/command.h"
#include "../src/command/invoker.h"
#include "../src/command/receiver/login_receiver.h"
#include "../src/command/login.h"

using namespace std;

class CommandTestFixture : public ::testing::Test
{
protected:
  void SetUp() override
  {
    cache_.SetKV(Cache::TEST_ID, "fifo_274");
    cache_.SetKV(Cache::TEST_NONCE, "5");
    cache_.SetKV(Cache::TEST_PASSWORD, "password");

    invoker_ = std::make_unique<Invoker>(cache_);
    invoker_->SetOnInvoke(new Login(CommandType::kLogin, "Login", new LoginReceiver(cache_)));
  }

  void TearDown() override
  {
  }

  std::unique_ptr<Invoker> invoker_;
  Cache cache_;
};

TEST_F(CommandTestFixture, LoginTest)
{
  cache_.SetKV(Cache::SESSION_ID, "");
  invoker_->Invoke("51");

  ASSERT_GT(cache_.GetValue(Cache::SESSION_ID).length(), 0);
}
