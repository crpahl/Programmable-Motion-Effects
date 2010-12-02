#include "TAO.h"
#include "Parser.h"
#include "Object3D.h"
#include <vector>
#include <iostream>


TAO::TAO(Object obj)
{
	this->obj = obj;
	this->samps = this->obj.samples;
	initTAO();
}


TAO::~TAO(void)
{
}


void TAO::initTAO()
{
		point3D newPoint; 
		color3D newColor; 
		plane3D newPlane;

		vector<Sample>::iterator s;
		int z = 0;

		for(s = samps.begin(); s != samps.end(); s++)
		{
			Object3D *newObj = new Object3D;

			for(unsigned int j = 0; j < s->nPlanes; j++)
			{
				memset(&newPlane, 0, sizeof(plane3D));

				for(unsigned int k = 0; k < s->planes[j].nPoints; k++)
				{
					memset(&newPoint, 0, sizeof(point3D));
					memset(&newColor, 0, sizeof(color3D));

					newPoint = s->planes[j].points[k];
					if(obj.globalColor)
						newColor = obj.color;
					else
						newColor = s->planes[j].points[k].color;
						
					newPlane.colors[k] = newColor;
					newPlane.points[k] = newPoint;
				}
			
				newPlane.amt_verts = s->planes[j].nPoints;
				(*newObj).setPlane(j,newPlane);
			}
			(*newObj).setTotalPlanes(s->nPlanes);
			(*newObj).setTime(s->time);
			(*newObj).setTotalVerts();
			this->objects[z++] = *newObj;	
		}
	//this->objects[k].setTotalVerts();
}


void TAO::createBiPlanes(){
	//	plane3D planes[MAX_PLANE_AMOUNT];
	//  GLfloat obj_colors[MAX_VERTICIES];

	//struct plane3D{
	//int amt_verts; //Size of arrays holding both colors and points
	//point3D points[MAX_PLANE_POINTS];
	//color3D colors[MAX_PLANE_POINTS];
	

	/*for (int i=0; i < this->obj_amt-1; i++){
		this->objects[i];
	
	}*/



}
	



void TAO::drawObjects(){

	for (int i=0; i < this->obj_amt; i++){
		this->objects[i].drawObject();
	}

}