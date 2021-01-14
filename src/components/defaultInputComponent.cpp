#include "defaultInputComponent.h"
#include <iostream>
#include "mathfu/constants.h"

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

  std::cout << "transform position = " << transform.position[0] << "," << transform.position[1] << "\n";
}