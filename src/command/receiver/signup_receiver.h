#ifndef SIGNUP_RECEIVER_H_
#define SIGNUP_RECEIVER_H_

#include <iostream>
#include "../cache.h"
#include "receiver.h"
#include "../../interface/dto/user/login_request.h"
#include "../../interface/dto/user/login_response.h"
// #include "../../interface/repository/user_repository.h"
#include "../../utils.h"

class SignupReceiver : public Receiver
{
public:
  SignupReceiver(Cache &cache) : Receiver(cache) {}

  void Action() override
  {
    AuthorizationKey key;
    key.setId(GetID());
    key.setPassword(GetPassword());
    // SignupRequest request(id, key.queryPassword());
    // Waiting for the implementatino from in.heo
    // UserHttpRepository repository(cache.GetValue(Cache::BASE_URL));
    // LoginResponse response = repository.Login(request);
    // cache_.SetKV(Cache::SESSION_ID, response.Get...);
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
