#ifndef LOGOUT_RECEIVER_H_
#define LOGOUT_RECEIVER_H_

#include <iostream>
#include "../cache.h"
#include "receiver.h"
#include "../../interface/dto/user/login_request.h"
#include "../../interface/dto/user/login_response.h"
// #include "../../interface/repository/user_repository.h"
#include "../../utils.h"

class LogoutReceiver : public Receiver
{
public:
  LogoutReceiver(Cache &cache) : Receiver(cache) {}

  void Action() override
  {
    AuthorizationKey key;
    key.setId(GetID());
    key.setPassword(GetPassword());

    // LogoutRequest request(id, key.queryNonce(), key.queryPasswordWithNonce());
    // Waiting for the implementatino from in.heo
    // UserHttpRepository repository(cache.GetValue(Cache::vBaseUrl));
    // LoginResponse response = repository.Login(request);
    // cache_.SetKV(Cache::vSessionID, response.Get...);
  }
};

#endif
