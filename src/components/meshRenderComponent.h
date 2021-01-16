#ifndef MESH_RENDER_COMPONENT_H
#define MESH_RENDER_COMPONENT_H

#include <memory>
#include "SDL.h"
#include "component.h"
#include "renderer.h"
#include "mathfu/quaternion.h"

class Renderer;

//JAQ_Todo clear pointers in this class when destroyed
class MeshRenderComponent : public IComponent {

public:
    MeshRenderComponent(Transform &transformIn) : transform(transformIn), rotationAxis(0.0, 0.0, 1.0){};
    virtual void Draw(Renderer &renderer) override;
    virtual void Update(float deltaTime) override{};

    void SetMesh(std::vector<mathfu::Vector<float, 3>> meshIn, mathfu::Vector<int, 4> &&rgbaIn){

    
        modelSpace = std::move(meshIn);
        worldSpace = modelSpace;
        meshCache = new SDL_Point[modelSpace.size()];
        numVertices = modelSpace.size();

        rgba = std::move(rgbaIn); //JAQ_Query is the move necessary here, or is it automatic because it's an rvr?

        hasMesh = true;
    }

   

private:
    void UpdateWorldSpaceMesh();
    void UpdateMeshCache();
    void Rotate();

    Transform &transform;
    
    std::vector<mathfu::Vector<float, 3>> modelSpace {};
    std::vector<mathfu::Vector<float, 3>> worldSpace {};
    SDL_Point *meshCache;

    std::size_t numVertices;
    bool hasMesh = false;

    mathfu::Vector<int, 4> rgba;
    const mathfu::Vector<float, 3> rotationAxis;
    float currentZAxisAngle = 0;
};

#endif