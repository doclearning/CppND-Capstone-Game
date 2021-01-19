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

  void Start(Renderer &renderer, std::size_t target_frame_duration);

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

  std::vector<std::shared_ptr<GObject>> gameObjects {};

  std::size_t screenWidth; 
  std::size_t screenHeight;

  int score{0};
  int currentLevel{1};
  std::string levelFinishMessage {};

  const std::string ACHIEVED_LEVEL = "You reached level ";
  const std::string ACHIEVED_SCORE_0 = "You scored ";
  const std::string ACHIEVED_SCORE_1 = " points";
  const std::string COMMAND_CONTINUING_MESSAGE = "Press C to continue, or R to restart.";
  const std::string COMMAND_RESTARTING_MESSAGE = "Press R to restart.";

  GameState gameState;
  LevelState levelState;
};

#endif