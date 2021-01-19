#include "defaultInputComponent.h"
#include <iostream>
#include "mathfu/constants.h"
#include "controller.h"
#include "physicsEntityComponent.h"

//Uses the Controller singleton to attach to it as an IObserver
DefaultInputComponent::DefaultInputComponent(Transform &transformIn, GObject &gobjectIn) : transform(transformIn), gobject(gobjectIn){

    auto &controller = Controller::instance();
    controller.Attach(this);
}

void DefaultInputComponent::Update(float deltaTime){}

void DefaultInputComponent::Notified(const Uint8 *state){

  //Gross, but lazy-assign this becuase we don't know if the other component will exist in the ctor
  if(shipPhysicsComponent == nullptr)
    shipPhysicsComponent = gobject.GetComponent<PhysicsEntityComponent>();


  if (state[SDL_SCANCODE_A]) {
    transform.zAxisAngle -= ROTATION_ANGLE_STEP;
  }

  if (state[SDL_SCANCODE_D]) {
    transform.zAxisAngle += ROTATION_ANGLE_STEP;
  }

  if (state[SDL_SCANCODE_W]) {
    shipPhysicsComponent->AddAcceleration(transform.forward * VELOCITY_SCALE_FACTOR);
  }else{
    shipPhysicsComponent->ClearAccumulator();
  }
  
  if (state[SDL_SCANCODE_S]) {
  }
}

DefaultInputComponent::~DefaultInputComponent(){
    Controller::instance().Detach(this);
}