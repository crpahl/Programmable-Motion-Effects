#include "cswindow.h"
#include <qgl.h>
#include <math.h>
#include <iostream>

CSWindow::CSWindow(QWidget *parent) : QGLWidget(parent)
{
	setFormat(QGLFormat(QGL::DoubleBuffer|QGL::DepthBuffer));
        setGeometry(100,100,800,500);
        setFocusPolicy(Qt::StrongFocus);    // Detect key events
        rotX = -145;
        rotY = -215;
}
void CSWindow::initializeGL()
{
        qglClearColor(Qt::white);
	glColor3f(1.0,1.0,1.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
}
void CSWindow::resizeGL(int width, int height)
{
        GLdouble aspect, theta, n, f, theta_radian, theta_2_radian, top, bott,left, right;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
        glViewport(0,0,(GLsizei) width, (GLsizei) height);
	aspect = (GLdouble)width/(GLdouble)height;
	theta = 60.0; theta_radian = theta*PI/180.0;
	theta_2_radian = theta_radian/2.0;
	n = 1.0;
        f = 1500.0;
	top = n*tan(theta_radian/2.0);
	bott = -top;
	right = top*aspect;
	left = -right;
        glFrustum(left,right, bott, top, n, f);
}
void CSWindow::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();
        glTranslatef(0,0,CameraPos);
        glRotatef(CameraRot[0],1,0,0);
        glRotatef(CameraRot[1],0,1,0);

	draw();
}

void CSWindow::draw()
{
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();

    //glTranslatef(100.0,0.0,-450.0);
    //glRotatef(rotX,1.0,0.0,0.0);
    //glRotatef(rotY,0.,1.0,0.0);

    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(1000,0,0);

        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,1000,0);

        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,1000);
     glEnd();
}
void CSWindow::mousePressEvent(QMouseEvent *event)
{
	lastPos = event->pos();
}
void CSWindow::mouseMoveEvent(QMouseEvent *event)
{
    GLfloat dx = GLfloat(event->x() - lastPos.x())/width();
    GLfloat dy = GLfloat(event->y() - lastPos.y())/height();

    if(event->buttons() & Qt::LeftButton)
    {
            rotX += 180*dx;
            rotY -= 180*dy;
            updateGL();
    }
    lastPos = event->pos();
}

void CSWindow::keyPressEvent(QKeyEvent *event)
{
    int dr= 5;
    float dx = .5f;
    switch(event->key()){
    case 16777234:			//left
        CameraRot[1] -= dr;
        break;
    case 16777236:
        CameraRot[1] += dr;
        break;
    case 16777235:
        CameraRot[0] += dr;
        break;
    case 16777237:
        CameraRot[0] -= dr;
        break;
    case 16777238:			//page up
        CameraPos += dx;
        break;
    case 16777239:			//page down
        CameraPos -= dx;
        break;
    case 16777216:
    case 27:
        exit(0);
        break;
    }
    printf("key %d\n" , event->key());
    updateGL();
}

