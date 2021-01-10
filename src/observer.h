#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

//JAQ_TODO: need to templateise this, so we can pass functions, say

template <class T>
class IObserver {
 public:
  virtual ~IObserver(){};
  virtual void Notified(const T &notification) = 0;
};

template <class T>
class ISubject {
 public:
  virtual ~ISubject(){};
  virtual void Attach(IObserver<T> *observer) = 0;
  virtual void Detach(IObserver<T> *observer) = 0;
  virtual void Notify(T notice) = 0;

  //Basic templating is sort of set up, apart from the notice above. Not finished.
};

#endif