#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

//JAQ_TODO: need to templateise this, so we can pass functions, say

class IObserver {
 public:
  virtual ~IObserver(){};
  virtual void Notified(const std::string &message) = 0;
};

class ISubject {
 public:
  virtual ~ISubject(){};
  virtual void Attach(IObserver *observer) = 0;
  virtual void Detach(IObserver *observer) = 0;
  virtual void Notify() = 0;
};

#endif