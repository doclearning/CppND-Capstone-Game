#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "observer.h"
#include "mathfu/vector.h"

class Snake : public IObserver<SDL_Keycode> {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(mathfu::Vector<float, 2> spawnPosition) : position(spawnPosition){}

  void Update();

  void Notified(const SDL_Keycode &notification) override;

  float speed{1.0};
  bool alive{true};

  mathfu::Vector<float, 2>& GetPosition(){
    return position;
  }

 private:

  mathfu::Vector<float, 2> position;

  void Translate(const mathfu::Vector<float, 2> translation);
};

#endif