#ifndef LOGIN_RECEIVER_H_
#define LOGIN_RECEIVER_H_

#include <iostream>
#include "../cache.h"
#include "receiver.h"
#include "../../interface/dto/user/login_request.h"
#include "../../interface/dto/user/login_response.h"
// #include "../../interface/repository/user_repository.h"
#include "../../utils.h"

class LoginReceiver : public Receiver
{
public:
  LoginReceiver(Cache &cache) : Receiver(cache) {}

  void Action() override
  {
    std::string id = GetID();
    std::string password = GetPassword();
    AuthorizationKey key;
    key.setId(id);
    key.setPassword(password);
    LoginRequest request(id, key.queryNonce(), key.queryPasswordWithNonce());
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

    std::string id;
    std::cout << "Enter ID: ";
    std::cin >> id;
    return id;
  }

  std::string GetPassword()
  {
    if (cache_.GetValue(Cache::TEST_PASSWORD).length() > 0)
      return cache_.GetValue(Cache::TEST_PASSWORD);

    std::string password;
    std::cout << "Enter Password: ";
    std::cin >> password;
    return password;
  }
};

#endif
