#ifndef JOIN_RECEIVER_H_
#define JOIN_RECEIVER_H_

#include <iostream>
#include <memory>
#include "../cache.h"
#include "chat_receiver.h"

#include <pthread.h>
//#include <sys/prctl.h>
#include "../../common/exception/thread/fail_thread_attr_init.h"
#include "../../common/exception/thread/fail_thread_create.h"
#include "../../common/exception/thread/fail_thread_attr_destroy.h"
#include "../../common/exception/thread/fail_thread_join.h"
#include "../../interface/dto/chat/receive_message_request.h"
#include "../../interface/dto/chat/receive_message_response.h"

#include "../../common/exception/command/invalid_command_exception.h"

#include <vector>
#include <unistd.h>
#include <semaphore.h> 

static void *ThreadWrapper(void *me);

class JoinReceiver : public ChatReceiver
{
public:
  JoinReceiver(Cache &cache, std::shared_ptr<ChatRepository> repository) : ChatReceiver(cache, repository) {}
  ~JoinReceiver() 
  {  
    thread_expired_ = true;
    pthread_attr_destroy(&attr_);
    void *status;
    pthread_join(thread_id_, (void **)&status);
  }
  
  void ReceiveMessage(const ReceiveMessageRequest& request)
  {
    ReceiveMessageResponse response = repository_->ReceiveMessage(request);
    for (const auto &it : response.GetMessages())
      color_.ReceivedMessage(it.GetMessage());
  }

  void Action() override
  {
    room_name_.assign(GetRoomName());
    session_id_.assign(cache_.GetValue(Cache::vSessionID));
    if (session_id_.empty())
      throw InvalidCommandException("Session is not exists");

    cache_.SetRoomName(room_name_);
    GenerateThread();

    thread_expired_ = false;
    cout << "Enter typing message or you can exit by typing quit " << endl;

    while(std::cin >> chat_message_ && chat_message_.compare("quit") != 0) 
    {
      session_id_.assign(cache_.GetValue(Cache::vSessionID));
      if (session_id_.empty())
        throw InvalidCommandException("Session is not exists");

        std::cout << "Enter typing message or you can exit by typing quit " << std::endl;
       
        try {
          SendMessageRequest request(room_name_, session_id_, chat_message_);
          SendMessageResponse response = repository_->SendMessage(request);
        }
        catch (const BaseException &ex)
        {
          color_.ImportantWithLineFeed(ex.what());
        }

        chat_message_.clear();
    }
      
  std::cout << "Action is end!" << std::endl;
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
  
  void GenerateThread(void);

  void *WorkerThread();

  template<typename T>
  bool isEqual(std::vector<T> const &v1, std::vector<T> const &v2)
  {
      auto pair = std::mismatch(v1.begin(), v1.end(), v2.begin());
      return (pair.first == v1.end() && pair.second == v2.end());
  }

  bool CompareInfoAndStoreIfRequired(std::vector<Message>& NewInfo) {

      if (isEqual(internal_info_, NewInfo)) {
          return true;
      }
      else {
        internal_info_.clear();
        internal_info_ = NewInfo;
      }
  }
  std::string getPaddingString(std::string const &str, int n)
  {
      std::ostringstream oss;
      oss << std::setw(n) << str;
      return oss.str();
  }  

private:
  AnsiColor color_;
  pthread_t thread_id_;
  pthread_attr_t attr_;
  volatile bool thread_expired_ = true;
  std::string room_name_;
  std::string session_id_, chat_message_;
  std::vector<Message> internal_info_;
};

#endif
