 #ifndef TRANSFORM_H
 #define TRANSFORM_H
 
 #include "mathfu/vector.h"
 
struct Transform {

    Transform(){}
    Transform(mathfu::Vector<float, 3> positionIn) : position(positionIn), forward(mathfu::Vector<float, 3>(0, -1, 0)){};

    mathfu::Vector<float, 3> position;
    float zAxisAngle = 0;
    mathfu::Vector<float, 3> forward;
};

#endif