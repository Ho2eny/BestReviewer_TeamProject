#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/command/command.h"
#include "../src/command/invoker.h"
#include "../src/command/cache.h"

#include "../src/command/receiver/signup_receiver.h"
#include "../src/command/receiver/login_receiver.h"
#include "../src/command/receiver/logout_receiver.h"
#include "../src/command/receiver/create_receiver.h"
#include "../src/command/receiver/list_receiver.h"

#include "../src/http/repository/user_http_repository.h"
#include "../src/http/repository/room_http_repository.h"

#include "../src/command/login.h"
#include "../src/command/signup.h"
#include "../src/command/createchatroom.h"
#include "../src/command/listchatrooms.h"
#include "../src/command/parameter_validator.h"
#include "../src/command/quit.h"

using namespace std;

class MockRoomRepository : public RoomRepository {
public:
  MOCK_METHOD(CreateRoomResponse, CreateRoom, (const CreateRoomRequest&), (override));
  MOCK_METHOD(RetrieveRoomResponse, RetrieveRoom, (const RetrieveRoomRequest&), (override));
};

class MockUserRepository : public UserRepository {
public:
  MOCK_METHOD(LoginResponse, Login, (const LoginRequest&), (override));
  MOCK_METHOD(SignupResponse, Signup, (const SignupRequest&), (override));
  MOCK_METHOD(LogoutResponse, Logout, (const LogoutRequest&), (override));
};

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
    invoker_ = make_unique<Invoker>(cache_);
    user_repo_ = make_shared<MockUserRepository>();
    room_repo_ = make_shared<MockRoomRepository>();
    invoker_->SetOnInvoke(move(make_unique<Login>(CommandType::kSignup, "Sign up for the program", move(make_unique<SignupReceiver>(cache_, user_repo_)))));
    invoker_->SetOnInvoke(move(make_unique<Login>(CommandType::kLogin, "Log in to the program", move(make_unique<LoginReceiver>(cache_, user_repo_)))));
    invoker_->SetOnInvoke(move(make_unique<Login>(CommandType::kLogout, "Log out of the program", move(make_unique<LogoutReceiver>(cache_, user_repo_)))));
    invoker_->SetOnInvoke(move(make_unique<CreateChatRoom>(CommandType::kCreateRoom, "Create Chat Room", move(make_unique<CreateReceiver>(cache_, room_repo_)))));
    invoker_->SetOnInvoke(move(make_unique<ListChatRooms>(CommandType::kListRooms, "List Chat Rooms", move(make_unique<ListReceiver>(cache_, room_repo_)))));
  }

  void TearDown() override
  {
  }

  std::unique_ptr<Invoker> invoker_;
  std::shared_ptr<MockUserRepository> user_repo_;
  std::shared_ptr<MockRoomRepository> room_repo_;
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

TEST_F(CommandTestFixture, CreateRoomTest)
{
  CreateRoomResponse kValidResponse = CreateRoomResponse();
  
  EXPECT_CALL(*room_repo_, CreateRoom(testing::_)).WillOnce(testing::Return(kValidResponse));
  cache_.SetSessionID("testsessionid");
  cache_.SetRoomName("testRoomName");
  invoker_->Invoke("60");
}