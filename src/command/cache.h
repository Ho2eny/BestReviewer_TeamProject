#ifndef CACHE_H_
#define CACHE_H_

#include <map>
#include <string>

class Cache
{
public:
  static const std::string ID;
  static const std::string TEST_ID;
  static const std::string TEST_NONCE;
  static const std::string TEST_PASSWORD;
  static const std::string BASE_URL;
  static const std::string SESSION_ID;

  void SetKV(const std::string& key, const std::string& value)
  {
    kv_[key] = value;
  }

  std::string GetValue(const std::string& key) const
  {
    return kv_.find(key)->second;
  }

private:
  std::map<const std::string, std::string> kv_;
};

const std::string Cache::ID = "id";
const std::string Cache::TEST_ID = "test_id";
const std::string Cache::TEST_NONCE = "test_nonce";
const std::string Cache::TEST_PASSWORD = "test_password";
const std::string Cache::BASE_URL = "base_url";
const std::string Cache::SESSION_ID = "session_id";

#endif
