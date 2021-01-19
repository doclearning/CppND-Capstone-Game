#include "game.h"

#include <iostream>
#include <random>

#include "SDL.h"
#include "mathfu/vector.h"
#include "mathfu/glsl_mappings.h"

#include "controller.h"
#include "collisionHandler.h"
#include "meshRenderComponent.h"
#include "physicsEntityComponent.h"
#include "boxColliderComponent.h"
#include "transform.h"
#include "ground.h"
#include "pad.h"
#include "ship.h"

Game::Game(std::size_t screenWidthIn, std::size_t screenHeightIn) : screenWidth(screenWidthIn), screenHeight(screenHeightIn), gameState(GameState::notrunning), levelState(LevelState::running) {

  Controller::instance().Attach(this);
}

Game::~Game(){
  Controller::instance().Detach(this);
}

void Game::Start(Renderer &renderer, std::size_t target_frame_duration){

  while(gameState != GameState::ending){

    SetGameState(GameState::notrunning);
    SetLevelState(LevelState::running, "Starting level " + std::to_string(currentLevel));
    Run(renderer, target_frame_duration);

    if(gameState == GameState::continuing){

      score += pow(currentLevel, 2);
      currentLevel++;
    }else{
      score = 0;
      currentLevel = 1;
    }
  }
}

void Game::Run(Renderer &renderer, std::size_t target_frame_duration) {

  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_work_done_end;
  Uint32 frame_end;
  Uint32 frame_work_done_duration;

  auto &controller = Controller::instance();
  auto &collisionHandler = CollisionHandler::instance();

  std::random_device randomDevice;
  std::mt19937 randomEngine(randomDevice());

  //JAQ_Future eventually have variable ground

  //Ground
  float groundOffset = 10;
  auto groundSpawnPosition = mathfu::Vector<float, 3>(screenWidth/2, screenHeight-groundOffset, 0);
  auto ground = std::make_shared<Ground>("Ground", std::move(groundSpawnPosition), screenWidth, screenHeight);
  gameObjects.push_back(ground);

  //Pad
  float randomPadWidth = std::uniform_int_distribution<int>(25, 100)(randomEngine);
  float randomPadHeight = std::uniform_int_distribution<int>(10, 25)(randomEngine);
  auto padYPosition = (groundSpawnPosition.y-randomPadHeight/2);
  auto padSpawnPosition = mathfu::Vector<float, 3>(std::uniform_int_distribution<int>(30.0, screenWidth-30)(randomEngine), padYPosition, 0);
  auto pad = std::make_shared<Pad>("Pad", std::move(padSpawnPosition), randomPadWidth, randomPadHeight);
  gameObjects.push_back(pad);

  //Ship
  float randomShipX = std::uniform_int_distribution<int>(30, screenWidth-30)(randomEngine);
  auto shipSpawnPosition = mathfu::Vector<float, 3>(randomShipX, 100, 0);
  auto ship = std::make_shared<Ship>(*this, "PlayerShip", std::move(shipSpawnPosition));
  gameObjects.push_back(ship);
  
  float deltaTime = 0;
  SetGameState(GameState::running);

  //Core loop
  while (gameState == GameState::running) {

    frame_start = SDL_GetTicks();

    //Handle closing window
    SetGameState(controller.HandleClientInput());
    controller.HandleGameInput();
    collisionHandler.ProcessCollisions();
    
    Update(deltaTime);

    renderer.FrameBegin();

    //JAQ_Future allow font size change
    if(levelState != LevelState::running){
      renderer.DrawText(levelFinishMessage, -150, 800);
      renderer.DrawText("---------", -75, 800);

      if(levelState == LevelState::passed){
        renderer.DrawText(COMMAND_CONTINUING_MESSAGE, 0, 800);
      }else{
        renderer.DrawText(ACHIEVED_LEVEL + std::to_string(currentLevel), 0, 800);
        renderer.DrawText(ACHIEVED_SCORE_0 + std::to_string(score) + ACHIEVED_SCORE_1, 25, 800);
        renderer.DrawText(COMMAND_RESTARTING_MESSAGE, 100, 800);
      }
      
    }

    for(auto &gobject : gameObjects){
      for(auto &component : gobject->components){
        component->Draw(renderer);
      }
    }
    renderer.FrameEnd();

    //JAQ_Future Improve all this frame-timing stuff. It's not good. 
    //Unlock framerate
    //Separate thread for rendering, gameplay, physics with deltaTime
    frame_work_done_end = SDL_GetTicks();
    frame_work_done_duration = frame_work_done_end - frame_start;

    //Delay to hit target framerate
    if (frame_work_done_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_work_done_duration);
    }

    renderer.UpdateWindowTitle(score, currentLevel);

    frame_end = SDL_GetTicks();
    deltaTime = static_cast<float>(frame_end-frame_start)*0.001f;
  }

  gameObjects.clear();
  collisionHandler.RemoveAllColliders();
}

void Game::SetGameState(GameState gameStateIn){
  gameState = gameStateIn;
}

void Game::SetLevelState(LevelState levelStateIn, std::string message){

  if(levelStateIn == levelState)
    return;

  levelState = levelStateIn;

  levelFinishMessage = std::move(message);
}

void Game::Update(float deltaTime) {

  for(auto &gobject : gameObjects){
    gobject->Update(deltaTime);
  }
}

int Game::GetScore() const { return score; }

void Game::Notified(const Uint8 *state){

  if(levelState == LevelState::failed || levelState == LevelState::passed)
    if (state[SDL_SCANCODE_R]) {
      SetGameState(GameState::restarting);
    }

  if(levelState == LevelState::passed)
    if (state[SDL_SCANCODE_C]) {
      SetGameState(GameState::continuing);
    }
}