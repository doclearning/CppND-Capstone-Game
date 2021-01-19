#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include <iostream>
#include <list>
#include <vector>
#include "observer.h"
#include "singleton.h"
#include "boxColliderComponent.h"
#include "collision.h"

class CollisionHandler : public Singleton<CollisionHandler>, public ISubject<Collision> {
 public:
  CollisionHandler(token) { std::cout << "CollisionHandler constructed" << std::endl; }

  void ProcessCollisions();

  void Attach(IObserver<Collision> *observer) override;
  void Detach(IObserver<Collision> *observer) override;
  void Notify(const Collision *state) override;

  //JAQ_TD should be generic
  void AddCollider(std::shared_ptr<BoxColliderComponent> collider);

  //JAQ_todo
  void RemoveCollider(std::shared_ptr<BoxColliderComponent> collider);
  void RemoveAllColliders();

  ~CollisionHandler() {  std::cout << "CollisionHandler destructed" << std::endl; }

 private:

  bool ProcessCollision(std::shared_ptr<BoxColliderComponent> componentA, std::shared_ptr<BoxColliderComponent> componentB);

  std::list<IObserver<Collision> *> list_observer_;

  //JAQ_TD should really take any sort of generic colliders, but running out of time
  std::vector<std::shared_ptr<BoxColliderComponent>> colliders {};
};

#endif