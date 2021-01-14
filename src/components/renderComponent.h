#ifndef DEFAULT_RENDER_COMPONENT_H
#define DEFAULT_RENDER_COMPONENT_H

#include <memory>
#include "SDL.h"

#include "component.h"
#include "renderer.h"

class Renderer;

class DefaultRenderComponent : public IComponent{

public:
    DefaultRenderComponent(Transform &transformIn) : transform(transformIn){};
    virtual void Draw(Renderer &renderer);
    // virtual void InitialiseTransform(Transform &transformIn) override{
        
    //     transform = transformIn;
    // }

private:
    Transform &transform;
};

#endif