
#include "Object3D.h"
#include "Parser.h"
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>


//using namespace std;


point3D& point3D::operator=(MyPoint &b){
	//point3D a;
	x = b.x;
	y = b.y;
	z = b.z;

	return *this;
}

bool point3D::operator==(point3D &b){
    if(this->x == b.x && this->y == b.y && this->z == b.z)
        return true;
    return false;
}

color3D& color3D::operator=(Color &_b){
	//color3D a;
	
	r = _b.r;
	g = _b.g;
	b = _b.b;
	a = _b.a;

	return *this;
}

/*plane3D plane3D::operator=(Sample &b){
	//vector<Sample>	samples;
	

}*/

Object3D::Object3D(void)
{
}


Object3D::~Object3D(void)
{
}

float Object3D::getTime(){
	return time;
}

int Object3D::getTotal_Verts(){
	return total_verts;
}

int Object3D::getTotal_Planes(){
    return total_planes;
}

plane3D Object3D::getPlane(int i){
    return this->planes[i];
}

void Object3D::setTime(float t){
	this->time = t;
}

// Sets the total number of points used to create the object
void Object3D::setTotalVerts(){
	//this->total_verts = t;
	int count = 0;
	for(int i =0; i < this->total_planes; i++){
		count += this->planes[i].amt_verts;
	}

	this->total_verts = count;
}

// Sets the total number of planes used to create the object
void Object3D::setTotalPlanes(int t){
	this->total_planes = t;

}


void Object3D::setPlane(int i, plane3D a){
	this->planes[i] = a;
}
// Iterates through every point in the object to create a
// single array that can be used to render the object
void Object3D::makeDrawArray(){
	//int totalItr = this->total_verts*24;

	/*for (int i = 0; i < this->total_verts*3; i++)
		for(int j = 0; j < this->planes[i].amt_verts; j++){
			this->obj_verts[i] = this->planes[j].points->x;
			this->obj_verts[i + 1] = this->planes[j].points->y;
			this->obj_verts[i + 2] = this->planes[j].points->z;
			i = i + 2;		
		}*/
	int points = 0;
        for(int j = 0; j < total_planes; j++)
	{
                for(int i = 0;  i < planes[j].amt_verts; i++)
		{
			obj_verts[points++] = planes[j].points[i].x;
			obj_verts[points++] = planes[j].points[i].y;
			obj_verts[points++] = planes[j].points[i].z;
		}
	}

	int colors = 0;
        for(int j = 0; j < total_planes; j++)
	{
                for(int i = 0;  i < planes[j].amt_verts; i++)
		{
			obj_colors[colors++] = planes[j].colors[i].r;
			obj_colors[colors++] = planes[j].colors[i].g;
			obj_colors[colors++] = planes[j].colors[i].b;
			obj_colors[colors++] = planes[j].colors[i].a;
		}
	}
		
}

// Draws the Object
void Object3D::drawObject(){
	this->makeDrawArray();

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(4, GL_FLOAT,0,this->obj_colors);
	glVertexPointer(3, GL_FLOAT,0,this->obj_verts);

        if(this->total_planes > 1)
            glDrawArrays(GL_QUADS,0,this->total_verts);
        else
            glDrawArrays(GL_POLYGON,0,this->total_verts);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

}


