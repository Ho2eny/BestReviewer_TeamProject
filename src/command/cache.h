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

  void SetID(const std::string &ID) { SetKV(Cache::vID, ID); }
  void SetTestID(const std::string &ID) { SetKV(Cache::vTestID, ID); }
  void SetTestNonce(const std::string &nonce) { SetKV(Cache::vTestNonce, nonce); }
  void SetTestPassword(const std::string &password) { SetKV(Cache::vTestPassword, password); }
  void SetBaseUrl(const std::string &base_url) { SetKV(Cache::vBaseUrl, base_url); }
  void SetSessionID(const std::string &session_id) { SetKV(Cache::vSessionID, session_id); }
  void SetRoomName(const std::string &room_name) { SetKV(Cache::vChatRoomName, room_name); }
  void RemoveSessionID() { SetKV(Cache::vSessionID, ""); }
  std::string GetValue(const std::string &key) { return kv_[key]; }
  void SetRooms(const std::vector<std::string> &rooms) { rooms_ = rooms; }
  std::vector<std::string> GetRooms() { return rooms_; }

private:
  void SetKV(const std::string &key, const std::string &value) { kv_[key] = value; }

  std::map<const std::string, std::string> kv_;
  std::vector<std::string> rooms_;
};

const std::string Cache::vID = "id";
const std::string Cache::vTestID = "test_id";
const std::string Cache::vTestNonce = "test_nonce";
const std::string Cache::vTestPassword = "test_password";
const std::string Cache::vBaseUrl = "base_url";
const std::string Cache::vSessionID = "session_id";
const std::string Cache::vTestSessionID = "test_session_id";
const std::string Cache::vChatRoomName = "chat_room_name";
const std::string Cache::vTestChatRoomName = "test_chat_room_name";

#endif
