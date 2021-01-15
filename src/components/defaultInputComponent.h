#ifndef DEFAULT_INPUT_COMPONENT_H
#define DEFAULT_INPUT_COMPONENT_H

#include <memory>
#include <list>
#include "SDL.h"
#include "component.h"
#include "observer.h"

class Renderer;

class DefaultInputComponent : public IComponent, public IObserver<Uint8> {

public:
    DefaultInputComponent(Transform &transformIn);
    virtual void Draw(Renderer &renderer) override{};
    virtual void Update() override;

    void Notified(const Uint8 *notification) override;

    ~DefaultInputComponent();

private:
    Transform &transform;
};

#endif



