#include <iostream>
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{1280};
  constexpr std::size_t kScreenHeight{1024};

  Renderer renderer(kScreenWidth, kScreenHeight);
  Game game(kScreenWidth, kScreenHeight);
  game.Start(renderer, kMsPerFrame);
  std::cout << "Game Over man!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  return 0;
}