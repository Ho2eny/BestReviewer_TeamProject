#ifndef CACHE_H_
#define CACHE_H_

#include <map>
#include <string>

class Cache
{
public:
  static const std::string vID;
  static const std::string vTestID;
  static const std::string vTestNonce;
  static const std::string vTestPassword;
  static const std::string vBaseUrl;
  static const std::string vSessionID;

  void SetID(const std::string &ID) { SetKV(Cache::vID, ID); }
  void SetTestID(const std::string &ID) { SetKV(Cache::vTestID, ID); }
  void SetTestNonce(const std::string &nonce) { SetKV(Cache::vTestNonce, nonce); }
  void SetTestPassword(const std::string &password) { SetKV(Cache::vTestPassword, password); }
  void SetBaseUrl(const std::string &base_url) { SetKV(Cache::vBaseUrl, base_url); }
  void SetSessionID(const std::string &session_id) { SetKV(Cache::vSessionID, session_id); }

  std::string GetValue(const std::string &key) { return kv_[key]; }

private:
  void SetKV(const std::string &key, const std::string &value) { kv_[key] = value; }

  std::map<const std::string, std::string> kv_;
};

const std::string Cache::vID = "id";
const std::string Cache::vTestID = "test_id";
const std::string Cache::vTestNonce = "test_nonce";
const std::string Cache::vTestPassword = "test_password";
const std::string Cache::vBaseUrl = "base_url";
const std::string Cache::vSessionID = "session_id";

#endif
