 #ifndef TRANSFORM_H
 #define TRANSFORM_H
 
 #include "mathfu/vector.h"
 
 //JAQ_Query Should this be passing by reference, or maybe r-value reference
struct Transform {

    Transform(){}
    Transform(mathfu::Vector<float, 2> positionIn) : position(positionIn){};

    mathfu::Vector<float, 2> position;
    float zAxisAngle = 0;
};

#endif