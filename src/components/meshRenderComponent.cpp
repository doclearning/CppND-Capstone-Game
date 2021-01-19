#include "meshRenderComponent.h"

MeshRenderComponent::MeshRenderComponent(Transform &transformIn, GObject &gobjectIn) : transform(transformIn), rotationAxis(0.0, 0.0, 1.0){};

void MeshRenderComponent::Draw(Renderer &renderer) {

  if(!hasMesh)
    return;

  Rotate();

  UpdateWorldSpaceMesh();

  UpdateMeshCache();

  SDL_SetRenderDrawColor(renderer.GetRenderContext(), rgba[0], rgba[1], rgba[2], rgba[3]);

  SDL_RenderDrawLines(renderer.GetRenderContext(), meshCache, numVertices);
}

void MeshRenderComponent::UpdateMeshCache(){
  for(int i = 0; i < numVertices; ++i){
    meshCache[i].x = static_cast<int>(worldSpace[i].x);
    meshCache[i].y = static_cast<int>(worldSpace[i].y);
  }
}

void MeshRenderComponent::UpdateWorldSpaceMesh(){

  for(int i = 0; i < numVertices; ++i){
    worldSpace[i] = modelSpace[i] + transform.position;
  }
}

void MeshRenderComponent::Rotate(){

  float rotationDelta = transform.zAxisAngle-currentZAxisAngle;
  currentZAxisAngle += rotationDelta;

  mathfu::Quaternion<float> quaternion = mathfu::Quaternion<float>::FromEulerAngles(mathfu::Vector<float, 3>(0, 0, rotationDelta));

  for(int i = 0; i < numVertices; ++i){
      modelSpace[i] = quaternion * modelSpace[i];
  }

  transform.forward = quaternion * transform.forward;
  transform.forward.Normalize();
}

ComponentType MeshRenderComponent::GetType(){
    return ComponentType::meshRenderComponent;
}

void MeshRenderComponent::SetMesh(std::vector<mathfu::Vector<float, 3>> meshIn, mathfu::Vector<int, 4> &&rgbaIn){


    modelSpace = std::move(meshIn);
    worldSpace = modelSpace;
    meshCache = new SDL_Point[modelSpace.size()];
    numVertices = modelSpace.size();

    rgba = std::move(rgbaIn); //JAQ_Query is the move necessary here, or is it automatic because it's an rvr?

    hasMesh = true;
}