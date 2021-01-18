#include "ground.h"

#include <cmath>
#include "mathfu/vector.h"
#include "mathfu/glsl_mappings.h"
#include "mathfu/constants.h"
#include "meshRenderComponent.h"
#include "physicsEntityComponent.h"

Ground::Ground(std::string &&nameIn, mathfu::Vector<float, 3> &&spawnPosition, std::size_t screenWidth, std::size_t screenHeight) : GObject(std::move(nameIn), std::move(spawnPosition)){

  std::cout << "Ground created\n";

  auto &collisionHandler = CollisionHandler::instance();

  auto physicsComponent = AddComponent<PhysicsEntityComponent>();
  physicsComponent->SetMass(50.0);
  

  auto renderComponent = AddComponent<MeshRenderComponent>();
  auto meshModel = std::vector<mathfu::Vector<float, 3>> {{-static_cast<float>(screenWidth/2), 0.0, 0.0}, {static_cast<float>(screenWidth/2), 0.0, 0.0}};
  renderComponent->SetMesh(meshModel, mathfu::Vector<int, 4>(0, 255, 0, 255));

  auto collisionComponent = AddComponent<BoxColliderComponent>();
  collisionComponent->SetModelspaceBounds(mathfu::vec2(-static_cast<float>(screenWidth/2), static_cast<float>(screenWidth/2)), mathfu::vec2(static_cast<float>(0), static_cast<float>(10)));
  collisionComponent->SetStatic(true);
  collisionHandler.AddCollider(collisionComponent);
}

void Ground::Update(float deltaTime) {
  GObject::Update(deltaTime);
}
