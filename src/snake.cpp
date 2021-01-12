#include "snake.h"

#include <cmath>
#include <iostream>

#include "mathfu/constants.h"

void Snake::Update() {
  // Wrap the Snake around to the beginning if going off of the screen.
  //head_x = fmod(head_x + grid_width, grid_width);
  //head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::Notified(const SDL_Keycode &notification){

  std::cout << "Observer: ";

  switch (notification) {
    case SDLK_UP:
      std::cout << "Up\n";

      Translate(-mathfu::kAxisY2f);
      break;

    case SDLK_DOWN:
      std::cout << "Down\n";
      Translate(mathfu::kAxisY2f);
      break;

    case SDLK_LEFT:
      std::cout << "Left\n";
      Translate(-mathfu::kAxisX2f);
      break;

    case SDLK_RIGHT:
      std::cout << "Right\n";
      Translate(mathfu::kAxisX2f);
      break;

  }
}

void Snake::Translate(const mathfu::Vector<float, 2> translation){

  position += translation;
}