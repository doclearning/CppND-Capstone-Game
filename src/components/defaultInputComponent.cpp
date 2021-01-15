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

void DefaultInputComponent::Notified(const SDL_Keycode &notification){

  std::cout << "Observer: ";
  float tempFactor = 5;

  switch (notification) {
    case SDLK_UP:
      std::cout << "Up\n";
      transform.position += transform.forward * tempFactor;
      break;

    case SDLK_DOWN:
      std::cout << "Down\n";
      transform.position -= transform.forward * tempFactor;
      break;

    case SDLK_LEFT:
      std::cout << "Left\n";
      transform.zAxisAngle -= 0.0872665;
      break;

    case SDLK_RIGHT:
      std::cout << "Right\n";
      transform.zAxisAngle += 0.0872665;
      break;

  }
}

DefaultInputComponent::~DefaultInputComponent(){

    auto &controller = Controller::instance();
    controller.Detach(this);
}