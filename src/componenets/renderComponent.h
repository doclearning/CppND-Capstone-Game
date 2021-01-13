#ifndef DEFAULT_RENDER_COMPONENT_H
#define DEFAULT_RENDER_COMPONENT_H

#include <memory>
#include "SDL.h"

#include "component.h"

class DefaultRenderComponent : public IComponent{

public:
    void Draw(SDL_Renderer *myRenderer);

    SDL_Renderer *sdl_renderer;

private:
    //std::shared_ptr<Transform>();

};

#endif