#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include "transform.h"

class IComponent {
 public:
  virtual ~IComponent(){};
  //virtual void InitialiseTransform(Transform &transform) = 0;
};

#endif