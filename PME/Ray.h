//
// Author: Herb Yang, March 9, 2010
//
#ifndef RAY_H
#define RAY_H
#include "Vector.h"
class Ray {
public:
    Ray();
    ~Ray();

    Vector o; // origin of the ray
    Vector d; // direction of travel - should be normalized
    Vector getPosition(const float& k);// get the coordinates with a value of k (the parameter value)
    Vector reflectedDirection( const Vector& normal);// given the normal, get the reflected light direction
    float distance(const Vector& point);// get the distance of the point from the origin of the ray
};
#endif
