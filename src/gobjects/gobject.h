#ifndef G_OBJECT_H
#define G_OBJECT_H

#include <memory>
#include <vector>
#include <iostream>
#include <deque>
#include <unordered_map>

#include "mathfu/vector.h"
#include "component.h"
#include "transform.h"
 
class IComponent;

enum GobjectType { gObject, ship, ground, pad };

class GObject {

public: 
    GObject(std::string &&nameIn, mathfu::Vector<float, 3> &&positionIn);

    virtual void Update(float deltaTime);

    //JAQ_Future Quite neat, though means you can't use the constructor. Possibly add variadic templactes/parameter packing

    //Templated method prevents me having to pass gobject.transform as a parameter to the IComponent object
    //The pointer is copied on the return to allow for setup of the object in the calling function
    template <typename T>
    std::shared_ptr<T> AddComponent(){
        std::shared_ptr<T> addedComponent = std::make_shared<T>(transform, *this);
        components.push_back(addedComponent);

        return addedComponent;
    }

    //Allows me to store all types in the same vector (with slicing avoidance below)
    template<typename T>
    std::shared_ptr<T> GetComponent(){

      for(auto component : components){
          if(dynamic_cast<T*>(component.get()) != nullptr)
            return std::dynamic_pointer_cast<T>(component);
      }

      return nullptr;
    }

    template<typename T>
    void RemoveComponent(){ 
        auto componentToRemove = GetComponent<T>();

        if(componentToRemove == nullptr)
          return;

        components.erase(std::remove(components.begin(), components.end(), componentToRemove), components.end());
    }
    
    std::string name;
    Transform transform;

    //Vector of pointers, so that the derived type of IComponent is not stripped by the move constructor
    //when emplace_back or similar is called
    //Could switch to pimpl wrapped pointer here
    std::vector<std::shared_ptr<IComponent>> components {};

    virtual GobjectType GetType() = 0;

};

#endif