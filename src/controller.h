#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <list>
#include "SDL.h"
#include "observer.h"
#include "singleton.h"
#include "game.h"

class Controller : public Singleton<Controller>, public ISubject<Uint8> {
 public:
  Controller(token) { std::cout << "Controller constructed" << std::endl; }

  GameState HandleClientInput();
  GameState HandleGameInput();

  void Attach(IObserver<Uint8> *observer) override;
  void Detach(IObserver<Uint8> *observer) override;
  void Notify(const Uint8 *state) override;

  ~Controller() {  std::cout << "Controller destructed" << std::endl; }


 private:
  std::list<IObserver<Uint8> *> list_observer_;
};

#endif