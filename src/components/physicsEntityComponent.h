#ifndef PHYSICS_ENTITY_COMPONENT_H
#define PHYSICS_ENTITY_COMPONENT_H

#include "SDL.h"
#include "gobject.h"
#include "component.h"
#include "mathfu/vector.h"
#include "mathfu/glsl_mappings.h"

class Renderer;

class PhysicsEntityComponent : public IComponent {

public:
    PhysicsEntityComponent(Transform &transformIn, GObject &gobjectIn);
    virtual void Draw(Renderer &renderer) override{};
    virtual void Update(float deltaTime) override;

    ComponentType GetType(){
        return ComponentType::physicsEntityComponent;
    }

    void SetMass(float mass);

    //JAQ_Query was thinking about using Rvr here, but seems safer to copy for a rarely-used thing?
    void SetVelocity(mathfu::vec3 velocityIn);
    void SetAcceleration(mathfu::vec3 accelerationIn);
    void SetDamping(float dampingIn);
    
    
    void AddForce(const mathfu::vec3 &forceIn);

    void ClearAccumulator();

    ~PhysicsEntityComponent();

private:

    void Step(float duration);

    Transform &transform;
    GObject &gobject;

    mathfu::vec3 velocity {};
    mathfu::vec3 acceleration {};
    mathfu::vec3 forceAccumulation {};

    //Remove energy to reduce instability
    float damping;
    float inverseMass;

};

#endif



