#include "TAO.h"
#include "Parser.h"
#include "Object3D.h"
#include <vector>
#include <iostream>

bool biPlane3D::operator==(biPlane3D &b){
    if(( this->points[0] == b.points[0]  &&
         this->points[1] == b.points[1] )||
       ( this->points[0] == b.points[1] &&
         this->points[1] == b.points[0] )

       )
        return true;
    return false;
}


TAO::TAO(){
}

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
    int totalPlanepts;
    int count = 0;
    int t;
    //Get the initital samples
    for(int i = 0; i < this->obj_amt - 1; i++){
        // this->objects[i]; this will be the initital object
        int temp = this->objects[i].getTotal_Planes();
        for(int l = 0; l < this->objects[i].getTotal_Planes(); l ++){
            totalPlanepts = this->objects[i].getPlane(l).amt_verts;
            for(int r = 0; r < totalPlanepts ; r++){
                biPlane3D newbiPlane;
                newbiPlane.time1 = this->objects[i].getTime();
                newbiPlane.time2 = this->objects[i + 1].getTime();

                newbiPlane.points[0] = this->objects[i].getPlane(l).points[r];
                newbiPlane.points[1] = this->objects[i].getPlane(l).points[(r + 1)% totalPlanepts];
                newbiPlane.points[2] = this->objects[i + 1].getPlane(l).points[r];
                newbiPlane.points[3] = this->objects[i + 1].getPlane(l).points[(r + 1)% totalPlanepts];

                newbiPlane.colors[0] = this->objects[i].getPlane(l).colors[r];
                newbiPlane.colors[1] = this->objects[i].getPlane(l).colors[(r + 1)% totalPlanepts];
                newbiPlane.colors[2] = this->objects[i + 1].getPlane(l).colors[r];
                newbiPlane.colors[3] = this->objects[i + 1].getPlane(l).colors[(r + 1)% totalPlanepts];

                t = count;
                bool fma = false;
                for(int s = 0; s < t; s++)
                {
                    if(newbiPlane == bi_planes[s])
                    {
                        fma = true;
                        break;
                    }
                }

                if(!fma){
                    this->bi_planes[count] = newbiPlane;
                    count++;
                }
            }

        }

    }

    this->biPlanes_amt = count;
}
	

void TAO::drawBiPlanes(){


    for(int i = 0; i < this->biPlanes_amt; i++){
        glColor4f(0 ,0 , 1, 0.3);
        glBegin(GL_QUADS);
            glVertex3f(this->bi_planes[i].points[0].x, this->bi_planes[i].points[0].y, this->bi_planes[i].points[0].z);
            glVertex3f(this->bi_planes[i].points[2].x, this->bi_planes[i].points[2].y, this->bi_planes[i].points[2].z);
            glVertex3f(this->bi_planes[i].points[3].x, this->bi_planes[i].points[3].y, this->bi_planes[i].points[3].z);
            glVertex3f(this->bi_planes[i].points[1].x, this->bi_planes[i].points[1].y, this->bi_planes[i].points[1].z);
        glEnd();
        glFlush();
    }

}

void TAO::drawObjects(){

	for (int i=0; i < this->obj_amt; i++){
		this->objects[i].drawObject();
	}

}
