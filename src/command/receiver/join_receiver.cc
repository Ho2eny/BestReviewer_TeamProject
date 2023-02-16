#include "join_receiver.h"

using namespace std;

void JoinReceiver::GenerateThread(void) {
  
  if (pthread_attr_init(&attr_) != 0)
    throw FailThreadAttrInitException("pthread_attr_init is failed");

  pthread_attr_setdetachstate(&attr_, PTHREAD_CREATE_JOINABLE);

  if (pthread_create(&thread_id_, NULL, ThreadWrapper, (void*)this) < 0 ) {
      throw FailThreadCreateException("pthread_create is failed");
  }
}

// static
static void *ThreadWrapper(void *me) {

    static_cast<JoinReceiver *>(me)->WorkerThread();

    return nullptr;
}

void* JoinReceiver::WorkerThread() {
  pthread_t tid;
  //prctl(PR_SET_NAME, (unsigned long)"FIFO_WorkerThread", 0, 0, 0);

  tid = pthread_self();

  while(!thread_expired_ && sem_wait(&present_lock_) == 0) {
    std::string sessionID = cache_.GetValue(Cache::vSessionID);

    //cout << "WorkerThread start loop " << endl;
    try {
      ReceiveMessageRequest request(roomName_, sessionID);
      ReceiveMessageResponse response = repository_->ReceiveMessage(request);
      std::vector<Message> messages = response.GetMessages();
      int index = 0; 
      for(auto& m : messages ) {
        cout << "Index is " << index++ << " date : " << m.GetDate() << " message :  " <<  m.GetMessage() <<
          " room : " << m.GetRoomName() << " user_id : " << m.GetUserId() << endl;
      }
    }
    catch (const BaseException &ex)
    {
      color_.ImportantWithLineFeed(ex.what());
    }

    //cout << "WorkerThread end loop " << endl;
    cout << "Type the message if you want" << endl;
  }
}