#ifndef GAME_H
#define GAME_H

#include <vector>
#include "SDL.h"
#include "observer.h"
#include "renderer.h"
#include "defaultInputComponent.h"

enum class GameState {notrunning, running, restarting, continuing, ending};
enum class LevelState {running, passed, failed};

class Game : public IObserver<Uint8>{
 public:
  Game(std::size_t screenWidth, std::size_t screenHeight);
  ~Game();

  void Start();

  void Run(Renderer &renderer, std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

  //JAQ_Todo put this in cpp
  void SetGameState(GameState gameStateIn);
  void SetLevelState(LevelState levelStateIn, std::string message);

  void LevelEnded(std::string);

  void Notified(const Uint8 *notification) override;

 private:

  void Update(float deltaTime);
  void UpdateWindowDecoration(Renderer &renderer, Uint32 frame_count, Uint32 frame_duration, Uint32 frame_end, Uint32 frame_start, Uint32 title_timestamp);

  std::vector<std::shared_ptr<GObject>> gameObjects {};

  std::size_t screenWidth; 
  std::size_t screenHeight;

  int score{0};

  GameState gameState;
  LevelState levelState;
};

#endif