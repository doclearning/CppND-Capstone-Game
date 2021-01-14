#include "defaultRenderComponent.h"
#include <iostream>

// DefaultRenderComponent::DefaultRenderComponent(){

// }

void DefaultRenderComponent::Draw(Renderer &renderer) {

  //std::cout << "Rendering DefaultRenderComponent\n";

  SDL_Rect block;
  block.w = 20;
  block.h = 20;

  //auto position = transform.position;

  block.x = static_cast<int>(transform.position[0]);
  block.y = static_cast<int>(transform.position[1]);
  
  SDL_SetRenderDrawColor(renderer.GetRenderContext(), 255, 0, 0, 255);

  SDL_RenderFillRect(renderer.GetRenderContext(), &block);

  // Update Screen
  //SDL_RenderPresent(renderer.GetRenderContext());
}
