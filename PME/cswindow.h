#ifndef CSWINDOW_H
#define CSWINDOW_H
#include <QGLWidget>
#include <QtGui>
#include <cstdlib> 
#include <ctime> 
#include "TAO.h"
#include <vector>
#include "Parser.h"
#define PI 3.14159
using namespace std;

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

        //void animateObjects(TAO tao, int ind);
        //void animate(TAO tao);

        bool displayPatches;
        bool lock;
        Parser *p;
	QPoint lastPos;
	GLfloat rotX;
	GLfloat rotY;
};
#endif
