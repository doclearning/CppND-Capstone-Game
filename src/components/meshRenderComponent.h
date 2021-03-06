#ifndef MESH_RENDER_COMPONENT_H
#define MESH_RENDER_COMPONENT_H

#include <memory>
#include "SDL.h"
#include "gobject.h"
#include "component.h"
#include "renderer.h"
#include "mathfu/quaternion.h"

class Renderer;

class MeshRenderComponent : public IComponent {

public:
    MeshRenderComponent(Transform &transformIn, GObject &gobjectIn);
    ~MeshRenderComponent();

    virtual void Draw(Renderer &renderer) override;
    virtual void Update(float deltaTime) override{};

    void SetMesh(std::vector<mathfu::Vector<float, 3>> meshIn, mathfu::Vector<int, 4> &&rgbaIn);

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