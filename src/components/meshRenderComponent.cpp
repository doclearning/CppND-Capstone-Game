#include "meshRenderComponent.h"

#include<algorithm>


void MeshRenderComponent::Draw(Renderer &renderer) {

  if(!hasMesh)
    return;

  Rotate();

  UpdateWorldSpaceMesh();

  UpdateMeshCache();

  SDL_SetRenderDrawColor(renderer.GetRenderContext(), rgba[0], rgba[1], rgba[2], rgba[3]);

  SDL_RenderDrawLines(renderer.GetRenderContext(), meshCache, numVertices);

  // SDL_SetRenderDrawColor(renderer.GetRenderContext(), 255, 0, 0, rgba[3]);
  // int worldX = static_cast<int>(transform.position[0]);
  // int worldY = static_cast<int>(transform.position[1]);
  // SDL_RenderDrawLine(renderer.GetRenderContext(), worldX, worldY, worldX+(transform.forward[0]*20), worldY+(transform.forward[1]*20));
}

void MeshRenderComponent::UpdateMeshCache(){
  for(int i = 0; i < numVertices; ++i){
    meshCache[i].x = static_cast<int>(worldSpace[i].x);
    meshCache[i].y = static_cast<int>(worldSpace[i].y);
  }
}

void MeshRenderComponent::UpdateWorldSpaceMesh(){
  
  int xOffset = static_cast<int>(transform.position[0]);
  int yOffset = static_cast<int>(transform.position[1]);

  //JAQ_Todo Probably should add vectors here, but would then make more allocations
  for(int i = 0; i < numVertices; ++i){

    worldSpace[i].x = modelSpace[i].x + xOffset;
    worldSpace[i].y = modelSpace[i].y + yOffset;
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