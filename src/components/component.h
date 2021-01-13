#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include "transform.h"

//Maybe make this abstract instead of an interface, and have the parent here. Think it needs to be here. Maybe not parent... maybe transform. I can't decide.

class IComponent {
 public:
  virtual ~IComponent(){};
  virtual void InitialiseTransform(Transform &transform) = 0;
};

#endif