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

  //JAQ_TODO Make member variables
  float tempFactor = 50;

  if (state[SDL_SCANCODE_A]) {
    transform.zAxisAngle -= 0.0872665;
  }

  if (state[SDL_SCANCODE_D]) {
    transform.zAxisAngle += 0.0872665;
  }

  if (state[SDL_SCANCODE_W]) {
    shipPhysicsComponent->AddAcceleration(transform.forward * tempFactor);
  }else{
    shipPhysicsComponent->ClearAccumulator();
  }
  
  if (state[SDL_SCANCODE_S]) {
  }
}

DefaultInputComponent::~DefaultInputComponent(){

    auto &controller = Controller::instance();
    controller.Detach(this);
}