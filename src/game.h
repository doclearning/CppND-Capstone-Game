#ifndef GAME_H
#define GAME_H

#include <vector>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "ship.h"

class Game {
 public:
  Game(std::size_t screenWidth, std::size_t screenHeight);
  void Run(Renderer &renderer, std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:

  void Update();

  //Ship ship;

  std::vector<Ship> gameObjects {};

  std::size_t screenWidth; 
  std::size_t screenHeight;

  int score{0};

  //Ship ship;
  Controller controller {};
};

#endif