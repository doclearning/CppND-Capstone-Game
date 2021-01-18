#ifndef PAD_H
#define PAD_H

#include <vector>
#include "SDL.h"
#include "mathfu/vector.h"

#include "gobject.h"

class Pad : public GObject {
 public:

  Pad(std::string &&nameIn, mathfu::Vector<float, 3> &&spawnPosition, float width, float height);

  void Update(float deltaTime) override;

  GobjectType GetType() override {return GobjectType::pad;}

private:
  
  float width, height;
};

#endif