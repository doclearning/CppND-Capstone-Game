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

  //Initialize SDL_ttf
  if( TTF_Init() == -1 ){
    std::cerr << "SDL_TTF could not initialise\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";    
  }                             

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

  if(!LoadFont()){

    std::cerr << "Loading font failed\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_FreeSurface(surfaceText);
  TTF_CloseFont( font );
  TTF_Quit();
  IMG_Quit();
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

void Renderer::DrawText(std::string message, int verticalCenterOffset, int wrapWidth){

  int textWidth;
  int textHeight;
  TTF_SizeText(font, message.c_str(), &textWidth, &textHeight);

  //Handle different lengths of text
  //int wrapWidth = 800;
  int rectHeight = static_cast<float>(std::ceil(static_cast<float>(textWidth)/static_cast<float>(wrapWidth)))*textHeight;
  rectHeight = std::max(textHeight, rectHeight) + 1;
  int rectWidth = std::min(textWidth, wrapWidth);

  surfaceText = TTF_RenderText_Blended_Wrapped(font, message.c_str(), textColor, wrapWidth);

  sdl_texture = SDL_CreateTextureFromSurface(sdl_renderer, surfaceText);

  SDL_Rect Message_rect;
  Message_rect.x = screen_width/2 - rectWidth/2;
  Message_rect.y = screen_height/2 - rectHeight/2 + verticalCenterOffset;
  Message_rect.w = rectWidth;
  Message_rect.h = rectHeight;

  SDL_RenderCopy(sdl_renderer, sdl_texture, NULL, &Message_rect);
}

void Renderer::UpdateWindowTitle(int score) {
  std::string title{"Lander --- Score: " + std::to_string(score)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::UpdateWindowTitle(int score, int level) {
  std::string title{"Lander --- Level: " + std::to_string(level) + ", Score: " + std::to_string(score)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

bool Renderer::LoadFont(){
    
    //JAQ_Todo move filename into header
    font = TTF_OpenFont( "../ARCADE.ttf", 28 );

    if( font == NULL )
        return false;
    
    //If everything loaded fine
    return true;    
}
