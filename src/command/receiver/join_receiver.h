#ifndef JOIN_RECEIVER_H_
#define JOIN_RECEIVER_H_

#include <iostream>
#include <memory>
#include "../cache.h"
#include "chat_receiver.h"

class JoinReceiver : public ChatReceiver
{
public:
  JoinReceiver(Cache &cache, std::shared_ptr<ChatRepository> repository) : ChatReceiver(cache, repository) {}

  // TODO : Change to thread
  void ReceiveMessage(const ReceiveMessageRequest& request)
  {
    ReceiveMessageResponse response = repository_->ReceiveMessage(request);
    for (const auto &it : response.GetMessages())
      color_.ReceivedMessage(it.GetMessage());
  }

  void Action() override
  {
    std::string sessionID = cache_.GetValue(Cache::vSessionID);
    if (sessionID.empty())
      throw InvalidCommandException("Session is not exists");

    try
    {
      std::string room_name = GetRoomName();
      cache_.SetRoomName(room_name);

      ReceiveMessageRequest request(room_name, sessionID);

      // TODO : Change to thread
      bool keep = true;
      std::string command;
      while (keep)
      {
        ReceiveMessage(request);

        
        cin >> command;
        keep = command == "quit";

        color_.Message(command);
      }
    }
    catch (const InvalidCommandException &ex)
    {
      color_.ImportantWithLineFeed(ex.what());
    }
  }

  std::string GetRoomName()
  {
    if (!cache_.GetValue(Cache::vTestChatRoomName).empty())
      return cache_.GetValue(Cache::vTestChatRoomName);

    std::string chat_room_name;
    color_.Important(" > Enter Chat Room Name: ");
    std::cin >> chat_room_name;
    return chat_room_name;
  }

private:
  AnsiColor color_;
};
#endif
