#ifndef G_OBJECT_H
#define G_OBJECT_H

#include <memory>
#include <vector>
#include "mathfu/vector.h"
#include "component.h"
#include "renderComponent.h"
#include "transform.h"
 
//I really don't understand why this is needed
class DefaultRenderComponent;

class GObject {

public: 
    virtual void Update(){}; //I'm confused why this can't be pure virtual

    //JAQ_Query do I need to std::move the arguments here
    GObject(std::string &&nameIn, mathfu::Vector<float, 2> &&positionIn) : name(nameIn), transform(positionIn){}

    void AddComponent(DefaultRenderComponent &&component){

        components.emplace_back(component);
    }

    //void RemoveComponent(IComponent component){

        //JAQ_Todo: 
            //Remove from list
            //Deregister it from things if required
            //Destroy component
    //}

    
    std::string name;
    Transform transform;
    std::vector<DefaultRenderComponent> components {};

private:

};

#endif