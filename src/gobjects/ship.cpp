#include "ship.h"

#include <cmath>

#include "mathfu/constants.h"
#include "physicsEntityComponent.h"
#include "mathfu/utilities.h"

Ship::Ship(std::string &&nameIn, mathfu::Vector<float, 3> &&spawnPosition) : GObject(std::move(nameIn), std::move(spawnPosition)){

  std::cout << "Ship created\n";

  auto &collisionHandler = CollisionHandler::instance();
  collisionHandler.Attach(this);
}

void Ship::Update(float deltaTime) {
  GObject::Update(deltaTime);
}

//JAQ_TD This whole thing is pretty ugly. Should all be nicely typed and clever. Running out of time.
void Ship::Notified(const Collision *collision){

  std::cout << "Collision observed in ship object: ";

  //Find out if it's with a pad or the ground
  if(collision->colliderA->gobject.GetType() == GetType()){
    //std::cout << "ColliderA is the ship\n";
  }else if(collision->colliderB->gobject.GetType() == GetType()){
    //std::cout << "ColliderB is the ship\n";
  }

  auto impactVelocity = (collision->velocityA.Length() + collision->velocityB.Length());
  auto impactAngle = mathfu::AngleHelper(collision->forwardA, collision->forwardB);

  if(impactVelocity < 22 && impactAngle < 0.0872665){
    std::cout << "  Ship landed at " << impactVelocity << "m/s and angle " << impactAngle << "\n";
    GetComponent<PhysicsEntityComponent>()->ZeroAll();

  }else{
    std::cout << "  Ship crashed at " << impactVelocity << "m/s and angle " << impactAngle << "\n";
    GetComponent<PhysicsEntityComponent>()->ZeroAll();
  }
}

Ship::~Ship(){

  auto &collisionHandler = CollisionHandler::instance();
}
