
#ifndef RECEIVER_H_
#define RECEIVER_H_

#include "../cache.h"

class Receiver
{
public:
  Receiver(Cache &cache) : cache_(cache) {}
  virtual void Action() = 0;

protected:
  Cache &cache_;
};

#endif
