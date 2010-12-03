#include "cswindow.h"
#include <qgl.h>
#include <math.h>
#include <iostream>

TAO taos[2];
int num_taos;

CSWindow::CSWindow(QWidget *parent) : QGLWidget(parent)
{
	setFormat(QGLFormat(QGL::DoubleBuffer|QGL::DepthBuffer));
        setGeometry(100,100,800,500);
        rotX = -145;
        rotY = -215;
        p = NULL;
}
void CSWindow::initializeGL()
{
        qglClearColor(Qt::white);
	glColor3f(1.0,1.0,1.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
        glFrustum(left,right, bott, top, n, f*3);
}
void CSWindow::paintGL()
{
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


        /*glLoadIdentity();

        glTranslatef(0,0,CameraPos);
        glRotatef(CameraRot[0],1,0,0);
        glRotatef(CameraRot[1],0,1,0);*/

	draw();
}

void CSWindow::draw()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0,0.0,-850.0);
    glRotatef(180, 1, 0, 0);
    glRotatef(rotX,1.0,0.0,0.0);
    glRotatef(rotY,0.,1.0,0.0);


    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(10000,0,0);

        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,10000,0);

        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,10000);
     glEnd();


     /*glColor3f(1.0,1.0,0);
     glBegin(GL_POLYGON);
             glVertex3f(0,0,0);
             glVertex3f(5,10,0);
             glVertex3f(10,0,0);
      glEnd();
      glFlush();*/

    if(num_taos > 0){
         this->render();
     }
}


/***** Mouse and Key Events *****/

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

/***** Connected Buttons *****/

void CSWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"), QDir::currentPath());

    if(!fileName.isEmpty())
    {
        //converint string to char
        QByteArray ba = fileName.toLatin1();
        char *c_str = ba.data();

        p = new Parser(c_str);

        if((*p).parse())
        {
            createTAOs();
            //render();
        }
    }
}

void CSWindow::debug()
{
    if(p != NULL)
        (*p).printObjects();
}


/***** Helper Methods *****/

void CSWindow::createTAOs()
{
    TAO *tao;
    vector<Object>::iterator i;
    vector<Object> obj = p->getObjects();

    for(i = obj.begin(); i != obj.end(); i++)
    {
        tao = new TAO(*i);
        tao->obj_amt = i->samples.size();
        tao->createBiPlanes();
        taos[num_taos++] = *tao;
    }
}

void CSWindow::render()
{
    //vector<TAO>::iterator i;
    //for(i = taos.begin(); i != taos.end(); i++)
    //glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    for(int i = 0; i < num_taos; i++)
    {
        //taos[i].drawObjects();
        taos[i].drawBiPlanes();

    }
    //glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //paintGL();
}
