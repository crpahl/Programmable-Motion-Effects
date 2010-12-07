/*
    Authors: Adel Lari, Clinton Pahl, Date: 07/2010

    This class stores the representation of the time aggregate
    object TAO. It is composed of objects and bilinear patches
    and contains the appropiate methods to draw the TAO itself.
*/

#pragma once

#ifndef TAO_H
#define TAO_H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Parser.h"
#include "Object3D.h"
#include <time.h>
#include <math.h>
#include <vector>

#define MAX_OBJECTS 100
#define MAX_BIPLANES 300

#define FPS 25



struct biPlane3D{
        float time1,time2;
        point3D points[4];
        color3D colors[4];


        bool operator==(biPlane3D &b);
};



class TAO
{
public:
        TAO();
	TAO(Object obj);
	~TAO(void);

//	void initTAO(vector<Object> objs);
	void initTAO();

	void animate();
	
        void drawObjects();

        Object3D getObject(int i);
	void createBiPlanes();
        void drawBiPlanes();

	int obj_amt;
        int biPlanes_amt; //amount of biPlanes!
        biPlane3D bi_planes[MAX_BIPLANES];

private:
        //Samples of the same object at different times
        Object3D objects[MAX_OBJECTS];

        //biPlane3D bi_planes[MAX_BIPLANES];
	vector<Sample> samps;
        //Object we get from the parser, contains all the samples
        Object obj;
};

#endif
