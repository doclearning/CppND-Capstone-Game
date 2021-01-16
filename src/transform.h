 #ifndef TRANSFORM_H
 #define TRANSFORM_H
 
 #include "mathfu/vector.h"
 
 //JAQ_Query Should this be passing by reference, or maybe r-value reference
struct Transform {

    Transform(){}
    Transform(mathfu::Vector<float, 3> positionIn) : position(positionIn), forward(mathfu::Vector<float, 3>(0, -1, 0)){};

    mathfu::Vector<float, 3> position;
    float zAxisAngle = 0;
    mathfu::Vector<float, 3> forward;

    ///Physics utility methods

    // inline void AddScaledVector(mathfu::Vector<float, 3> &vector, float scalar){

    //     position = vector * scalar;
    // }
};

#endif