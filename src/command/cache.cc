#include "cache.h"

void Cache::SetID(const std::string &ID) { SetKV(Cache::vID, ID); }
void Cache::SetTestID(const std::string &ID) { SetKV(Cache::vTestID, ID); }
void Cache::SetTestNonce(const std::string &nonce) { SetKV(Cache::vTestNonce, nonce); }
void Cache::SetTestPassword(const std::string &password) { SetKV(Cache::vTestPassword, password); }
void Cache::SetBaseUrl(const std::string &base_url) { SetKV(Cache::vBaseUrl, base_url); }
void Cache::SetSessionID(const std::string &session_id) { SetKV(Cache::vSessionID, session_id); }
void Cache::SetRoomName(const std::string &room_name) { SetKV(Cache::vChatRoomName, room_name); }
void Cache::SetTestRoomName(const std::string &room_name) { SetKV(Cache::vTestChatRoomName, room_name); }
void Cache::SetTestChatMessageQuit(const std::string &message) { SetKV(Cache::vTestChatMessageQuit, message); }
void Cache::RemoveSessionID() { SetKV(Cache::vSessionID, ""); }
std::string Cache::GetValue(const std::string &key) { return kv_[key]; }
void Cache::SetRooms(const std::vector<std::string> &rooms) { rooms_ = rooms; }
std::vector<std::string> Cache::GetRooms() { return rooms_; }

const std::string Cache::vID = "id";
const std::string Cache::vTestID = "test_id";
const std::string Cache::vTestNonce = "test_nonce";
const std::string Cache::vTestPassword = "test_password";
const std::string Cache::vBaseUrl = "base_url";
const std::string Cache::vSessionID = "session_id";
const std::string Cache::vTestSessionID = "test_session_id";
const std::string Cache::vChatRoomName = "chat_room_name";
const std::string Cache::vTestChatRoomName = "test_chat_room_name";
const std::string Cache::vTestChatMessageQuit = "test_chat_quit";