#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <string>

class Message {
public:
  Message(int date, std::string message, std::string room_name, std::string user_id) : date_(date), message_(message), room_name_(room_name), user_id_(user_id) {}

  int GetDate() const;
  std::string GetMessage() const;
  std::string GetRoomName() const;
  std::string GetUserId() const;

  bool operator==(const Message &rhs) const { 
    return ( date_ == rhs.date_) && (message_ == rhs.message_)
    && ( room_name_ == rhs.room_name_) && (user_id_ == rhs.user_id_);
  }

private:
  int date_;
  std::string message_;
  std::string room_name_;
  std::string user_id_;
};

inline int Message::GetDate() const {
  return date_;
}

inline std::string Message::GetMessage() const {
  return message_;
}

inline std::string Message::GetRoomName() const {
  return room_name_;
}

inline std::string Message::GetUserId() const {
  return user_id_;
}

#endif