#ifndef SHIP_INPUT_COMPONENT_H
#define SHIP_INPUT_COMPONENT_H

#include "SDL.h"
#include "gobject.h"
#include "component.h"
#include "observer.h"
#include "physicsEntityComponent.h"

class Renderer;
 
class ShipInputComponent : public IComponent, public IObserver<Uint8> {

public:
    ShipInputComponent(Transform &transformIn, GObject &gobjectIn);
    virtual void Draw(Renderer &renderer) override{};
    virtual void Update(float deltaTime) override;

    void Notified(const Uint8 *notification) override;

    ~ShipInputComponent();

private:
    Transform &transform;
    GObject &gobject;

    const float VELOCITY_SCALE_FACTOR = 50.0f;
    static constexpr float ROTATION_ANGLE_STEP = 0.0872665;

    std::shared_ptr<PhysicsEntityComponent> shipPhysicsComponent;
};

#endif



