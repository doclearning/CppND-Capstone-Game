#include "ship.h"

#include <cmath>
#include <iostream>

#include "mathfu/constants.h"

Ship::Ship(std::string &&nameIn, mathfu::Vector<float, 3> &&spawnPosition) : GObject(std::move(nameIn), std::move(spawnPosition)){

  std::cout << "Ship created\n";
}

void Ship::Update() {
  //Wrap the Snake around to the beginning if going off of the screen.
  //head_x = fmod(head_x + grid_width, grid_width);
  //head_y = fmod(head_y + grid_height, grid_height);

  //std::cout << "Ship update\n";
  GObject::Update();
}

