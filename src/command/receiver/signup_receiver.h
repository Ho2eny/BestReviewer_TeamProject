#ifndef SIGNUP_RECEIVER_H_
#define SIGNUP_RECEIVER_H_

#include <iostream>
#include "../cache.h"
#include "../../utils.h"
#include "user_receiver.h"

class SignupReceiver : public UserReceiver
{
public:
  SignupReceiver(Cache &cache, std::shared_ptr<UserRepository> repository) : UserReceiver(cache, repository) {}

  void Action() override
  {
    std::string id = GetId();
    std::string password = GetPassword();
    AuthorizationKey key(id, password);

    SignupRequest request(id, key.QueryPassword());
    SignupResponse response = repository_->Signup(request);

    AnsiColor color;
    color.TextWithLineFeed("Signed up to FIFO Chat with " + id);
  }
};

#endif
