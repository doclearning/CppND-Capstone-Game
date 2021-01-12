#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "ship.h"

class Game {
 public:
  Game(std::size_t screenWidth, std::size_t screenHeight);
  void Run(Controller &controller, Renderer &renderer, std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Ship ship;
  std::size_t screenWidth; 
  std::size_t screenHeight;

  //std::random_device dev;
  //std::mt19937 engine;
  //std::uniform_int_distribution<int> random_w;
  //std::uniform_int_distribution<int> random_h;

  int score{0};

  void Update();
};

#endif