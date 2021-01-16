#ifndef DEFAULT_INPUT_COMPONENT_H
#define DEFAULT_INPUT_COMPONENT_H

#include "SDL.h"
#include "component.h"

class Renderer;

class PhysicsComponent : public IComponent {

public:
    PhysicsComponent(Transform &transformIn);
    virtual void Draw(Renderer &renderer) override{};
    virtual void Update() override;


    ~PhysicsComponent();

private:
    Transform &transform;
};

#endif



