#ifndef CACHE_H_
#define CACHE_H_

#include <map>
#include <vector>
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
  static const std::string vTestSessionID;
  static const std::string vChatRoomName;
  static const std::string vTestChatRoomName;

  void SetID(const std::string &ID);
  void SetTestID(const std::string &ID);
  void SetTestNonce(const std::string &nonce);
  void SetTestPassword(const std::string &password);
  void SetBaseUrl(const std::string &base_url);
  void SetSessionID(const std::string &session_id);
  void SetRoomName(const std::string &room_name);
  void SetTestRoomName(const std::string &room_name);
  void RemoveSessionID();
  std::string GetValue(const std::string &key);
  void SetRooms(const std::vector<std::string> &rooms);
  std::vector<std::string> GetRooms();

private:
  void SetKV(const std::string &key, const std::string &value) { kv_[key] = value; }

  std::map<const std::string, std::string> kv_;
  std::vector<std::string> rooms_;
};

#endif
