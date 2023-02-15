#ifndef LOGIN_RECEIVER_H_
#define LOGIN_RECEIVER_H_

#include <iostream>
#include "../cache.h"
#include "receiver.h"
#include "../../interface/dto/user/login_request.h"
#include "../../interface/dto/user/login_response.h"
// #include "../../interface/repository/user_repository.h"
#include "../../utils.h"
#include "../../ui_helper/ansi_color.h"

class LoginReceiver : public Receiver
{
public:
  LoginReceiver(Cache &cache) : Receiver(cache) {}

  void Action() override
  {
    std::string id = GetID();
    std::string password = GetPassword();
    AuthorizationKey key;
    key.SetId(id);
    key.SetPassword(password);

    LoginRequest request(id, key.QueryNonce(), key.QueryPasswordWithNonce());
    // Waiting for the implementatino from in.heo
    // UserHttpRepository repository(cache.GetValue(Cache::BASE_URL));
    // LoginResponse response = repository.Login(request);
    // cache_.SetKV(Cache::SESSION_ID, response.Get...);
    cache_.SetKV(Cache::ID, id);
    cache_.SetKV(Cache::SESSION_ID, "test_session_id");
  }

  std::string GetID()
  {
    if (cache_.GetValue(Cache::TEST_ID).length() > 0)
      return cache_.GetValue(Cache::TEST_ID);

    AnsiColor color;
    std::string id;
    color.Important("> Enter ID : ");
    std::cin >> id;
    return id;
  }

  std::string GetPassword()
  {
    if (cache_.GetValue(Cache::TEST_PASSWORD).length() > 0)
      return cache_.GetValue(Cache::TEST_PASSWORD);

    AnsiColor color;
    std::string password;
    color.Important("> Enter Password: ");
    std::cin >> password;
    return password;
  }
};

#endif
