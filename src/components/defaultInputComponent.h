#ifndef DEFAULT_INPUT_COMPONENT_H
#define DEFAULT_INPUT_COMPONENT_H

#include <memory>
#include <list>
#include "SDL.h"
#include "observer.h"
#include "component.h"

class DefaultInputComponent : public IComponent/*, public ISubject<SDL_Keycode>*/{

public:
    DefaultInputComponent(Transform &transformIn) : transform(transformIn){};
    virtual void Draw(Renderer &renderer) override{};

    void HandleInput(bool &running);

    // void Attach(IObserver<SDL_Keycode> *observer) override;
    // void Detach(IObserver<SDL_Keycode> *observer) override;
    // void Notify(SDL_Keycode) override;

private:
    Transform &transform;
    //std::list<IObserver<SDL_Keycode> *> list_observer_;
  
};

#endif



