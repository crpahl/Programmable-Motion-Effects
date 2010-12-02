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




class TAO
{
public:
	TAO(Object obj);
	~TAO(void);

//	void initTAO(vector<Object> objs);
	void initTAO();

	void animate();
	
	void drawObjects();

	void createBiPlanes();

	int obj_amt;


private:
	Object3D objects[MAX_OBJECTS];
	plane3D bi_planes[MAX_BIPLANES];
	vector<Sample> samps;
	Object obj;
};

#endif
