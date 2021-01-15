#include "defaultRenderComponent.h"
#include <iostream>


void DefaultRenderComponent::Draw(Renderer &renderer) {


  SDL_Rect block;
  block.w = 20;
  block.h = 20;

  block.x = static_cast<int>(transform.position[0]);
  block.y = static_cast<int>(transform.position[1]);
  
  SDL_SetRenderDrawColor(renderer.GetRenderContext(), 255, 0, 0, 255);

  SDL_RenderFillRect(renderer.GetRenderContext(), &block);

}
