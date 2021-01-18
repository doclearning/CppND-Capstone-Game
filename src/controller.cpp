#include <iostream>

#include "controller.h"
#include "SDL.h"

GameState Controller::HandleClientInput() {

  //JAQ_Future Keypresses for other states
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT)
      return GameState::ending;
  }
  return GameState::running;
}

GameState Controller::HandleGameInput(){

  const Uint8 *state = SDL_GetKeyboardState(NULL);

  GameState gameState = GameState::running;

  if(state[SDL_SCANCODE_R]){
    gameState = GameState::restarting;
  }else if(state[SDL_SCANCODE_C]){
    gameState = GameState::transitioning;
  }

  Notify(state);

  return gameState;
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