#include "meshRenderComponent.h"

#include<algorithm>


void MeshRenderComponent::Draw(Renderer &renderer) {

  if(!hasMesh)
    return;

  Rotate();

  UpdateWorldSpaceMesh();

  SDL_SetRenderDrawColor(renderer.GetRenderContext(), rgba[0], rgba[1], rgba[2], rgba[3]);

  SDL_RenderDrawLines(renderer.GetRenderContext(), worldSpacePoints, numVertices);

}

void MeshRenderComponent::UpdateWorldSpaceMesh(){
  
  int xOffset = static_cast<int>(transform.position[0]);
  int yOffset = static_cast<int>(transform.position[1]);

  for(int i = 0; i < numVertices; ++i){

    worldSpacePoints[i].x = modelSpacePoints[i].x + xOffset;
    worldSpacePoints[i].y = modelSpacePoints[i].y + yOffset;
  }
}


void MeshRenderComponent::Rotate(){

  float rotationDelta = transform.zAxisAngle-currentZAxisAngle;
  currentZAxisAngle += rotationDelta;

  std::cout << "Angle = " << currentZAxisAngle << "\n";

    for(int i = 0; i < numVertices; ++i){
        mathfu::Vector<float, 3> vector(modelSpacePoints[i].x, modelSpacePoints[i].y, 0.0f);
        mathfu::Quaternion<float> quaternion = mathfu::Quaternion<float>::FromEulerAngles(mathfu::Vector<float, 3>(0, 0, rotationDelta));//::FromAngleAxis(rotationDelta, rotationAxis);
        mathfu::Vector<float, 3> rotated_vector = quaternion * vector;

        modelSpacePoints[i].x = rotated_vector[0];
        modelSpacePoints[i].y = rotated_vector[1];
    }
}