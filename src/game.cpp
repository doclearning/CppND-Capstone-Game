#include "game.h"
#include <iostream>
#include "SDL.h"
#include "mathfu/vector.h"

Game::Game(std::size_t screenWidth, std::size_t screenHeight) {
}

void Game::Run(Renderer &renderer, std::size_t target_frame_duration) {

  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  //confused why this doesn't work: static_cast<float>(screenWidth/2), static_cast<float>(screenHeight/2)
  auto shipSpawn = mathfu::Vector<float, 2>(320, 240);

  std::cout << "Ship spawn location = " << shipSpawn[0] << ", " << shipSpawn[1] << "\n";

  auto ship = std::make_shared<Ship>("PlayerShip", std::move(shipSpawn));
  gameObjects.push_back(ship);

  ship->AddComponent<DefaultRenderComponent>();
  //JAQ_TODO Need to attach the controller as a component
  
  
  

  controller.Attach(ship.get()); //Kind of weird sending a raw pointer to this

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running);
    Update();
    renderer.FrameBegin();

    for(auto &gobject : gameObjects){
      for(auto &component : gobject->components){
        //if(instanceof<DefaultRenderComponent>(*component)){ //JAQ_Query Confused why this doesn't work
          component->Draw(renderer);
        //}
      }
    }

    renderer.FrameEnd();

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::Update() {
  //if (!ship.alive) return;

  for(auto &gobject : gameObjects){

    gobject->Update();
  }

}

int Game::GetScore() const { return score; }