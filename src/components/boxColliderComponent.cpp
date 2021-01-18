#include "boxColliderComponent.h"

BoxColliderComponent::BoxColliderComponent(Transform &transformIn, GObject &gobjectIn) : transform(transformIn), gobject(gobjectIn), modelspaceBoundsX(mathfu::kZeros2f), modelspaceBoundsY(mathfu::kZeros2f) {}

void BoxColliderComponent::Update(float deltaTime){}


void BoxColliderComponent::SetModelspaceBounds (mathfu::vec2 boundsXIn, mathfu::vec2 boundsYIn){
    modelspaceBoundsX = boundsXIn;
    modelspaceBoundsY = boundsYIn;
}

mathfu::vec2 BoxColliderComponent::GetWorldSpaceBoundsX(){

    return modelspaceBoundsX + transform.position.x;
}

mathfu::vec2 BoxColliderComponent::GetWorldSpaceBoundsY(){

    return modelspaceBoundsY + transform.position.y;
}


BoxColliderComponent::~BoxColliderComponent(){}