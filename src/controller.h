#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <list>
#include "SDL.h"
#include "observer.h"

class Controller : public ISubject<SDL_Keycode> {
 public:
  void HandleInput(bool &running);

  void Attach(IObserver<SDL_Keycode> *observer) override;
  void Detach(IObserver<SDL_Keycode> *observer) override;
  void Notify(SDL_Keycode) override;

 private:
  std::list<IObserver<SDL_Keycode> *> list_observer_;
};

#endif