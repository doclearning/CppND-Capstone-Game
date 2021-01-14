#include "ship.h"

#include <cmath>
#include <iostream>

#include "mathfu/constants.h"

Ship::Ship(std::string &&nameIn, mathfu::Vector<float, 2> &&spawnPosition) : GObject(std::move(nameIn), std::move(spawnPosition)){

  std::cout << "Ship created\n";
}

void Ship::Update() {
  //Wrap the Snake around to the beginning if going off of the screen.
  //head_x = fmod(head_x + grid_width, grid_width);
  //head_y = fmod(head_y + grid_height, grid_height);

  //std::cout << "Ship update\n";
}

void Ship::Notified(const SDL_Keycode &notification){

  std::cout << "Observer: ";

  mathfu::Vector<float, 2> tempFactor(10, 10);

  switch (notification) {
    case SDLK_UP:
      std::cout << "Up\n";

      transform.position += -mathfu::kAxisY2f*tempFactor;
      break;

    case SDLK_DOWN:
      std::cout << "Down\n";
      transform.position += mathfu::kAxisY2f*tempFactor;
      break;

    case SDLK_LEFT:
      std::cout << "Left\n";
      transform.position += -mathfu::kAxisX2f*tempFactor;
      break;

    case SDLK_RIGHT:
      std::cout << "Right\n";
      transform.position += mathfu::kAxisX2f*tempFactor;
      break;

  }

  std::cout << "transform position = " << transform.position[0] << "," << transform.position[1] << "\n";
}