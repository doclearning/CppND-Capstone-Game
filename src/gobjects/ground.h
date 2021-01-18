#ifndef GROUND_H
#define GROUND_H

#include <vector>
#include <deque>
#include "SDL.h"
#include "mathfu/vector.h"

#include "gobject.h"

class Ground : public GObject {
 public:

  Ground(std::string &&nameIn, mathfu::Vector<float, 3> &&spawnPosition);

  void Update(float deltaTime) override;

  GobjectType GetType() override {return GobjectType::ground;}

private:
  

};

#endif