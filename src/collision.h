 #ifndef COLLISION_H
 #define COLLISION_H
 
 #include "mathfu/vector.h"
 #include "boxColliderComponent.h"
 
 //Decided that making copies of the vectors here was safer, and not a common occurance.
struct Collision {

    Collision(std::shared_ptr<BoxColliderComponent> colliderAIn, std::shared_ptr<BoxColliderComponent> &colliderBIn, mathfu::vec3 &&velocityAIn, mathfu::vec3 &&velocityBIn, mathfu::vec3 forwardAIn, mathfu::vec3 forwardBIn) : 
        colliderA(colliderAIn), colliderB(colliderBIn), velocityA(std::move(velocityAIn)), velocityB(std::move(velocityBIn)), forwardA(forwardAIn), forwardB(forwardBIn){}

    std::shared_ptr<BoxColliderComponent> colliderA;
    std::shared_ptr<BoxColliderComponent> colliderB;

    mathfu::vec3 velocityA;
    mathfu::vec3 velocityB;

    mathfu::vec3 forwardA;
    mathfu::vec3 forwardB;
};

#endif