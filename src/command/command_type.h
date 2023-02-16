#ifndef COMMAND_TYPE_
#define COMMAND_TYPE_

enum class CommandType
{
  kSignup = 50,
  kLogin = 51,
  kLogout = 52,
  kListRooms = 60,
  kCreateRoom = 61,
  kJoinRoom = 62,
  kWrongCommand = 1000
};

#endif