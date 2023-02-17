#ifndef JOIN_RECEIVER_H_
#define JOIN_RECEIVER_H_

#include "../cache.h"
#include "chat_receiver.h"
#include "room_receiver.h"

#include "../../common/exception/chat/fail_receive_message_exception.h"

#include <vector>
#include <unistd.h>
#include <semaphore.h>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <memory>
#include <pthread.h>


static const char *QUIT_ROOM = "quit";

static void *ThreadWrapper(void *me);
using namespace std;

class JoinReceiver : public ChatReceiver
{
public:
  JoinReceiver(Cache &cache, std::shared_ptr<ChatRepository> repository) : ChatReceiver(cache, repository) {}
  ~JoinReceiver()
  {
    if (!isthread_destoyed)
      ThreadDestory();
  }

  void ThreadDestory() 
  {
    if(isthread_destoyed) return;
    pthread_attr_destroy(&attr_);
    void *status;
    pthread_join(thread_id_, (void **)&status);
    isthread_destoyed = true;
  }
  
  void InputIessage()
  {
    color_.ImportantWithLineFeed("Enter typing message or you can exit by typing quit ");
  }

  void Action() override
  {
    CheckSession();
    room_name_.assign(GetRoomName());
    cache_.SetRoomName(room_name_);

    try
    {
      ListLastMessages();
    }
    catch (const FailReceiveMessageException &ex)
    {
      throw InvalidCommandException(ex.what());
    }

    if(cache_.GetValue(Cache::vTestChatMessageQuit).empty()) return;

    GenerateThread();

    thread_expired_ = false;

    while (std::getline(std::cin, chat_message_) && chat_message_.compare(QUIT_ROOM) != 0)
    {
      if (std::cin.fail() || chat_message_.length() <= 0)
      {
        chat_message_.clear();
        continue;
      }

      InputIessage();
      SendMessage();
      CheckSession();

      chat_message_.clear();
    }
    thread_expired_ = true;
  }

  void *WorkerThread();

private:
  void SendMessage()
  {
    try
    {
      SendMessageRequest request(room_name_, session_id_, chat_message_);
      SendMessageResponse response = repository_->SendMessage(request);
    }
    catch (const BaseException &ex)
    {
      color_.ErrorWithLineFeed("여기서 에러");
      throw InvalidCommandException("Failed to receive messages");
    }
  }

  void CheckSession()
  {
    session_id_.assign(cache_.GetValue(Cache::vSessionID));
    if (session_id_.empty())
      throw InvalidCommandException("Session is not exists (While Chatting)");
  }

  void ThreadDestory()
  {
    pthread_attr_destroy(&attr_);
    void *status;
    pthread_join(thread_id_, (void **)&status);
    isthread_destoyed = true;
  }

  std::string GetRoomName()
  {
    if (!cache_.GetValue(Cache::vTestChatRoomName).empty())
      return cache_.GetValue(Cache::vTestChatRoomName);

    std::string room_name = "";
    do
    {
      color_.Important(" > Enter Chat Room Name: ");
      std::cin >> room_name;
    } while (room_name.empty());

    return room_name;
  }

  void ListLastMessages()
  {
    std::string sessionID = cache_.GetValue(Cache::vSessionID);
    ReceiveMessageRequest request(room_name_, sessionID);
    last_message_ = "";
    try
    {
      ReceiveMessageResponse response = repository_->ReceiveMessage(request);
      std::vector<Message> messages = response.GetMessages();
      last_message_ = "The message your missed is " + std::to_string(messages.size());
      color_.ImportantWithLineFeed(last_message_);

      for (const auto &iter : messages)
      {
        std::stringstream ss;
        ss << "(" << iter.GetDate() << ":" << iter.GetUserId() << ") " << iter.GetMessage();
        last_message_ = ss.str();
        PrintMessage(iter.GetUserId(), last_message_);
      }
    }
    catch (const BaseException &ex)
    {
      throw InvalidCommandException(ex.what());
    }
  }

  void GenerateThread(void);

  void PrintMessage(std::string user_id, std::string message)
  {
    if (user_id == cache_.GetValue(Cache::vID))
      color_.Message(PaddingString(message));
    else
      color_.ReceivedMessage(message);
  }

  std::string PaddingString(std::string const &str, int n = 150)
  {
    std::ostringstream oss;
    oss << std::setw(n) << str;
    return oss.str();
  }

  AnsiColor color_;
  pthread_t thread_id_;
  pthread_attr_t attr_;
  volatile bool thread_expired_ = true, isthread_destoyed = false;
  std::string room_name_;
  std::string session_id_, chat_message_;
  std::string last_message_;
};

#endif
