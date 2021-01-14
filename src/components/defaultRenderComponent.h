#ifndef DEFAULT_RENDER_COMPONENT_H
#define DEFAULT_RENDER_COMPONENT_H

#include <memory>
#include "SDL.h"

#include "component.h"

class Renderer;

class DefaultRenderComponent : public IComponent{

public:
    DefaultRenderComponent(Transform &transformIn) : transform(transformIn){};
    virtual void Draw(Renderer &renderer) override;

private:
    Transform &transform;
};

#endif