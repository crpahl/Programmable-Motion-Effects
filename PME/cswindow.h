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
    float t;
    color3D color;
    float x, y;
    //float tsleft, tsright;
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
        void displayOutput();
        void animate();
        void speed();
        void blur();
        void setThreshold(int f);
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

        //Different motion effects
        float alphaGen(float tn, float tf, float l, float alpha);
        float brighten(float tn, float tf, float l, float c);
        void motionBlur(float t, float f_time);
        void speedLines(Vector seed, float w, float l, float f_time);
        void stroboImage(float spacing, float length, float f_time);


        //Get rid of this useless method
        void setPixel(int x, int y, Color c);

        //void animateObjects(TAO tao, int ind);
        //void animate(TAO tao);

        Ray testRay;

        Vector *gaze, *up, *eye;
        Camera cam;                 //The camera that generates rays

        bool displayPatches;
        bool lock;
        bool displayGrid;
        bool output;
        bool _animate;
        bool _speed;
        bool _blur;

        int w, h;
        float threshold;
        float time;

        Parser *p;
	QPoint lastPos;
	GLfloat rotX;
	GLfloat rotY;
};
#endif
