#ifndef DEFAULT_RENDER_COMPONENT_H
#define DEFAULT_RENDER_COMPONENT_H

#include <memory>
#include "SDL.h"
#include "component.h"
#include "renderer.h"

class Renderer;

class DefaultRenderComponent : public IComponent {

public:
    DefaultRenderComponent(Transform &transformIn) : transform(transformIn){};
    virtual void Draw(Renderer &renderer) override;
    virtual void Update(float deltaTime) override{};
    

private:
    Transform &transform;
};

#endif