#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

void Controller::HandleInput(bool &running) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {

      std::cout << "Input\n";

      
      Notify();

      switch (e.key.keysym.sym) {
        // case SDLK_UP:
        //   ChangeDirection(snake, Snake::Direction::kUp,
        //                   Snake::Direction::kDown);
        //   break;

        // case SDLK_DOWN:
        //   ChangeDirection(snake, Snake::Direction::kDown,
        //                   Snake::Direction::kUp);
        //   break;

        // case SDLK_LEFT:
        //   ChangeDirection(snake, Snake::Direction::kLeft,
        //                   Snake::Direction::kRight);
        //   break;

        // case SDLK_RIGHT:
        //   ChangeDirection(snake, Snake::Direction::kRight,
        //                   Snake::Direction::kLeft);
        //   break;

        
        //Notify();
      }
    }
  }
}

//JAQ_Concern: Feels weird having to implement these methods here
void Controller::Attach(IObserver *observer) {
  list_observer_.push_back(observer);
}
void Controller::Detach(IObserver *observer) {
  list_observer_.remove(observer);
}
void Controller::Notify() {
  std::list<IObserver *>::iterator iterator = list_observer_.begin();
  while (iterator != list_observer_.end()) {
    (*iterator)->Notified("Notification");
    ++iterator;
  }
}