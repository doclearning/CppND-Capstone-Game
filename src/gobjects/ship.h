#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <deque>
#include "SDL.h"
#include "SDL_image.h"
#include "mathfu/vector.h"

#include "gobject.h"
#include "observer.h"
#include "collisionHandler.h"

class Game;

class Ship : public GObject, public IObserver<Collision>  {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Ship(Game &gameIn, std::string &&nameIn, mathfu::Vector<float, 3> &&spawnPosition);
  ~Ship();

  void Update(float deltaTime) override;

  void Notified(const Collision *notification) override;

  GobjectType GetType() override {return GobjectType::ship;}

private:
  void RemoveCollisionHandler();
  void RemoveInputHandler();
  void CleanUp();
  
  bool shipStopped;
  bool cleanedUp;

  Game &game;

  static constexpr float MAX_IMPACT_VELOCITY = 40;
  static constexpr float MAX_IMPACT_ANGLE = 0.15;
};

#endif