#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "mathfu/vector.h"

#include "gobject.h"
#include "observer.h"

class Ship : public GObject, public IObserver<SDL_Keycode> {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Ship(mathfu::Vector<float, 2> &&spawnPosition);

  void Update();

  void Notified(const SDL_Keycode &notification) override;

  float speed{1.0};
  bool alive{true};

};

#endif