#ifndef G_OBJECT_H
#define G_OBJECT_H

#include <memory>
#include <vector>
#include "mathfu/vector.h"
#include "component.h"
#include "transform.h"
 

class GObject {

public: 
    virtual void Update() = 0;

    GObject(mathfu::Vector<float, 2> &&positionIn) : transform(positionIn){}

    //Should component here be a shared pointer, or moved here
    //void AddComponent(IComponent component){

        //JAQ_Todo: 
            //add component to list
            //Give component transform
            //Give it anything else required
        
        
    //}

    //void RemoveComponent(IComponent component){

        //JAQ_Todo: 
            //Remove from list
            //Deregister it from things if required
            //Destroy component
    //}

    //JAQ_Query Should this be a shared pointer, so that all components get passed a pointer to it?
    Transform transform;

private:
    std::vector<IComponent> components {};
};

#endif