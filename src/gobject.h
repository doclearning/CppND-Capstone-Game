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

    //Should component here be a shared pointer, or moved here
    void AddComponent(DefaultRenderComponent &&defaultRenderComponent){

        //JAQ_Todo: 
            //add component to list
            //Give component transform
            //Give it anything else required
        components.emplace_back(defaultRenderComponent);
        

        //DefaultRenderComponent &&component
    }

    //void RemoveComponent(IComponent component){

        //JAQ_Todo: 
            //Remove from list
            //Deregister it from things if required
            //Destroy component
    //}

    //JAQ_Query Should this be a shared pointer, so that all components get passed a pointer to it?
    std::string name;
    Transform transform;
    std::vector<DefaultRenderComponent> components {};

private:

};

#endif