#ifndef DEFAULT_INPUT_COMPONENT_H
#define DEFAULT_INPUT_COMPONENT_H

#include "SDL.h"
#include "gobject.h"
#include "component.h"
#include "observer.h"
#include "physicsEntityComponent.h"

class Renderer;

//JAQ_Todo refactor this to player input component. As then it's unique.
class DefaultInputComponent : public IComponent, public IObserver<Uint8> {

public:
    DefaultInputComponent(Transform &transformIn, GObject &gobjectIn);
    virtual void Draw(Renderer &renderer) override{};
    virtual void Update(float deltaTime) override;
    
    void Notified(const Uint8 *notification) override;

    ~DefaultInputComponent();

private:
    Transform &transform;
    GObject &gobject;

    static constexpr float VELOCITY_SCALE_FACTOR = 50;
    static constexpr float ROTATION_ANGLE_STEP = 0.0872665;

    std::shared_ptr<PhysicsEntityComponent> shipPhysicsComponent;
};

#endif



