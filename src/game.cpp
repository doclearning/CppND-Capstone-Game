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

Game::Game(std::size_t screenWidthIn, std::size_t screenHeightIn) : screenWidth(screenWidthIn), screenHeight(screenHeightIn), gameState(GameState::notrunning) {
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

  //JAQ_Todo eventually have variable ground
  float groundOffset = 10;
  auto groundSpawnPosition = mathfu::Vector<float, 3>(screenWidth/2, screenHeight-groundOffset, 0);
  auto ground = std::make_shared<Ground>("Ground", std::move(groundSpawnPosition), screenWidth, screenHeight);
  gameObjects.push_back(ground);

  float randomPadWidth = std::uniform_int_distribution<int>(25, 100)(randomEngine);
  float randomPadHeight = std::uniform_int_distribution<int>(10, 25)(randomEngine);

  auto padYPosition = (groundSpawnPosition.y-randomPadHeight/2);
  auto padSpawnPosition = mathfu::Vector<float, 3>(std::uniform_int_distribution<int>(30.0, screenWidth-30)(randomEngine), padYPosition, 0);
  //auto padSpawnPosition = mathfu::Vector<float, 3>(screenWidth/2, screenHeight/2+100, 0);
  auto pad = std::make_shared<Pad>("Pad", std::move(padSpawnPosition), randomPadWidth, randomPadHeight);
  gameObjects.push_back(pad);

  //JAQ_Todo Randomise this at the top of the screen
  auto shipSpawnPosition = mathfu::Vector<float, 3>(screenWidth/2, screenHeight/2, 0);
  auto ship = std::make_shared<Ship>(*this, "PlayerShip", std::move(shipSpawnPosition));
  gameObjects.push_back(ship);
  
  float deltaTime = 0;
  int frame_count = 0;
  SetGameState(GameState::running);

  //Core loop
  while (gameState == GameState::running) {
    frame_start = SDL_GetTicks();

    //JAQ_Future should set up game.h as an observer as well, and handle events like that
    //Handle closing window
    SetGameState(controller.HandleClientInput());

    //Handle user key presses
    GameState updatedGameState = controller.HandleGameInput();

    // if(levelState == LevelState::running && updatedGameState == GameState::transitioning)
    //   SetGameState(updatedGameState);

    collisionHandler.ProcessCollisions();
    
    Update(deltaTime);

    renderer.FrameBegin();
    for(auto &gobject : gameObjects){
      for(auto &component : gobject->components){
        //if(instanceof<DefaultRenderComponent>(*component)){ //JAQ_Query Confused why this doesn't work
          component->Draw(renderer);
        //}
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

    frame_end = SDL_GetTicks();
    deltaTime = static_cast<float>(frame_end-frame_start)*0.001f;
  }
}

void Game::LevelEnded(std::string message){
  //Draw UI

  std::cout << message << "\n";
}

void Game::Update(float deltaTime) {

  for(auto &gobject : gameObjects){
    gobject->Update(deltaTime);
  }
}

void Game::UpdateWindowDecoration(Renderer &renderer, Uint32 frame_count, Uint32 frame_duration, Uint32 frame_end, Uint32 frame_start, Uint32 title_timestamp){
// Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }
}

int Game::GetScore() const { return score; }