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
  JoinReceiver(Cache &cache, std::shared_ptr<ChatRepository> repository) : ChatReceiver(cache, repository) 
  {
    sem_init(&present_lock_, 0, 0);
  }

  ~JoinReceiver() 
  {  
    thread_expired_ = true;
    sem_destroy(&present_lock_);

    //TODO memory leak if fails?
    if (pthread_attr_destroy(&attr_) != 0)
      throw FailThreadAttrDestroyException("pthread_attr_destroy is failed");

    void *status;
    pthread_join(thread_id_, (void **)&status);
    if (status != 0)
      throw FailThreadJoinException("pthread_join is failed");
  }
  
  // TODO : Change to thread
  void ReceiveMessage(const ReceiveMessageRequest& request)
  {
    ReceiveMessageResponse response = repository_->ReceiveMessage(request);
    for (const auto &it : response.GetMessages())
      color_.ReceivedMessage(it.GetMessage());
  }

  void Action() override
  {
    roomName_.assign(GetRoomName());
    session_id_.assign(cache_.GetValue(Cache::vSessionID));
    if (session_id_.empty())
      throw InvalidCommandException("Session is not exists");

    cache_.SetRoomName(roomName_);
    GenerateThread();

    //start
    thread_expired_ = false;
    std::cout << "start thread here !! " << std::endl;
    std::cout << "Enter typing message or you can exit by typing quit " << std::endl;

    while(std::cin >> chat_message_ && chat_message_.compare("quit") != 0) 
    {
      session_id_.assign(cache_.GetValue(Cache::vSessionID));
      if (session_id_.empty())
        throw InvalidCommandException("Session is not exists");

        std::cout << "Enter typing message or you can exit by typing quit " << std::endl;
       
        try {
          //send message
          SendMessageRequest request(roomName_, session_id_, chat_message_);
          SendMessageResponse response = repository_->SendMessage(request);
          
          //usleep( 3000 * 1000 );
        }
        catch (const BaseException &ex)
        {
          color_.ImportantWithLineFeed(ex.what());
        }

        chat_message_.clear();
        sem_post(&present_lock_);
        
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
  
private:
  AnsiColor color_;
  pthread_t thread_id_;
  pthread_attr_t attr_;
  volatile bool thread_expired_ = true;
  std::string roomName_;
  std::string session_id_, chat_message_;
  sem_t present_lock_;
};
#endif
