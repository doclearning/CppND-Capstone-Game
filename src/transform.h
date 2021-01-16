 #ifndef TRANSFORM_H
 #define TRANSFORM_H
 
 #include "mathfu/vector.h"
 
 //JAQ_Query Should this be passing by reference, or maybe r-value reference
struct Transform {

    static constexpr float world_scale = 0.00000001f;

    Transform(){}
    Transform(mathfu::Vector<float, 3> positionIn) : position(positionIn), forward(mathfu::Vector<float, 3>(0, -1, 0)){};

    mathfu::Vector<float, 3> position;
    float zAxisAngle = 0;
    mathfu::Vector<float, 3> forward;
};

#endif