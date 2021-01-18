#ifndef BOX_COLLIDER_COMPONENT_H
#define BOX_COLLIDER_COMPONENT_H

#include "gobject.h"
#include "component.h"
#include "mathfu/vector.h"
#include "mathfu/glsl_mappings.h"
#include "mathfu/constants.h"

class Renderer;

//JAQ_todo probably have an IObserver here to grab collisions in the ship
class BoxColliderComponent : public IComponent {

public:
    BoxColliderComponent(Transform &transformIn, GObject &gobjectIn);
    virtual void Draw(Renderer &renderer) override{};
    virtual void Update(float deltaTime) override;

    ComponentType GetType(){
        return ComponentType::physicsEntityComponent;
    }

    void SetModelspaceBounds (mathfu::vec2 boundsXIn, mathfu::vec2 boundsYIn);
    mathfu::vec2 GetWorldSpaceBoundsX();
    mathfu::vec2 GetWorldSpaceBoundsY();

    ~BoxColliderComponent();

    GObject &gobject;

private:

    mathfu::vec2 modelspaceBoundsX;
    mathfu::vec2 modelspaceBoundsY;

    Transform &transform;
    
};

#endif



