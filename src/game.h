#ifndef GAME_H
#define GAME_H

#include <vector>
#include "SDL.h"
#include "renderer.h"
#include "defaultInputComponent.h"

class Game {
 public:
  Game(std::size_t screenWidth, std::size_t screenHeight);
  void Run(Renderer &renderer, std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:

  void Update(float deltaTime);
  void UpdateWindowDecoration(Renderer &renderer, Uint32 frame_count, Uint32 frame_duration, Uint32 frame_end, Uint32 frame_start, Uint32 title_timestamp);

  std::vector<std::shared_ptr<GObject>> gameObjects {};

  std::size_t screenWidth; 
  std::size_t screenHeight;

  int score{0};
};

#endif