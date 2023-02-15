#ifndef USER_HTTP_REPOSITORY_H_
#define USER_HTTP_REPOSITORY_H_

#include <memory>
#include <string>

#include "../../interface/repository/user_repository.h"
#include "../converter/user_dto_converter.h"
#include "../http_plugin.h"

class UserHttpRepository : public UserRepository {
public:
  UserHttpRepository(std::string base_url);

  virtual LoginResponse Login(const LoginRequest& request) override;

  virtual SignupResponse Signup(const SignupRequest& request) override;

  virtual LogoutResponse Logout(const LogoutRequest& request) override;

  void SetHttpClient(const std::shared_ptr<HttpPlugin>& client);

private:
  void Initialize();

  std::shared_ptr<HttpPlugin> http_client_;
  std::shared_ptr<UserDtoConverter> user_dto_converter_;
  std::string base_url_;
};

#endif