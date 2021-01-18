#include "pad.h"

#include <cmath>

#include "mathfu/vector.h"
#include "mathfu/glsl_mappings.h"
#include "mathfu/constants.h"
#include "meshRenderComponent.h"
#include "physicsEntityComponent.h"

Pad::Pad(std::string &&nameIn, mathfu::Vector<float, 3> &&spawnPosition, float width, float height) : GObject(std::move(nameIn), std::move(spawnPosition)){

  std::cout << "Pad created\n";

  auto &collisionHandler = CollisionHandler::instance();

  auto physicsComponent = AddComponent<PhysicsEntityComponent>();
  physicsComponent->SetMass(50.0);
  

  auto renderComponent = AddComponent<MeshRenderComponent>();
  auto meshModel = std::vector<mathfu::Vector<float, 3>> {{-static_cast<float>(width/2), -static_cast<float>(height/2), 0.0}, 
                                                          {-static_cast<float>(width/2), static_cast<float>(height/2), 0.0},
                                                          {static_cast<float>(width/2), static_cast<float>(height/2), 0.0},
                                                          {static_cast<float>(width/2), -static_cast<float>(height/2), 0.0},
                                                          {-static_cast<float>(width/2), -static_cast<float>(height/2), 0.0}
                                                          };
  renderComponent->SetMesh(meshModel, mathfu::Vector<int, 4>(0, 255, 0, 255));

  auto collisionComponent = AddComponent<BoxColliderComponent>();
  collisionComponent->SetModelspaceBounds(mathfu::vec2(-static_cast<float>(width/2), static_cast<float>(width/2)), mathfu::vec2(-static_cast<float>(height/2), static_cast<float>(height/2)));
  collisionComponent->SetStatic(true);
  collisionHandler.AddCollider(collisionComponent);
}

void Pad::Update(float deltaTime) {
  GObject::Update(deltaTime);
}
