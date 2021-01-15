#ifndef G_OBJECT_H
#define G_OBJECT_H

#include <memory>
#include <vector>
#include <iostream>

#include "mathfu/vector.h"
#include "component.h"
#include "defaultRenderComponent.h"
#include "transform.h"
 
//I really don't understand why this is needed
class DefaultRenderComponent;
class IComponent;

class GObject {

public: 
    virtual void Update(){

      for(auto &component : components){
        component->Update();
      }

    }

    //JAQ_Query do I need to std::move the arguments here
    GObject(std::string &&nameIn, mathfu::Vector<float, 3> &&positionIn) : name(nameIn), transform(positionIn){

        std::cout << "Spawning " << name << " at " << transform.position[0] << ", " << transform.position[1] << "\n";
    }

    //Templated method prevents me having to pass gobject.transform as a parameter to the IComponent object
    //The pointer is copied on the return to allow for setup of the object in the calling function
    //Quite neat, though means you can't use the constructor. Well, maybe there's a clever way to template that actually
    template <typename T>
    std::shared_ptr<T> AddComponent(){
        std::shared_ptr<T> addedComponent = std::make_shared<T>(transform);
        components.push_back(addedComponent);

        return addedComponent;
    }

    // template<typename T>
    // std::shared_ptr<T> GetComponent(){

    // }

    //Not sure how to specifiy the component
    //void RemoveComponent(IComponent component){

        //JAQ_Todo: 
            //Remove from list
            //Deregister it from things if required
            //Destroy component
    //}
    
    std::string name;
    Transform transform;

    //Vector of pointers, so that the derived type of IComponent is not stripped by the move constructor
    //when emplace_back or similar is called
    //Could switch to pimpl wrapped pointer here
    std::vector<std::shared_ptr<IComponent>> components {};

private:

};

#endif