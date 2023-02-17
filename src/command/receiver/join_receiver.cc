#include "join_receiver.h"

using namespace std;

void JoinReceiver::GenerateThread(void) {
  pthread_attr_init(&attr_);
  pthread_attr_setdetachstate(&attr_, PTHREAD_CREATE_JOINABLE);
  pthread_create(&thread_id_, NULL, ThreadWrapper, (void*)this);
}

// static
static void *ThreadWrapper(void *me) {

    static_cast<JoinReceiver *>(me)->WorkerThread();

    return nullptr;
}
 
void* JoinReceiver::WorkerThread() {
  pthread_t tid;
  tid = pthread_self();
  while(!thread_expired_ ) {
    std::string sessionID = cache_.GetValue(Cache::vSessionID);
    try {
      ReceiveMessageRequest request(room_name_, sessionID);
      ReceiveMessageResponse response = repository_->ReceiveMessage(request);
      std::vector<Message> messages = response.GetMessages();

      if(!CompareInfoAndStoreIfRequired(messages)) {
        cout << "[";
        for (vector<Message>::iterator iter = messages.begin(); iter != messages.end(); iter++) {
          cout << "{date : " << (*iter).GetDate() << " message :  " << getPaddingString((*iter).GetMessage(), 50) <<
            " room : " << (*iter).GetRoomName()  << " user_id : " << (*iter).GetUserId() << "}";
            if(iter == messages.end() - 1) cout << "]"<< endl;
            cout << endl;
        }
      }
    }
    catch (const BaseException &ex)
    {
      color_.ImportantWithLineFeed(ex.what());
    }
  
    usleep( 3000 * 1000 );
  }

  ThreadDestory();
}