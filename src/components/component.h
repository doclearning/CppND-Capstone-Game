#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include "gobject.h"
#include "transform.h"
//#include "renderer.h"

class Renderer;

enum ComponentType { defaultInputComponent, defaultRenderComponent, meshRenderComponent, physicsEntityComponent };

class IComponent {
 public:
  virtual ~IComponent(){};
  virtual void Draw(Renderer &renderer) = 0;
  virtual void Update(float deltaTime) = 0;

  //JAQ_Todo remove this. Unused probably.
  virtual ComponentType GetType() = 0;
};

#endif