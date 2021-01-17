#include "ground.h"

#include <cmath>

#include "mathfu/constants.h"

Ground::Ground(std::string &&nameIn, mathfu::Vector<float, 3> &&spawnPosition) : GObject(std::move(nameIn), std::move(spawnPosition)){

  std::cout << "Ground created\n";
}

void Ground::Update(float deltaTime) {
  GObject::Update(deltaTime);
}
