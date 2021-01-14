#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <list>
#include "SDL.h"
#include "observer.h"
#include "singleton.h"

class Controller : public Singleton<Controller>, public ISubject<SDL_Keycode> {
 public:
  Controller(token) { std::cout << "Controller constructed" << std::endl; }

  void HandleInput(bool &running);

  void Attach(IObserver<SDL_Keycode> *observer) override;
  void Detach(IObserver<SDL_Keycode> *observer) override;
  void Notify(SDL_Keycode) override;

  ~Controller() {  std::cout << "Controller destructed" << std::endl; }


 private:
  std::list<IObserver<SDL_Keycode> *> list_observer_;
};

#endif