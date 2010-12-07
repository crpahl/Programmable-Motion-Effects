#include "cswindow.h"
#include <qgl.h>
#include <math.h>
#include <iostream>

#define RESX 600
#define RESY 600
#define INF 999999999

TAO taos[10];
//bool pixels[RESX*RESY];
vector<Trace> pixelz[RESX*RESY];

int num_taos;

CSWindow::CSWindow(QWidget *parent) : QGLWidget(parent)
{
	setFormat(QGLFormat(QGL::DoubleBuffer|QGL::DepthBuffer));
        setGeometry(100,100,RESX,RESY);
        setFocusPolicy(Qt::StrongFocus);
        rotX = -145;
        rotY = -215;
        displayPatches = false;
        displayGrid = true;
        lock = false;
        output = false;
        _animate = false;
        _speed = true;
        _blur = false;
        p = NULL;

        //setting the up and gaze vectors of the camera
        gaze = new Vector(0.0, 0.0, -1.0);
        up = new Vector(0.0,1.0,0.0);
        eye = new Vector(0.0, 0.0, 0.0);
}
void CSWindow::initializeGL()
{
        qglClearColor(Qt::gray);
        //glColor3f(1.0,1.0,1.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void CSWindow::resizeGL(int width, int height)
{
        /*GLdouble aspect, theta, n, f, theta_radian, theta_2_radian, top, bott,left, right;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

        glViewport(0,0,(GLsizei) width, (GLsizei) height);

	aspect = (GLdouble)width/(GLdouble)height;
	theta = 60.0; theta_radian = theta*PI/180.0;
	theta_2_radian = theta_radian/2.0;
	n = 1.0;
        f = 7000.0;
	top = n*tan(theta_radian/2.0);
	bott = -top;
	right = top*aspect;
	left = -right;

        glFrustum(left,right, bott, top, n, f);

        cam.initCamera(*up, *gaze, *eye, n, top, right, bott, left, width, height);*/

        //Setting global width/height
        w = width;
        h = height;

        //Initializing viewport and frustrum
        GLdouble n, f;
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glViewport(0,0,(GLsizei) width, (GLsizei) height);

        n = 1;
        f = 7000;
        glFrustum(-1,1,-1,1, n, f);

        //Initializing the camera that will be used to project rays
        cam.initCamera(*up, *gaze, *eye, n, 1, 1, -1, -1, width, height);
}

void CSWindow::paintGL()
{
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	draw();
}

void CSWindow::draw()
{
    switch(_animate)
    {
        //Case where render mode is on, render animation or checkerboard scene
        //if no animation available to display
        case true:
        {

                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                gluOrtho2D(0.0, (GLfloat)w, 0.0, (GLfloat)h);
                glDisable(GL_DEPTH_TEST);
                //glEnable(GL_POINT_SMOOTH);
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();

                if(num_taos > 0 && _animate)
                {
                    //Animates speed lines
                    if(_speed)
                    {
                        Vector seed(.1,(threshold/2.0)+0.5,0);
                        this->speedLines(seed,4,4,time);
                    }
                    //Animates motion blur
                    else if(_blur)
                        this->motionBlur(4*threshold,time);
                }
                else
                {
                    int i,j,c;
                    GLubyte checkImage[h][w][3];

                    for(i=0; i <h; i++)
                        for(j =0; j < w; j++){
                            c = (((i&0x8)==0)^((j&0x8)==0))*255;
                            checkImage[i][j][0] = (GLubyte) c;
                            checkImage[i][j][1] = (GLubyte) c;
                            checkImage[i][j][2] = (GLubyte) c;
                    }

                    glShadeModel(GL_FLAT);
                    glPixelStorei(GL_UNPACK_ALIGNMENT,1);

                    glClear(GL_COLOR_BUFFER_BIT);
                    glRasterPos2i(0,0);

                    glDrawPixels(w,h, GL_RGB,GL_UNSIGNED_BYTE, checkImage);
                    glFlush();
                 }

            break;
        }
        case false:
        {

            glEnable(GL_DEPTH_TEST);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glColor3f(0,0,0);

            //Locks the camera to the position that rays are projected from
            if(lock)
            {
                //gluLookAt(0, 0, 0, 2500, 1000, -5000, 0, 1, 0);
                gluLookAt(0, 0, 0, gaze->x(), gaze->y(), gaze->z(), 0, 1, 0);
            }
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

            //Renders a grid for the coordinate axes
            if(displayGrid)
            {
                glColor4f(0,0,0,.5);
                glBegin(GL_LINES);
                    //glColor3f(1,0,0);
                    //glVertex3f(0,0,0);
                    for (int i = 300; i < 10000; i+=300){

                    glVertex3f(0,0,-i);
                    glVertex3f(10000,0,-i);


                    glVertex3f(0,0,-i);
                    glVertex3f(0,10000,-i);

                    glVertex3f(i,0,0);
                    glVertex3f(i,0,-10000);

                    glVertex3f(0,i,0);
                    glVertex3f(0,i,-10000);
                }
                 glEnd();

                 glBegin(GL_LINES);
                     glColor3f(1,0,0);
                     glVertex3f(0,0,0);
                     glVertex3f(10000,0,0);

                     glColor3f(0,1,0);
                     glVertex3f(0,0,0);
                     glVertex3f(0,10000,0);

                     glColor3f(0,0,1);
                     glVertex3f(0,0,0);
                     glVertex3f(0,0,-10000);

                 glEnd();
            }


            //Renders the 3D scene
            if(num_taos > 0)
            {
                this->render();   //Uncomment to render scene
            }
            break;
        }
        default:
            break;
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
    //printf("key %d\n" , event->key());
    updateGL();
}

/***** Helper Methods *****/

// Projects rays from the camera. For each intersection the
// appropiate algorithms are used to determine the properties
// that need to be stored in a pixel to render the 2D animation.
void CSWindow::trace()
{
    std::cout << "Begin trace..." << std::endl;
    Vector p00,p01,p10,p11,r,d,srt;
    color3D color1, color2, color;
    Trace fragment;
    screen_res_t currX, currY;
    screen_res_t x, y;
    Ray currRay;
    float time, col1, col2;

    x = cam.Nx;
    y = cam.Ny;

    for (currY = 0; currY < y; currY++)
    {
        for (currX = 0; currX < x; currX++)
        {
            currRay = cam.getRayThroughPixel(currX, currY);

            /*if(currX == 350 && currY == 0)
                testRay = currRay;*/

            for(int i=0; i < num_taos; i++)
            {
                for(int k =0; k < taos[i].biPlanes_amt; k++)
                {
                        //Creating the paramters needed for the bilinear patch algorithm
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

                        //If true, comput the times, and clor values based on s and r
                        if(dp.RayPatchIntersection(r,d,srt))
                        {
                            //Time of intersection
                            time = (taos[i].bi_planes[k].time1) +
                                   srt.x()*(taos[i].bi_planes[k].time2 - taos[i].bi_planes[k].time1);

                            //Color at intersection
                            col1 = srt.y();
                            col2 = 1 - srt.y();

                            color1.r = taos[i].bi_planes[k].colors[0].r * col1;
                            color1.g = taos[i].bi_planes[k].colors[0].g * col1;
                            color1.b = taos[i].bi_planes[k].colors[0].b * col1;
                            color1.a = taos[i].bi_planes[k].colors[0].a * col1;

                            color2.r = taos[i].bi_planes[k].colors[1].r * col2;
                            color2.g = taos[i].bi_planes[k].colors[1].g * col2;
                            color2.b = taos[i].bi_planes[k].colors[1].b * col2;
                            color2.a = taos[i].bi_planes[k].colors[1].a * col2;

                            color.r = color1.r + color2.r;
                            color.g = color1.g + color2.g;
                            color.b = color1.b + color2.b;
                            color.a = color1.a + color2.a;

                            //creating a trace fragment
                            fragment.color = color;
                            fragment.time = time;
                            fragment.x = (float)srt.x();
                            fragment.y = (float)srt.y();
                            fragment.t = (float)srt.z();

                            pixelz[currY * x + currX].push_back(fragment);
                        }
                }
            }


        }
    }
    std::cout << "End trace!" << std::endl;
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

// Grabing the objects stored in the parser to create the TAO
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

// Rendering the TAO in 3D
void CSWindow::render()
{
    for(int i = 0; i < num_taos; i++)
    {
        taos[i].drawObjects();
        if(displayPatches)
            taos[i].drawBiPlanes();
    }
}

/***** Motion Effects *****/
float CSWindow::alphaGen(float tn, float tf, float l, float alpha)
{
    float a = (tf-tn)/l;

    a = 1 - a;

    return a/2;
}

// Renders the 2D motion blur animation
void CSWindow::motionBlur(float l, float f_time){
//ensure t is between 0 and 1

    glBegin(GL_POINTS);
    //float min_scalar;
    Trace frag;

    //Iterating over every pixel to determine if it needs to be set
    for(int n = 0; n < cam.Ny; n++)
        for(int m = 0; m < cam.Nx; m++){

        if(!pixelz[n*cam.Nx+m].empty())
        {
            //min_scalar = INF;

            for(unsigned int j = 0; j < pixelz[n*cam.Nx+m].size(); j++)
            {
                /*temp_frag = pixelz[n*cam.Nx+m].at(j);
                if(temp_frag.t < min_scalar)
                {
                    frag = temp_frag;
                    min_scalar = temp_frag.t;
                }
            }*/

            frag = pixelz[n*cam.Nx+m].at(j);

            //If a trace fragment is within the time interval display it
            if((f_time-frag.time < l) &&  (f_time-frag.time > 0))
            {
                glColor4f(frag.color.r,frag.color.g,frag.color.b,
                           alphaGen(frag.time,f_time,l,frag.color.a) );
                glVertex2i(m,n);
                break;
            }
            else
            {
                glColor3f(1,1,1);
                glVertex2i(m,n);
            }
        }
        }
        else
        {
            glColor3f(1,1,1);
            glVertex2i(m,n);
        }
    }
    glEnd();
    glFlush();
}

// Renders the 2D speed lines animation
void CSWindow::speedLines(Vector seed, float w, float l, float f_time){
    Trace frag;
    glBegin(GL_POINTS);
    float r;

    for(int n = 0; n < cam.Ny; n++)
        for(int m = 0; m < cam.Nx; m++)
        {
        if(!pixelz[n*cam.Nx+m].empty())
        {
            for(unsigned int j = 0; j < pixelz[n*cam.Nx+m].size(); j++)
            {
                frag = pixelz[n*cam.Nx+m].at(j);
                r = ((f_time - frag.time)/l)/1.5;

                //Checking that a pixel falls between a certain time interval and height
                //if((f_time-frag.time < l) &&  (f_time-frag.time > 0)
                //  && (frag.y >= (float)seed.y() || frag.y <= 1 - (float)seed.y()))
                if((f_time-frag.time < l) &&  (f_time-frag.time > 0) &&
                   /*((frag.y >= 0.1 && frag.y <= 0.2) || (frag.y >= 0.4 && frag.y <= 0.5)
                    || (frag.y >= 0.7 && frag.y <= 0.8)))*/
                   (frag.y >= (float)seed.y() || frag.y <= (1 - (float)seed.y())))
                   //(frag.y >= 0.8 || frag.y <= 0.2))
                   //(frag.y >= 0.8+r/5 || frag.y <= 0.2-r/5))
                {
                    glColor4f(frag.color.r,frag.color.g,frag.color.b,1);
                    glColor4f(frag.color.r,frag.color.g,frag.color.b,
                              alphaGen(frag.time,f_time,l,frag.color.a));
                    glVertex2i(m,n);
                    break;
                }
                else
                {
                    glColor3f(1,1,1);
                    glVertex2i(m,n);
                }
            }
        }
        else
        {
            glColor3f(1,1,1);
            glVertex2i(m,n);
        }
    }
    glEnd();
    glFlush();
}

// Renders the 2D strobophobic animation
void CSWindow::stroboImage(float spacing, float length, float f_time){

    glPointSize(1.0);
    glBegin(GL_POINTS);
    //glColor3f(1,1,1);

    //Iterating over every pixel
    for(int n = 0; n < cam.Ny; n++)
    {
        for(int m = 0; m < cam.Nx; m++)
        {
            //glColor3f(1,1,1);
            //glVertex2i(m,n);

        //ensure pixel has seen something here
        if(!pixelz[n*cam.Nx+m].empty())
        {
            for(int k =0; k < (int)pixelz[n*cam.Nx+m].size()-1; k++)
            {

                Trace frag = pixelz[n*cam.Nx+m].at(k);
                //ensure it it within the timerane
                if(frag.time <= f_time)
                {
                    //Trace frag2 = pixelz[n*cam.Nx+m].at((int) k+1 % pixelz[n*cam.Nx+m].size());
                    Trace frag2 = pixelz[n*cam.Nx+m].at(k+1);

                    if(frag.time < (f_time*25) - spacing)
                    {
                        //t1mod = (int)frag.time % (int)spacing;
                        //t2mod = (int)frag2.time % (int)spacing;

                        //if(t1mod <= 0 && t2mod < 0)
                        //{
                            //Set alpha a low constant
                            //glColor4f(frag.color.r,frag.color.g,frag.color.b, 1);
                            glColor3f(0,1,0);
                            glVertex2i(m,n);
                        //}
                        /*else{
                            glColor3f(0,0,1);//Blah
                            glVertex2i(m,n);
                        }*/
                    }
                    else{
                        glColor3f(0,0,1);
                        glVertex2i(m,n);
                    }
                }
                else{
                    glColor3f(1,0,1);
                        glVertex2i(m,n);
                    }
            }

        }

        else
        {
            glColor3f(0,0,1);
            glVertex2i(m,n);
        }
    }
    }

    glEnd();
    glFlush();


}

/***** Connected Buttons *****/

void CSWindow::setThreshold(int t)
{
    threshold = (float)t/100.0f;
}

void CSWindow::displayOutput()
{
    output = !output;
    if(!output){
        GLdouble n, f;
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glViewport(0,0,(GLsizei) w, (GLsizei) h);

        n = 1;
        f = 7000;
        glFrustum(-1,1,-1,1, n, f);
    }

    updateGL();
}

void CSWindow::speed()
{
    _speed = true;
    _blur = false;
}

void CSWindow::blur()
{
    _blur = true;
    _speed = false;
}

void CSWindow::setGrid()
{
    displayGrid = !displayGrid;
    updateGL();
}

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

// The main animation loops
void CSWindow::animate()
{
    _animate = true;
    //if(output)
    //{
        GLdouble n, f;
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glViewport(0,0,(GLsizei) w, (GLsizei) h);

        n = 1;
        f = 7000;
        glFrustum(-1,1,-1,1, n, f);

        for(time = 0; time < 20; time+=0.3)
        {
            updateGL();
        }
    //}
    _animate = false;

    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0,0,(GLsizei) w, (GLsizei) h);

    n = 1;
    f = 7000;
    glFrustum(-1,1,-1,1, n, f);

    updateGL();
}

// Opens a file to be passed to the parser
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

// Prints all objects read from the parser
void CSWindow::debug()
{
    if(p != NULL)
        (*p).printObjects();
}
