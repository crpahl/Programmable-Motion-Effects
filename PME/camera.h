//
// Author: Herb Yang, March 9, 2010
//
#ifndef CAMERA_H
#define CAMERA_H

#include <stdlib.h>
#include <time.h>
#include "Ray.h"
#include "Vector.h"

// The screen resolution is defined as type screen_res_t
typedef unsigned short screen_res_t;
#define RANGE 10000

struct ONB{
    Vector u, v, w;
};

/*struct Ray{
    //Vector o; // origin of the ray
    Vector o;
    Vector d; // direction of travel - should be normalized
    //Vector getPosition(const float &k);// get the coordinates with a value of k (the parameter value)
    //float distance(const Vector &point);// get the distance of the point from the origin of the ray
};*/

class Camera {
public:
    Ray ray2;
    Vector eye,		// eye is the location of the camera
    up,			// up is the up vector
    gaze;			// gaze is the direction of the camera
    ONB basis;		// basis is the orthonormal basis
    float s;		// s is the distance of the image plane from the centre of projection
    float au,av,	// a(u,v) are the lower left corner of the image plane (viewing rectangle)
    bu,bv;		// b(u,v) are the upper right corner of the image plane (viewing rectangle) (see lecture notes)
    screen_res_t Nx, Ny;// Nx, Ny, are the number of pixels in the x and y direction of the image plane
    Camera(); // default constructor
    Camera(
            Vector up,  Vector gaze,  Vector eye,
            float viewDist,
            float ruX,  float ruY,// ruX, ruY are the coordinates of the upper right corner of the image plane
            float llX,  float llY,// llX, llY are the coordinates of the lower left corner of the image image
            screen_res_t X,  screen_res_t Y);
    int initCamera(
            Vector up,  Vector gaze,  Vector eye,
            float viewDist,
            float ruX,  float ruY,
            float llX,  float llY,
            screen_res_t X,  screen_res_t Y);

    Ray getRayThroughPixel( screen_res_t x, screen_res_t y);// create a ray through a pixel at (x,y)
    void createONB(const Vector &a , const Vector &b);    // create an Orthonormal Basis system from a and b
    Vector fromCameraToWorld(Vector &pos);				  // given the location the camera coordinate system, return the coordinates
    // in the world coordinate system

};

#endif
