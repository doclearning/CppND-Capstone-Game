#include "defaultInputComponent.h"
#include <iostream>
#include "mathfu/constants.h"
#include "controller.h"

//Uses the Controller singleton to attach to it as an IObserver
DefaultInputComponent::DefaultInputComponent(Transform &transformIn) : transform(transformIn){

    auto &controller = Controller::instance();
    controller.Attach(this);
}

void DefaultInputComponent::Update(){
}

void DefaultInputComponent::Notified(const Uint8 *state){

  //JAQ_TODO Make member variables
  float tempFactor = 5;

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
    transform.position += transform.forward * tempFactor;
  }
  
  if (state[SDL_SCANCODE_S]) {
    count++;
    transform.position -= transform.forward * tempFactor;
  }

  if(count > 0)
    std::cout << "\n";
}

DefaultInputComponent::~DefaultInputComponent(){

    auto &controller = Controller::instance();
    controller.Detach(this);
}