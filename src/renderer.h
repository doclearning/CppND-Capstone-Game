#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "ship.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();

  void FrameBegin();
  void FrameEnd();

  void DrawText(std::string message, int verticalCenterOffset, int wrapWidth);
 
  void UpdateWindowTitle(int score);
  void UpdateWindowTitle(int score, int level);

  //JAQ_Query Is this OK to do? Is there a new pointer allocation? If so, fairly cheap if then out of scope quickly?
  SDL_Renderer* GetRenderContext(){
    return sdl_renderer;
  }

 private:

  bool LoadFont();

  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  SDL_Texture *sdl_texture;

  const std::size_t screen_width;
  const std::size_t screen_height;

  //Text Rendering stuff
  SDL_Surface *surfaceText = NULL;
  SDL_Surface *screen = NULL;
  SDL_Event event;
  TTF_Font *font = NULL;
  SDL_Color textColor = { 0, 255, 0 };

};

#endif