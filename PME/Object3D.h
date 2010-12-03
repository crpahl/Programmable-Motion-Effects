//#pragma once
#ifndef Object3D_H
#define Object3D_H
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Parser.h"

#define MAX_PLANE_POINTS 10
#define MAX_PLANE_AMOUNT 100
#define MAX_VERTICIES 100


struct point3D{
	float x;
	float y;
	float z;

	point3D& operator=(MyPoint &b);
        bool operator==(point3D &b);
};

struct color3D{
	float r;
	float g;
	float b;
	float a;

	color3D& operator=(Color &_b);
};

struct plane3D{
	int amt_verts; //Size of arrays holding both colors and points
	point3D points[MAX_PLANE_POINTS];
	color3D colors[MAX_PLANE_POINTS];

        //plane3D operator=(Sample &b);
};

class Object3D
{
public:
	//Set plane values in constructor!
	Object3D(void);
	~Object3D(void);

	void setTime(float t);
	float getTime();

        int getTotal_Verts();
        int getTotal_Planes();

        plane3D getPlane(int i);

        void drawObject();
	void makeDrawArray();

	void setTotalVerts();
	void setTotalPlanes(int t);

	void setPlane(int i, plane3D a);

	//void objIntersect();
	//plane3D planes[MAX_PLANE_AMOUNT];

private:
	float time;
	int total_planes;
	int total_verts;
	plane3D planes[MAX_PLANE_AMOUNT];
	GLfloat obj_colors[MAX_VERTICIES];
	GLfloat obj_verts[MAX_VERTICIES];
};

#endif
