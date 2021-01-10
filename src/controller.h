#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <list>
#include "snake.h"
#include "observer.h"

class Controller : public ISubject {
 public:
  void HandleInput(bool &running/*, Snake &snake*/);

  void Attach(IObserver *observer) override;
  void Detach(IObserver *observer) override;
  void Notify() override;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input, Snake::Direction opposite) const;

  std::list<IObserver *> list_observer_;
};

#endif