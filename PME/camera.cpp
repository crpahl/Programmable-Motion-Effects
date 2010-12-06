/*
Author: Herb Yang, March 9, 2010 - modified based on a version by Daniel Neilson
*/

#include "camera.h"
#include <string.h>
#include <iostream>
#include "Ray.h"

bool first;

Camera::Camera(){}

// Initialize the camera. Return 1 iff successful
// INITIALIZE:m _X _Y should be the values of the ViewPort.
// bu,bv,au,av should be the values of the frustrum.
Camera::Camera(			// constructor
        Vector _up,  Vector _gaze,  Vector _eye,
        float _viewDist,
        float _ruX,  float _ruY,
        float _llX,  float _llY,
        screen_res_t _X,  screen_res_t _Y) {

    eye = _eye;
    up = _up;
    gaze = _gaze;
    s = _viewDist;
    bu = _ruX;
    bv = _ruY;
    au = _llX;
    av = _llY;
    Nx = _X;
    Ny = _Y;
    createONB(gaze, up);// create the OMB basis vectors
}
// Initialize the camera. Return 1 iff successful
int Camera::initCamera(
        Vector _up,  Vector _gaze,  Vector _eye,
        float _viewDist,
        float _ruX,  float _ruY,
        float _llX,  float _llY,
        screen_res_t _X,  screen_res_t _Y) {
    first = true;

    eye = _eye;
    up = _up;
    gaze = _gaze;
    s = _viewDist;
    bu = _ruX;
    bv = _ruY;
    au = _llX;
    av = _llY;
    Nx = _X;
    Ny = _Y;
    createONB(gaze,up);// create the ONB basis vectors
    //first_time = true; // for random sampling
    return 1;
}
// Create and return a ray through the desired pixel - the ray direction is normalized. The origin of the
// ray is at the center of the camera or the eye location
Ray Camera::getRayThroughPixel( screen_res_t x, screen_res_t y)  {
    Vector pos;
    Ray ray;
    ray.o = eye;

    pos.x(au + ( ((bu-au)/(Nx-1) )*(x+0.5f) ));
    pos.y(av + ( ((bv-av)/(Ny-1) )*(y+0.5f) ));
    pos.z(-s);

    // Convert the uvw coordinates into xyz coordinates, and place the result
    // in the ray
    ray.d = fromCameraToWorld(pos);
    ray.d = ray.d - ray.o;

    ray.d.normalize();

    return ray;
} // getRayThroughPixel
void Camera::createONB(const Vector& a, const Vector& b)
{
    //following the steps layed out in the slides to get an orthonormal basis
    basis.w = -a;
    basis.w.normalize();
    basis.u = b.cross(basis.w);
    basis.u.normalize();
    basis.v = basis.w.cross(basis.u);
}
// transform from the camera coordinate system to the world coordinate system
Vector Camera::fromCameraToWorld(Vector &p)
{
    //following the steps in the slides to transform from the camera to the world coordinate system
    Vector transform;

    transform.x( p.x() * basis.u.x() + p.y() *basis.v.x() + p.z() *(int)basis.w.x() );
    transform.y( p.x() * basis.u.y() + p.y() *basis.v.y() + p.z() *(int)basis.w.y() );
    transform.z( p.x() * basis.u.z() + p.y() *basis.v.z() + p.z() *(int)basis.w.z() );

    return transform;
}
