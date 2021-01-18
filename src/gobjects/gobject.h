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
 
//JAQ_Issues Really need to better understand forward declaration
class IComponent;

//Check object is of class type
template<typename Base, typename T>
inline bool instanceof(const T&) {
  return std::is_base_of<Base, T>::value;
}

enum GobjectType { gObject, ship, ground, pad };

//JAQ_Todo Move functions into cpp
class GObject {

public: 
    virtual void Update(float deltaTime){

      for(auto &component : components){
        component->Update(deltaTime);
      }

    }

    //JAQ_Query do I need to std::move the arguments here
    GObject(std::string &&nameIn, mathfu::Vector<float, 3> &&positionIn) : name(nameIn), transform(positionIn){

        std::cout << "Spawning " << name << " at " << transform.position[0] << ", " << transform.position[1] << "\n";
    }

    //Templated method prevents me having to pass gobject.transform as a parameter to the IComponent object
    //The pointer is copied on the return to allow for setup of the object in the calling function
    //JAQ_Issue Quite neat, though means you can't use the constructor. Possibly add variadic templactes/parameter packing
    template <typename T>
    std::shared_ptr<T> AddComponent(){
        std::shared_ptr<T> addedComponent = std::make_shared<T>(transform, *this);
        components.push_back(addedComponent);

        return addedComponent;
    }

    //JAQ_Refactor Fix this. It's gross.
    template<typename T>
    std::shared_ptr<T> GetComponent(){

      auto componentName = typeid(T(transform, *this)).name();

      //JAQ_Query As this is iterating shared pointers, am I right to iterate without the reference?
      for(auto component : components){
        if(typeid(*(component.get())).name() == componentName)
          return std::dynamic_pointer_cast<T>(component);
      }

      return nullptr;
    }

    template<typename T>
    void RemoveComponent(){ 
        auto componentToRemove = GetComponent<T>();

        if(componentToRemove == nullptr)
          return;

        //components.(std::dynamic_pointer_cast<IComponent>(componentToRemove));
        components.erase(std::remove(components.begin(), components.end(), componentToRemove), components.end());
    }

    // void ForcePush(mathfu::Vector<float, 3> &&forceIn);
    // mathfu::Vector<float, 3> ForcePull();
    
    std::string name;
    Transform transform;

    //Vector of pointers, so that the derived type of IComponent is not stripped by the move constructor
    //when emplace_back or similar is called
    //Could switch to pimpl wrapped pointer here
    std::vector<std::shared_ptr<IComponent>> components {};

    virtual GobjectType GetType(){return GobjectType::gObject;}

};

#endif