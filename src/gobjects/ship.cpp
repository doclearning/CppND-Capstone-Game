#include "ship.h"

#include <cmath>

#include "mathfu/constants.h"
#include "mathfu/utilities.h"
#include "mathfu/vector.h"
#include "mathfu/glsl_mappings.h"

#include "meshRenderComponent.h"
#include "physicsEntityComponent.h"
#include "shipInputComponent.h"
#include "controller.h"

//JAQ_Future read these from a file
static std::vector<mathfu::Vector<float, 3>> shipMeshModel {
  mathfu::vec3{-8, 8, 0},
  mathfu::vec3{0, -16, 0},
  mathfu::vec3{8, 8, 0},
  mathfu::vec3{0, 0, 0},
  mathfu::vec3{-8, 8, 0}
};

constexpr float RadToDeg(float radians){ 
    return radians * (180.0/3.141592653589793238463); 
} 

Ship::Ship(Game &gameIn, std::string &&nameIn, mathfu::Vector<float, 3> &&spawnPosition) : GObject(std::move(nameIn), std::move(spawnPosition)), game(gameIn), shipStopped(false), cleanedUp(false){

  std::cout << "Ship created\n";

  auto &collisionHandler = CollisionHandler::instance();
  collisionHandler.Attach(this);

  AddComponent<ShipInputComponent>();
  
  auto physicsComponent = AddComponent<PhysicsEntityComponent>();
  physicsComponent->SetMass(50.0);
  physicsComponent->SetVelocity(mathfu::Vector<float, 3>(0.0, 0.0, 0.0));
  physicsComponent->SetAcceleration(mathfu::Vector<float, 3>(0.0, 10.0, 0.0));
  physicsComponent->SetDamping(0.99f);
  physicsComponent->ClearAccumulator();

  auto renderComponent = AddComponent<MeshRenderComponent>();
  renderComponent->SetMesh(shipMeshModel, mathfu::Vector<int, 4>(0, 255, 0, 255));

  auto collisionComponent = AddComponent<BoxColliderComponent>();
  collisionComponent->SetModelspaceBounds(mathfu::vec2(-8, 8), mathfu::vec2(-16, 8));
  collisionHandler.AddCollider(collisionComponent);

}

void Ship::Update(float deltaTime) {
  GObject::Update(deltaTime);

  //Not really clean, but need to remove this here rather than in notified, as we can't remove those observers during the notify
  if(shipStopped && !cleanedUp)
    CleanUp();
}

void Ship::CleanUp(){

  RemoveCollisionHandler();
  RemoveInputHandler();

  cleanedUp = true;
}

//JAQ_TD This whole thing is pretty ugly. Should all be nicely typed and clever. Running out of time.
//JAQ_TD would be better if I knew the types of the colliders
void Ship::Notified(const Collision *collision){

  if(collision->colliderA->gobject.GetType() != GetType() && collision->colliderB->gobject.GetType() != GetType())
    return;

  shipStopped = true;
  auto impactVelocity = (collision->velocityA.Length() + collision->velocityB.Length());
  auto impactAngle = mathfu::AngleHelper(collision->forwardA, collision->forwardB);

  std::string outcome;
  LevelState updatedLevelState = LevelState::failed;

  if(collision->colliderA->gobject.GetType() == GobjectType::pad || collision->colliderB->gobject.GetType() == GobjectType::pad){

    bool acceptableSpeed = false; 
    bool acceptableAngle = false;

    //JAQ_TD The ship should not really be making these decisions. The game should.

    if(impactVelocity < MAX_IMPACT_VELOCITY)
      acceptableSpeed = true;

    if(impactAngle < MAX_IMPACT_ANGLE){
      acceptableAngle = true;
    }

    int angleInDegTruncated = static_cast<int>(RadToDeg(impactAngle));
    int velocityTruncated = static_cast<int>(impactVelocity);

    if(acceptableSpeed && acceptableAngle){
      outcome = "Well done! Ship landed. Velocity " + std::to_string(velocityTruncated) + "m/s and angle " + std::to_string(angleInDegTruncated) + " degrees from vertical";
      updatedLevelState = LevelState::passed;
    }else{

      outcome = "Unlucky. You crashed into the pad. Velocity " + std::to_string(velocityTruncated) + "m/s";
      if(!acceptableSpeed)outcome += " (too fast)";
      outcome += " and angle " + std::to_string(angleInDegTruncated) + " degrees from vertical";
      if(!acceptableAngle)outcome += " (too off-centre)";
    }
  }else{
    outcome = "Bad luck! You didn't make it to the pad";
  }

  GetComponent<PhysicsEntityComponent>()->ZeroAll();

  game.SetLevelState(updatedLevelState, outcome);
}

Ship::~Ship(){
  RemoveCollisionHandler();
}
void Ship::RemoveCollisionHandler(){
  CollisionHandler::instance().Detach(this);  
}

void Ship::RemoveInputHandler(){
  RemoveComponent<ShipInputComponent>();
}
