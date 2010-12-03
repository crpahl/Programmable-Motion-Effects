#pragma once

#ifndef TAO_H
#define TAO_H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Parser.h"
#include "Object3D.h"
#include <vector>

#define MAX_OBJECTS 100
#define MAX_BIPLANES 100


struct ray3D{
    point3D origin;
    //Direction should be normalized
    point3D direction;
    float distance;

};

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

	void createBiPlanes();
        void drawBiPlanes();

	int obj_amt;


private:
        //Samples of the same object at different times
        Object3D objects[MAX_OBJECTS];

        int biPlanes_amt; //amount of biPlanes!
        biPlane3D bi_planes[MAX_BIPLANES];
	vector<Sample> samps;
        //Object we get from the parser, contains all the samples
        Object obj;
};

#endif
