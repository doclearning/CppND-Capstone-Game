#include "renderComponent.h"
#include <iostream>

// DefaultRenderComponent::DefaultRenderComponent(){

// }

void DefaultRenderComponent::Draw(Renderer &renderer) {

  //std::cout << "Rendering DefaultRenderComponent\n";

  SDL_Rect block;
  block.w = 20;
  block.h = 20;

  auto position = transform.position;

  block.x = static_cast<int>(100);
  block.y = static_cast<int>(100);
  
  SDL_SetRenderDrawColor(renderer.GetRenderContext(), 255, 0, 0, 255);

  SDL_RenderFillRect(renderer.GetRenderContext(), &block);

  // Update Screen
  //SDL_RenderPresent(renderer.GetRenderContext());
}
