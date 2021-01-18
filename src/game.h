#ifndef GAME_H
#define GAME_H

#include <vector>
#include "SDL.h"
#include "renderer.h"
#include "defaultInputComponent.h"

enum class GameState {notrunning, running, ending, transitioning, restarting};
enum class LevelState {running, passed, failed};

class Game {
 public:
  Game(std::size_t screenWidth, std::size_t screenHeight);
  void Run(Renderer &renderer, std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

  //JAQ_Todo put this in cpp
  void SetGameState(GameState gameStateIn){
    gameState = gameStateIn;
  }
  
  void SetLevelState(LevelState levelStateIn, std::string message){

    if(levelStateIn == levelState)
      return;
    
    if(levelStateIn != LevelState::running)
      LevelEnded(message);

    levelState = levelStateIn;
  }

  void LevelEnded(std::string);

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