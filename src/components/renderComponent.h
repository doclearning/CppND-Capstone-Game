#ifndef DEFAULT_RENDER_COMPONENT_H
#define DEFAULT_RENDER_COMPONENT_H

#include <memory>
#include "SDL.h"

#include "component.h"

class DefaultRenderComponent : public IComponent{

public:
    virtual void Draw(SDL_Renderer *myRenderer);

    SDL_Renderer *sdl_renderer;

    virtual void InitialiseTransform(Transform &transformIn) override{
        
        transform = transformIn;
    }

private:
    //std::shared_ptr<Transform>();
    Transform &transform;
};

#endif