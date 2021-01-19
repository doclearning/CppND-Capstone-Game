#ifndef BOX_COLLIDER_COMPONENT_H
#define BOX_COLLIDER_COMPONENT_H

#include "gobject.h"
#include "component.h"
#include "mathfu/vector.h"
#include "mathfu/glsl_mappings.h"
#include "mathfu/constants.h"

class Renderer;

class BoxColliderComponent : public IComponent {

public:
    BoxColliderComponent(Transform &transformIn, GObject &gobjectIn);
    virtual void Draw(Renderer &renderer) override{};
    virtual void Update(float deltaTime) override;

    void SetModelspaceBounds (mathfu::vec2 boundsXIn, mathfu::vec2 boundsYIn);
    mathfu::vec2 GetWorldSpaceBoundsX();
    mathfu::vec2 GetWorldSpaceBoundsY();

    bool IsStatic(){
        return isStatic;
    }

    void SetStatic(bool isStaticIn){
        isStatic = isStaticIn;
    }

    ~BoxColliderComponent();

    GObject &gobject;

private:

    mathfu::vec2 modelspaceBoundsX;
    mathfu::vec2 modelspaceBoundsY;

    Transform &transform;
    bool isStatic;
};

#endif



