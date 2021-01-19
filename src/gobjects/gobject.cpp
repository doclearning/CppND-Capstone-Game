#include "gobject.h"
 
GObject::GObject(std::string &&nameIn, mathfu::Vector<float, 3> &&positionIn) : name(nameIn), transform(positionIn){

    std::cout << "Spawning " << name << " at " << transform.position[0] << ", " << transform.position[1] << "\n";
}

void GObject::Update(float deltaTime){

  for(auto &component : components){
    component->Update(deltaTime);
  }
}

GobjectType GObject::GetType(){return GobjectType::gObject;}
