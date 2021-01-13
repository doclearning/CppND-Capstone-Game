#include "renderComponent.h"

DefaultRenderComponent::DefaultRenderComponent(){

}

void DefaultRenderComponent::Draw(SDL_Renderer *sdl_renderer) {
  SDL_Rect block;
  block.w = 20;
  block.h = 20;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  auto position = transform.position;

  block.x = static_cast<int>(position[0]);
  block.y = static_cast<int>(position[1]);
  
  SDL_SetRenderDrawColor(sdl_renderer, 255, 0, 0, 255);

  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}