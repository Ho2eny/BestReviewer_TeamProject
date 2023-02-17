#ifndef SIGNUP_REQUEST_H_
#define SIGNUP_REQUEST_H_

#include <string>
#include <vector>

#include "../base_request.h"
#include "../../../common/exception/user/invalid_id_password_exception.h"

class SignupRequest : public BaseRequest {
public:
  SignupRequest() {}
  SignupRequest(std::string id, std::string password) : id_(id), password_(password) {
    if (!ValidateIdPassword(id, password)) {
      throw InvalidIdPasswordException("Id or Password is not invalid");
    }
  }

  std::string GetId() const;
  std::string GetPassword() const;

private:
  bool ValidateIdPassword(const std::string& id, const std::string& password) const;
  bool ValidateId(const std::string& id) const;
  bool ValidatePassword(const std::string& password) const;

  std::string id_;
  std::string password_;
};

inline std::string SignupRequest::GetId() const {
  return id_;
}

inline std::string SignupRequest::GetPassword() const {
  return password_;
}

inline bool SignupRequest::ValidateIdPassword(const std::string& id, const std::string& password) const {
  return ValidateId(id) && ValidatePassword(password);
}

inline bool SignupRequest::ValidateId(const std::string& id) const {
  std::vector<std::string> prohibited_character = { ",", "|" };

  for (const auto& character : prohibited_character) {
    if (id.find(character) != std::string::npos)
      return false;
  }

  return true;
}

inline bool SignupRequest::ValidatePassword(const std::string& password) const {
  std::vector<std::string> prohibited_character = { "," };

  for (const auto& character : prohibited_character) {
    if (password.find(character) != std::string::npos)
      return false;
  }

  return true;
}

#endif