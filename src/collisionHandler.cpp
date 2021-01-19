#include "collisionHandler.h"

#include <iostream>
#include <string>
#include "physicsEntityComponent.h"

void CollisionHandler::ProcessCollisions(){

  if(colliders.size() < 2)
    return;

  for(int i = 0; i < colliders.size()-1; ++i){

    for(int j = i+1; j < colliders.size(); ++j){

      if(colliders[i]->IsStatic() && colliders[j]->IsStatic())
        continue;

      bool isCollision = ProcessCollision(colliders[i], colliders[j]);

      //JAQ_TD This is also really ugly (obvs). Though will only happen once a game really, so not my biggest concern.
      if(isCollision){

        auto colliderAPhysicsEntity = colliders[i]->gobject.GetComponent<PhysicsEntityComponent>();
        auto colliderBPhysicsEntity = colliders[j]->gobject.GetComponent<PhysicsEntityComponent>();

        assert(colliderAPhysicsEntity != nullptr);
        assert(colliderBPhysicsEntity != nullptr);

        auto velA = colliderAPhysicsEntity->GetVelocity();
        auto velB = colliderBPhysicsEntity->GetVelocity();     
        
        Collision collision(colliders[i], colliders[j], colliderAPhysicsEntity->GetVelocity(), colliderBPhysicsEntity->GetVelocity(), colliders[i]->gobject.transform.forward, colliders[j]->gobject.transform.forward);

        //JAQ_TD This is really not threadsafe in its lifetime. Vomit.
        Notify(&collision);

      }
    }
  }
}

bool CollisionHandler::ProcessCollision(std::shared_ptr<BoxColliderComponent> componentA, std::shared_ptr<BoxColliderComponent> componentB){
  
  auto xBoundsA = componentA->GetWorldSpaceBoundsX();
  auto yBoundsA = componentA->GetWorldSpaceBoundsY();
  auto xBoundsB = componentB->GetWorldSpaceBoundsX();
  auto yBoundsB = componentB->GetWorldSpaceBoundsY();

  if(xBoundsA.y >= xBoundsB.x && xBoundsB.y >= xBoundsA.x)
    if(yBoundsA.y >= yBoundsB.x && yBoundsB.y >= yBoundsA.x)
      return true;

  return false;
}

void CollisionHandler::AddCollider(std::shared_ptr<BoxColliderComponent> collider){
    colliders.push_back(collider);
}

void CollisionHandler::RemoveCollider(std::shared_ptr<BoxColliderComponent> collider){
    colliders.erase(std::remove(colliders.begin(), colliders.end(), collider), colliders.end());
}

void CollisionHandler::RemoveAllColliders(){
    colliders.clear();
}

void CollisionHandler::Attach(IObserver<Collision> *observer) {
  list_observer_.push_back(observer);
}
void CollisionHandler::Detach(IObserver<Collision> *observer) {

  auto exists = std::find(list_observer_.begin(), list_observer_.end(), observer) != list_observer_.end();

  if(std::find(list_observer_.begin(), list_observer_.end(), observer) != list_observer_.end());
    list_observer_.remove(observer);
}
void CollisionHandler::Notify(const Collision *collision) {
  std::list<IObserver<Collision> *>::iterator iterator = list_observer_.begin();
  while (iterator != list_observer_.end()) {
    (*iterator)->Notified(collision);
    ++iterator;
  }
}