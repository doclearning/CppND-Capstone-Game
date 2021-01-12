#include <iostream>

#include "controller.h"
#include "SDL.h"
#include "snake.h"

void Controller::HandleInput(bool &running) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {

      Notify(e.key.keysym.sym);
    }
  }
}

//JAQ_Concern: Feels weird having to implement these methods here
void Controller::Attach(IObserver<SDL_Keycode> *observer) {
  list_observer_.push_back(observer);
}
void Controller::Detach(IObserver<SDL_Keycode> *observer) {
  list_observer_.remove(observer);
}
void Controller::Notify(SDL_Keycode keycode) {
  std::list<IObserver<SDL_Keycode> *>::iterator iterator = list_observer_.begin();
  while (iterator != list_observer_.end()) {
    (*iterator)->Notified(keycode);
    ++iterator;
  }
}