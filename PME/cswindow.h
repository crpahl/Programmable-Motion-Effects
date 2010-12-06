#ifndef CSWINDOW_H
#define CSWINDOW_H
#include <QGLWidget>
#include <QtGui>
#include <cstdlib> 
#include <ctime> 
#include "TAO.h"
#include "bilinear.h"
#include <vector>
#include "camera.h"
#include "Parser.h"
#include "Object3D.h"
#define PI 3.14159
using namespace std;

struct Trace{
    //Vector srt;
    float time;
    color3D color;
    float x, y;
};

class CSWindow : public QGLWidget
{
	Q_OBJECT
public: 
	CSWindow(QWidget *parent =0);

        float CameraPosX, CameraPosY, CameraPosZ;	// Camera Distance to Origin
        float CameraRot[4];				// Camera Rotation
signals:
	void setSlider(int r);
public slots:
        void open();
        void debug();
        void showPatches();
        void lockCamera();
        void setGrid();
protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
        void keyPressEvent(QKeyEvent *event);
private:

        void draw();
        void createTAOs();
        void render();
        void trace();
        void setPixel(int x, int y, Color c);

        //void animateObjects(TAO tao, int ind);
        //void animate(TAO tao);

        Ray testRay;

        Vector *gaze, *up, *eye;
        Camera cam;                 //The camera that generates rays
        bool displayPatches;
        bool lock;
        bool displayGrid;
        Parser *p;
	QPoint lastPos;
	GLfloat rotX;
	GLfloat rotY;
};
#endif
