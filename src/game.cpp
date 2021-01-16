#include "game.h"
#include <iostream>
#include "SDL.h"
#include "mathfu/vector.h"
#include "mathfu/glsl_mappings.h"
#include "meshRenderComponent.h"
#include "physicsEntityComponent.h"

//JAQ_Todo read this from a file
static std::vector<mathfu::Vector<float, 3>> meshModel {
  mathfu::vec3{-8, 8, 0},
  mathfu::vec3{0, -16, 0},
  mathfu::vec3{8, 8, 0},
  mathfu::vec3{0, 0, 0},
  mathfu::vec3{-8, 8, 0}
};

Game::Game(std::size_t screenWidthIn, std::size_t screenHeightIn) : screenWidth(screenWidthIn), screenHeight(screenHeightIn) {
}

void Game::Run(Renderer &renderer, std::size_t target_frame_duration) {

  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_work_done_end;
  Uint32 frame_end;
  Uint32 frame_work_done_duration;

  float deltaTime = 0;

  int frame_count = 0;
  bool running = true;

  auto &controller = Controller::instance();

  //JAQ_Todo Randomise this at the top of the screen
  auto shipSpawn = mathfu::Vector<float, 3>(screenWidth/2, screenHeight/2, 0);

  auto ship = std::make_shared<Ship>("PlayerShip", std::move(shipSpawn));
  gameObjects.push_back(ship);

  ship->AddComponent<DefaultInputComponent>();
  
  auto shipPhysicsComponent = ship->AddComponent<PhysicsEntityComponent>();
  shipPhysicsComponent->SetMass(2.0);
  shipPhysicsComponent->SetVelocity(mathfu::Vector<float, 3>(0.00003, 0.00004, 0.0));
  shipPhysicsComponent->SetAcceleration(mathfu::Vector<float, 3>(0.0, 1.0, 0.0));
  shipPhysicsComponent->SetDamping(0.99);
  shipPhysicsComponent->ClearAccumulator();

  //JAQ_Query This would be better in the component constructor, but need some clever variadic template/parameter pack thing perhaps?
  auto shipRenderComponent = ship->AddComponent<MeshRenderComponent>();
  shipRenderComponent->SetMesh(meshModel, mathfu::Vector<int, 4>(0, 255, 0, 255));
  
  //Core loop
  while (running) {
    frame_start = SDL_GetTicks();

    controller.HandleInput(running);
    
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

    //JAQ_Todo Improve all this frame-timing stuff. It's not good. 
    //Unlock framerate
    //Use delta times for translations etc, put in singleton, and use for all frame-dependent calculations
    //Separate thread for rendering, gameplay, physics
    frame_work_done_end = SDL_GetTicks();
    frame_work_done_duration = frame_work_done_end - frame_start;
    

    //Delay to hit target framerate
    if (frame_work_done_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_work_done_duration);
    }

    frame_end = SDL_GetTicks();
    deltaTime = static_cast<float>(frame_start-frame_end)/1000.0;
  }
}

void Game::Update(float deltaTime) {
  //if (!ship.alive) return;

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