#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "ship.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();

  void FrameBegin();
  void FrameEnd();
 
  void UpdateWindowTitle(int score);
  void UpdateWindowTitle(int score, int level);

  //JAQ_Query Is this OK to do? Is there a new pointer allocation? If so, fairly cheap if then out of scope quickly?
  SDL_Renderer* GetRenderContext(){
    return sdl_renderer;
  }

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;

};

#endif