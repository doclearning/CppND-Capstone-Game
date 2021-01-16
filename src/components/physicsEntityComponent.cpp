#include "physicsEntityComponent.h"
#include <iostream>
#include <cmath>
#include "mathfu/constants.h"

//Uses the Controller singleton to attach to it as an IObserver
PhysicsEntityComponent::PhysicsEntityComponent(Transform &transformIn, GObject &gobjectIn) : transform(transformIn), gobject(gobjectIn){

}

void PhysicsEntityComponent::Update(float deltaTime){

    auto temp = gobject.accruedForce;
    
    AddForce(temp);
    Step(deltaTime);

    if(temp == mathfu::kZeros3f) {
        ClearAccumulator();
    }else{
        gobject.accruedForce = mathfu::kZeros3f;
    }
}

//All calculations over delta time
void PhysicsEntityComponent::Step(float deltaTime){

    if(deltaTime <= 0.0)
        return;

    //Linear velocity
    transform.position += velocity * deltaTime;

    //Acceleration
    mathfu::vec3 resultingAcceleration = acceleration;
    resultingAcceleration += forceAccumulation * inverseMass;
    
    //Linear velocity from acceleration
    velocity += resultingAcceleration * deltaTime;

    //Drag
    velocity *= std::pow(damping, deltaTime);
}

void PhysicsEntityComponent::AddForce(const mathfu::vec3 &forceeIn){
    
    forceAccumulation += forceeIn;
}

//---------------- Mutators

void PhysicsEntityComponent::SetMass(float massIn){
    
    if(massIn != 0)
        inverseMass = 1.0/massIn;
}
void PhysicsEntityComponent::SetVelocity(mathfu::vec3 velocityIn){
    
    velocity = velocityIn;
}
void PhysicsEntityComponent::SetAcceleration(mathfu::vec3 accelerationIn){
    
    acceleration = accelerationIn;
}
void PhysicsEntityComponent::SetDamping(float dampingIn){
    
    damping = dampingIn;
}

void PhysicsEntityComponent::ClearAccumulator(){

    forceAccumulation = mathfu::kZeros3f;
}


PhysicsEntityComponent::~PhysicsEntityComponent(){}