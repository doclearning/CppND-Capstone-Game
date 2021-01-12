#include "ship.h"

#include <cmath>
#include <iostream>

#include "mathfu/constants.h"

Ship::Ship(mathfu::Vector<float, 2> &&spawnPosition) : GObject(std::move(spawnPosition)){
}

void Ship::Update() {
  //Wrap the Snake around to the beginning if going off of the screen.
  //head_x = fmod(head_x + grid_width, grid_width);
  //head_y = fmod(head_y + grid_height, grid_height);
}

void Ship::Notified(const SDL_Keycode &notification){

  std::cout << "Observer: ";

  switch (notification) {
    case SDLK_UP:
      std::cout << "Up\n";

      transform->position += -mathfu::kAxisY2f;
      break;

    case SDLK_DOWN:
      std::cout << "Down\n";
      transform->position += mathfu::kAxisY2f;
      break;

    case SDLK_LEFT:
      std::cout << "Left\n";
      transform->position += -mathfu::kAxisX2f;
      break;

    case SDLK_RIGHT:
      std::cout << "Right\n";
      transform->position += mathfu::kAxisX2f;
      break;

  }
}