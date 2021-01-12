#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "component.h"

class AbstractRenderComponent : public IComponent{

public:
    virtual void Draw() = 0;
};

#endif