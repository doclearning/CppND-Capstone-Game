#include "ship.h"

#include <cmath>

#include "mathfu/constants.h"
#include "mathfu/utilities.h"
#include "mathfu/vector.h"
#include "mathfu/glsl_mappings.h"

#include "meshRenderComponent.h"
#include "physicsEntityComponent.h"
#include "defaultInputComponent.h"

//JAQ_Todo read these from a file
static std::vector<mathfu::Vector<float, 3>> shipMeshModel {
  mathfu::vec3{-8, 8, 0},
  mathfu::vec3{0, -16, 0},
  mathfu::vec3{8, 8, 0},
  mathfu::vec3{0, 0, 0},
  mathfu::vec3{-8, 8, 0}
};

Ship::Ship(std::string &&nameIn, mathfu::Vector<float, 3> &&spawnPosition) : GObject(std::move(nameIn), std::move(spawnPosition)){

  std::cout << "Ship created\n";

  auto &collisionHandler = CollisionHandler::instance();
  collisionHandler.Attach(this);

  AddComponent<DefaultInputComponent>();
  
  auto physicsComponent = AddComponent<PhysicsEntityComponent>();
  physicsComponent->SetMass(50.0);
  physicsComponent->SetVelocity(mathfu::Vector<float, 3>(0.0, 0.0, 0.0));
  physicsComponent->SetAcceleration(mathfu::Vector<float, 3>(0.0, 10.0, 0.0));
  physicsComponent->SetDamping(0.99f);
  physicsComponent->ClearAccumulator();

  //JAQ_Query This would be better in the component constructor, but need some clever variadic template/parameter pack thing perhaps?
  auto renderComponent = AddComponent<MeshRenderComponent>();
  renderComponent->SetMesh(shipMeshModel, mathfu::Vector<int, 4>(0, 255, 0, 255));

  auto collisionComponent = AddComponent<BoxColliderComponent>();
  collisionComponent->SetModelspaceBounds(mathfu::vec2(-8, 8), mathfu::vec2(-16, 8));
  collisionHandler.AddCollider(collisionComponent);

}

void Ship::Update(float deltaTime) {
  GObject::Update(deltaTime);
}

//JAQ_TD This whole thing is pretty ugly. Should all be nicely typed and clever. Running out of time.
void Ship::Notified(const Collision *collision){

  std::cout << "Collision observed in ship object: ";

  //Find out if it's with a pad or the ground
  // if(collision->colliderA->gobject.GetType() == GetType()){
  //   std::cout << "ColliderA is the ship\n";
  // }else if(collision->colliderB->gobject.GetType() == GetType()){
  //   std::cout << "ColliderB is the ship\n";
  // }
  std::cout << "Collider A = " << collision->colliderA->gobject.GetType() << "\n";
  std::cout << "Collider B = " << collision->colliderB->gobject.GetType() << "\n";

  auto impactVelocity = (collision->velocityA.Length() + collision->velocityB.Length());
  auto impactAngle = mathfu::AngleHelper(collision->forwardA, collision->forwardB);

  if(impactVelocity < 22 && impactAngle < 0.0872665){
    std::cout << "  Ship landed at " << impactVelocity << "m/s and angle " << impactAngle << "\n";
    GetComponent<PhysicsEntityComponent>()->ZeroAll();

  }else{
    std::cout << "  Ship crashed at " << impactVelocity << "m/s and angle " << impactAngle << "\n";
    GetComponent<PhysicsEntityComponent>()->ZeroAll();
  }

  //auto &collisionHandler = CollisionHandler::instance();
  //collisionHandler.Detach(this);
}

Ship::~Ship(){

  auto &collisionHandler = CollisionHandler::instance();

  //JAQ_Todo check if detached first
  collisionHandler.Detach(this);
}
