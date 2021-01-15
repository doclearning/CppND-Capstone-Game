#include <iostream>

#include "controller.h"
#include "SDL.h"

void Controller::HandleInput(bool &running) {

  const Uint8 *state = SDL_GetKeyboardState(NULL);
  Notify(state);

  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    }
  }
}

void Controller::Attach(IObserver<Uint8> *observer) {
  list_observer_.push_back(observer);
}
void Controller::Detach(IObserver<Uint8> *observer) {
  list_observer_.remove(observer);
}
void Controller::Notify(const Uint8 *keycode) {
  std::list<IObserver<Uint8> *>::iterator iterator = list_observer_.begin();
  while (iterator != list_observer_.end()) {
    (*iterator)->Notified(keycode);
    ++iterator;
  }
}