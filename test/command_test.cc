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
    cache_.SetTestID("fifo_274");
    cache_.SetTestNonce("5");
    cache_.SetTestPassword("password");

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
  cache_.SetSessionID("");
  invoker_->Invoke("51");

  if(cache_.GetValue(Cache::vSessionID).length())
  {
    // TODO: Signup 
    invoker_->Invoke("50");
  }

  ASSERT_GT(cache_.GetValue(Cache::vSessionID).length(), 0);
}
