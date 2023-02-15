#include <gtest/gtest.h>
#include "../src/command/command.h"
#include "../src/command/invoker.h"
#include "../src/command/cache.h"

#include "../src/command/receiver/signup_receiver.h"
#include "../src/command/receiver/login_receiver.h"
#include "../src/command/receiver/logout_receiver.h"

#include "../src/plugin/curl/repository/user_http_repository.h"

#include "../src/command/login.h"
#include "../src/command/signup.h"
#include "../src/command/parameter_validator.h"
#include "../src/command/quit.h"

using namespace std;

class CommandTestFixture : public ::testing::Test
{
protected:
  void SetUp() override
  {
    ParameterValidator validator(1, {});
    string base_url = validator.GetBaseUrl();
    cache_.SetBaseUrl(base_url);

    cache_.SetTestID("fifo_274");
    cache_.SetTestNonce("5");
    cache_.SetTestPassword("password");

    invoker_ = make_unique<Invoker>(cache_);
    shared_ptr<UserHttpRepository> user_repo = make_shared<UserHttpRepository>(base_url);
    invoker_->SetOnInvoke(move(make_unique<Login>(CommandType::kSignup, "Sign up for the program", move(make_unique<SignupReceiver>(cache_, user_repo)))));
    invoker_->SetOnInvoke(move(make_unique<Login>(CommandType::kLogin, "Log in to the program", move(make_unique<LoginReceiver>(cache_, user_repo)))));
    invoker_->SetOnInvoke(move(make_unique<Login>(CommandType::kLogout, "Log out of the program", move(make_unique<LogoutReceiver>(cache_, user_repo)))));
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

  if (cache_.GetValue(Cache::vSessionID).length())
  {
    // TODO: Signup
    invoker_->Invoke("50");
  }

  ASSERT_GT(cache_.GetValue(Cache::vSessionID).length(), 0);
}
