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

  mathfu::Vector<float, 2> tempFactor(10, 10);

  switch (notification) {
    case SDLK_UP:
      std::cout << "Up\n";

      transform.position += -mathfu::kAxisY2f*tempFactor;
      break;

    case SDLK_DOWN:
      std::cout << "Down\n";
      transform.position += mathfu::kAxisY2f*tempFactor;
      break;

    case SDLK_LEFT:
      std::cout << "Left\n";
      transform.position += -mathfu::kAxisX2f*tempFactor;
      break;

    case SDLK_RIGHT:
      std::cout << "Right\n";
      transform.position += mathfu::kAxisX2f*tempFactor;
      break;

  }
}

DefaultInputComponent::~DefaultInputComponent(){

    auto &controller = Controller::instance();
    controller.Detach(this);
}