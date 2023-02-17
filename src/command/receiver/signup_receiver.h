#ifndef SIGNUP_RECEIVER_H_
#define SIGNUP_RECEIVER_H_

#include <iostream>
#include "../cache.h"
#include "../../utils.h"
#include "user_receiver.h"
#include "../../common/exception/user/fail_signup_exception.h"
#include "../../common/exception/user/invalid_id_password_exception.h"

class SignupReceiver : public UserReceiver
{
public:
  SignupReceiver(Cache &cache, std::shared_ptr<UserRepository> repository) : UserReceiver(cache, repository) {}

  void Action() override
  {
    AnsiColor color;

    std::string id = GetId();
    std::string password = GetPassword();
    AuthorizationKey key(id, password);

    SignupRequest request(id, key.QueryPassword());
    try
    {
      SignupResponse response = repository_->Signup(request);
      color.TextWithLineFeed("Signed up to FIFO Chat with " + id);
    }
    catch (const FailSignupException &ex)
    {
      throw InvalidCommandException(ex.what());
    }
    catch (const InvalidIdPasswordException &ex)
    {
      throw InvalidCommandException(ex.what());
    }
  }
};

#endif
