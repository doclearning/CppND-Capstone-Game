#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include "transform.h"
#include "renderer.h"

class Renderer;

class IComponent {
 public:
  virtual ~IComponent(){};
  virtual void Draw(Renderer &renderer) = 0;
};

#endif