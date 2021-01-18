cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} src src/components src/gobjects src/utils include)

add_executable(LanderClone src/main.cpp src/game.cpp src/controller.cpp src/collisionHandler.cpp src/renderer.cpp src/gobjects/ship.cpp src/gobjects/ground.cpp src/components/defaultRenderComponent.cpp src/components/defaultInputComponent.cpp src/components/meshRenderComponent.cpp src/components/physicsEntityComponent.cpp src/components/boxColliderComponent.cpp)

string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(LanderClone ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
