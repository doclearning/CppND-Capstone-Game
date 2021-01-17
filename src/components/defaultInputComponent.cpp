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

  //JAQ_TODO Make member variables
  float tempFactor = 50;

  int count = 0;

  if (state[SDL_SCANCODE_A]) {
    count++;
    transform.zAxisAngle -= 0.0872665;
  }

  if (state[SDL_SCANCODE_D]) {
    count++;
    transform.zAxisAngle += 0.0872665;
  }

  if (state[SDL_SCANCODE_W]) {
    count++;

    //auto entity = gobject.GetComponent<PhysicsEntityComponent>();
    gobject.accruedForce += transform.forward * tempFactor;
  }
  
  if (state[SDL_SCANCODE_S]) {
    count++;
    //transform.position -= transform.forward * tempFactor;
  }

  // if(count > 0)
  //   std::cout << "\n";
}

DefaultInputComponent::~DefaultInputComponent(){

    auto &controller = Controller::instance();
    controller.Detach(this);
}