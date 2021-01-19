#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height)
    : screen_width(screen_width),
      screen_height(screen_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

  // Create Window
  sdl_window = SDL_CreateWindow("Lander", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::FrameBegin(){

  //Set background render color and clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
  SDL_RenderClear(sdl_renderer);
  SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 255, 255);
}

void Renderer::FrameEnd(){
  
  //Draw frame
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score) {
  std::string title{"Lander --- Score: " + std::to_string(score)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::UpdateWindowTitle(int score, int level) {
  std::string title{"Lander --- Level: " + std::to_string(level) + ", Score: " + std::to_string(score)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
