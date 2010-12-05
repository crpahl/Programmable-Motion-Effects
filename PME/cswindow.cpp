#include "cswindow.h"
#include <qgl.h>
#include <math.h>
#include <iostream>

TAO taos[10];
bool pixels[600*500];
int num_taos;

CSWindow::CSWindow(QWidget *parent) : QGLWidget(parent)
{
	setFormat(QGLFormat(QGL::DoubleBuffer|QGL::DepthBuffer));
        setGeometry(100,100,600,500);
        setFocusPolicy(Qt::StrongFocus);
        rotX = -145;
        rotY = -215;
        displayPatches = false;
        lock = false;
        p = NULL;

        //setting the up and gaze vectors of the camera
        gaze = new Vector(1450.0, 1000.0, 2500.0);
        up = new Vector(0.0,1.0,0.0);
        eye = new Vector(1450.0, 1000.0, 2501.0);
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
        glLoadIdentity();

        GLdouble aspect, theta, n, f, theta_radian, theta_2_radian, top, bott,left, right;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

        glViewport(0,0,(GLsizei) width, (GLsizei) height);

	aspect = (GLdouble)width/(GLdouble)height;
	theta = 60.0; theta_radian = theta*PI/180.0;
	theta_2_radian = theta_radian/2.0;
	n = 1.0;
        f = 5000.0;
	top = n*tan(theta_radian/2.0);
	bott = -top;
	right = top*aspect;
	left = -right;

        glFrustum(left,right, bott, top, n, f);

        cam.initCamera(*up, *gaze, *eye, n, top, right, bott, left, width, height);
}

void CSWindow::paintGL()
{
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	draw();
}

void CSWindow::draw()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(0,0,0);

    if(lock)
        gluLookAt(1450, 1000, 2501, 1450, 1000, 2500, 0, 1, 0);
    else
    {
        //re-orientating the camera to view scene
        glRotatef(180,1.0,0.0,0.0);
        glRotatef(180,0.0,1.0,0.0);
        //roating based on mouse movements
        glRotatef(rotY,1.0,0.0,0.0);
        glRotatef(rotX,0.,1.0,0.0);
        //translating initial camera position
        glTranslatef(-500,-500,-1500);
        //translating based on key movements
        glTranslatef(CameraPosX,0,0);
        glTranslatef(0,CameraPosY,0);
        glTranslatef(0,0,CameraPosZ);
    }

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

    if(num_taos > 0)
     {
        //this->render();
        ////////////////////////////////////AHHHHHHHHHHHHHHHHH//////////////////////////

        glColor3f(0,0,0);
        glBegin(GL_LINES);
            glVertex3f(testRay.o.x(),testRay.o.y(),testRay.o.z() );
            glVertex3f(testRay.d.x()*5000,testRay.d.y()*5000,testRay.d.z()*5000);
        glEnd();

        //glPointSize(2.0);
        glBegin(GL_POINTS);
        int count, count2;
        count = count2 = 0;
        for(int n = 0; n < cam.Ny; n++)
            for(int m = 0; m < cam.Nx; m++){
                if(pixels[n*cam.Nx+m]){
                    glColor3f(1.0,0,0);
                    glVertex2i(m,n);
                    count++;
                }
                else{
                    glColor3f(0,1,0);
                    glVertex2i(m,n);
                    count2++;
                }
        }
        cout << "count: " << count << "count2: " << count2 << endl;
        glEnd();
        glFlush();

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
    float dx= 20;

    switch(event->key()){
        case 16777234:			//left
            CameraPosX -= dx;
            break;
        case 16777236:                  //right
            CameraPosX += dx;
            break;
        case 16777235:			//up key
            CameraPosZ -= dx;
            break;
        case 16777237:			//down key
            CameraPosZ += dx;
            break;
        case 16777238:                  //page up
            CameraPosY -= dx;
            break;
        case 16777239:                  //page down
            CameraPosY += dx;
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

void CSWindow::lockCamera()
{
    lock = !lock;
    updateGL();
}

void CSWindow::showPatches()
{
    displayPatches = !displayPatches;
    updateGL();
}

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
            trace();
            updateGL();
        }
    }
}

void CSWindow::debug()
{
    if(p != NULL)
        (*p).printObjects();
}


/***** Helper Methods *****/

void CSWindow::trace()
{
    Vector p00,p01,p10,p11,r,d,srt;
    screen_res_t currX, currY;
    screen_res_t x, y;
    Ray currRay;

    x = cam.Nx;
    y = cam.Ny;

    int count = 0;
    int count2 = 0;

    for (currY = 0; currY < y; currY++)
    {
        for (currX = 0; currX < x; currX++)
        {
            currRay = cam.getRayThroughPixel(currX, currY);

            if(currX == 0 && currY == 0)
                currRay = cam.getRayThroughPixel(currX, currY);
            if(currX == 400 && currY == 400)
                currRay = cam.getRayThroughPixel(currX, currY);


            if(currX*currY == 100000)
            {
                testRay = currRay;
            }

            for(int i=0; i < num_taos; i++)
            {
                for(int k =0; k < taos[i].biPlanes_amt; k++)
                {
                        p00.x(taos[i].bi_planes[k].points[0].x);
                        p00.y(taos[i].bi_planes[k].points[0].y);
                        p00.z(taos[i].bi_planes[k].points[0].z);

                        p01.x(taos[i].bi_planes[k].points[1].x);
                        p01.y(taos[i].bi_planes[k].points[1].y);
                        p01.z(taos[i].bi_planes[k].points[1].z);

                        p10.x(taos[i].bi_planes[k].points[2].x);
                        p10.y(taos[i].bi_planes[k].points[2].y);
                        p10.z(taos[i].bi_planes[k].points[2].z);

                        p11.x(taos[i].bi_planes[k].points[3].x);
                        p11.y(taos[i].bi_planes[k].points[3].y);
                        p11.z(taos[i].bi_planes[k].points[3].z);

                        r.x(currRay.o.x()); r.y(currRay.o.y()); r.z(currRay.o.z());
                        d.x(currRay.d.x()); d.y(currRay.d.y()); d.z(currRay.d.z());

                        BilinearPatch dp(p00,p01,p10,p11);

                        if(dp.RayPatchIntersection(r,d,srt))
                        {
                            pixels[currY * x + currX] = true;
                            count2++;
                            break;
                        }
                        else
                        {
                            pixels[currY * x + currX] = false;
                            count++;
                        }
                }
            }


        }
    }

    //std::cerr << "count: " << count << "count2: " << count2 << endl;
}

// set the colour of the raw image at location x, y with colour c
//
void CSWindow::setPixel(int x, int y, Color c)
{
    /*int i;
    Color *p;
    p = rawImage;
    i = y*theCamera.Nx+x;

    p[i] = c;*/
}

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
        taos[i].drawObjects();
        if(displayPatches)
            taos[i].drawBiPlanes();
    }
    //glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //paintGL();
}

