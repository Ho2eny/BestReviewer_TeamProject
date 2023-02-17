#include <sstream>
#include "join_receiver.h"

using namespace std;
static const int sleep_second = 3000 * 1000;

void JoinReceiver::GenerateThread(void)
{
  pthread_attr_init(&attr_);
  pthread_attr_setdetachstate(&attr_, PTHREAD_CREATE_JOINABLE);
  pthread_create(&thread_id_, NULL, ThreadWrapper, (void *)this);
}

static void *ThreadWrapper(void *me)
{
  static_cast<JoinReceiver *>(me)->WorkerThread();
  return nullptr;
}

void *JoinReceiver::WorkerThread()
{
  pthread_t tid;
  tid = pthread_self();

  std::string sessionID = cache_.GetValue(Cache::vSessionID);
  ReceiveMessageRequest request(room_name_, sessionID);

  while (!thread_expired_)
  {
    try
    {
      ReceiveMessageResponse response = repository_->ReceiveMessage(request);
      std::vector<Message> messages = response.GetMessages();

      bool print_messages = false;
      for (const auto &iter : messages)
      {
        std::stringstream ss;
        ss << "(" << iter.GetDate() << ":" << iter.GetUserId() << ") " << iter.GetMessage();
        std::string message = ss.str();

        if (print_messages)
        {
          PrintMessage(iter.GetUserId(), message);
          last_message_ = message;
        }

        if (!print_messages && message == last_message_)
        {
          print_messages = true;
        }
      }
    }
    catch (const BaseException &ex)
    {
      throw InvalidCommandException(ex.what());
    }

    usleep(sleep_second);
  }

  ThreadDestory();
  return nullptr;
}