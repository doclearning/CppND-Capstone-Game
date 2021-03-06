#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

template <class T>
class IObserver {
 public:
  virtual ~IObserver(){};
  virtual void Notified(const T *notification) = 0;
};

template <class T>
class ISubject {
 public:
  virtual ~ISubject(){};
  virtual void Attach(IObserver<T> *observer) = 0;
  virtual void Detach(IObserver<T> *observer) = 0;

  //JAQ_TD refactor this to return a reference or an rvr
  virtual void Notify(const T *notice) = 0;
};

#endif