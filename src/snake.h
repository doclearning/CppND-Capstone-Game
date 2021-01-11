#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
#include "observer.h"
#include "mathfu/vector.h"

class Snake : public IObserver<SDL_Keycode> {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        position(grid_width / 2, grid_height / 2){}

  void Update();

  //void GrowBody();
  //bool SnakeCell(int x, int y);

  void Notified(const SDL_Keycode &notification) override;

  Direction direction = Direction::kUp;

  float speed{1.0};
  int size{1};
  bool alive{true};

  mathfu::Vector<float, 2>& GetPosition(){
    return position;
  }

 private:

  mathfu::Vector<float, 2> position;

  bool growing{false};
  int grid_width;
  int grid_height;

  void Translate(const mathfu::Vector<float, 2> translation);
};

#endif