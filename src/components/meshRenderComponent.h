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
    virtual void Update() override{};

    void SetMesh(SDL_Point *pointsIn, std::size_t numVerticesIn, mathfu::Vector<int, 4> &&rgbaIn){

        numVertices = numVerticesIn;
        modelSpacePoints = pointsIn;
        
        worldSpacePoints = new SDL_Point[numVertices];
        std::copy(modelSpacePoints, modelSpacePoints + numVerticesIn, worldSpacePoints);

        rgba = std::move(rgbaIn); //JAQ_Query is the move necessary here, or is it automatic because it's an rvr?

        hasMesh = true;
    }

    void Rotate();

private:
    void UpdateWorldSpaceMesh();

    Transform &transform;
    SDL_Point *modelSpacePoints;
    std::size_t numVertices;
    bool hasMesh = false;

    mathfu::Vector<int, 4> rgba;
    const mathfu::Vector<float, 3> rotationAxis;
    float currentZAxisAngle = 0;

    SDL_Point *worldSpacePoints;
};

#endif