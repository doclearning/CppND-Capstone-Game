#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "mathfu/vector.h"

#include "gobject.h"
#include "observer.h"

class Ship : public GObject {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Ship(std::string &&nameIn, mathfu::Vector<float, 2> &&spawnPosition);

  void Update();
  
  float speed{1.0};
  bool alive{true};

};

#endif