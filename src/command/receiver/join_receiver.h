#ifndef JOIN_RECEIVER_H_
#define JOIN_RECEIVER_H_

#include <iostream>
#include <memory>
#include "../cache.h"
#include "chat_receiver.h"

#include <pthread.h>
#include "../../common/exception/thread/fail_thread_attr_init.h"
#include "../../common/exception/thread/fail_thread_create.h"
#include "../../common/exception/thread/fail_thread_attr_destroy.h"
#include "../../common/exception/thread/fail_thread_join.h"
#include "../../interface/dto/chat/receive_message_request.h"
#include "../../interface/dto/chat/receive_message_response.h"
#include <vector>

static void* WorkerThread(void *arg);

class JoinReceiver : public ChatReceiver
{
public:
  JoinReceiver(Cache &cache, std::shared_ptr<ChatRepository> repository) : ChatReceiver(cache, repository) {}

  ~JoinReceiver() {
    //TODO memory leak if fails?
    if (pthread_attr_destroy(&attr) != 0)
      throw FailThreadAttrDestroyException("pthread_attr_destroy is failed");

    void *status;
    pthread_join(thread_id, (void **)&status);
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
  
  void GenerateThread(void);

private:
  AnsiColor color;
  pthread_t thread_id;
  pthread_attr_t attr;
  int tid;
};

void JoinReceiver::GenerateThread(void) {

  if (pthread_attr_init(&attr) != 0)
    throw FailThreadAttrInitException("pthread_attr_init is failed");

  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  if (pthread_create(&thread_id, NULL, &WorkerThread, (void*)this) < 0)
      throw FailThreadCreateException("pthread_create is failed");

  cout << "Generate success" << endl;
}

static void* WorkerThread(void *arg) {
  pthread_t tid;
  tid = pthread_self();
  cout << "CJ TEST WorkerThread tid is " << tid << endl;

  JoinReceiver* r = static_cast<JoinReceiver*>(arg); 
  ReceiveMessageRequest request(r->GetRoomName(), r->GetSessionID());
   
  ReceiveMessageResponse response = chat_repository_->ReceiveMessage(request);
  std::vector<Message> messages = response.GetMessages();
  int test_index = 0; 
  for( Message m : messages ) {
    cout << "CJ TEST test index is " << test_index++ << << "date : " << m.GetDate() << "message : " <<  m.GetMessage() <<
      "room : " << m.GetRoomName() << "user_id" : << m.GetUserId() << endl;

  }


}
#endif
