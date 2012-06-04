#include "glwidget.h"
#include "mainwindow.h"

GlWidget::GlWidget(QWidget *parent) :
    QGLWidget(parent)
{

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this, SLOT(timeOutSlot()));
    timer->start(TIMER);
    last_time = QTime::currentTime();
    last_pos = QPoint(0,0);
    setMouseTracking(true);
    mode = MODE_NOTHING;
    mode_draw = DRAW_BOX;
    phase_drawing = NO_DRAWING;
    //format().setDoubleBuffer(true);
}

void GlWidget::initializeGL()
{
#ifndef DEBUG_QT
	//Init Shader
	initShader();
    // Init Object manage
	new ObjectAccessor(new Scene(OPTION_ENABLE_TEXTURE | OPTION_ENABLE_LIGHT));
    // Init Camera
    cam = new Camera(Vector3D(0.0f,0.0f,0.0f));

	Light* l = new Light(Vector3D(3.0f,0.0f,2.0f));
    l->setSpot(90);
	ObjectAccessor::getObjMgr()->getScene()->add(l);

	Robot* rob = new Robot();

    ObjectAccessor::getObjMgr()->getScene()->add(rob->getBase());
	selected_obj = NULL;
    created_obj = NULL;
	text = ObjectAccessor::getObjMgr()->getTexture("../../src/img/moon2.bmp");
    sh =  new Shader("../../src/Shader/shading.vert","../../src/Shader/shading.frag");//Shader("../../src/Shader/light2.vert","../../src/Shader/light2.frag");
#endif
    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    if(this->height())
        perspectiveGL(45,this->width()/this->height(),0.1,1000);
    glClearColor(0, 0, 0, 0.0);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_LIGHT1);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
}

void GlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode (GL_TEXTURE);
    glLoadIdentity ();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
#ifndef DEBUG_QT
    if(cam)
        cam->look();



    ObjectAccessor::getObjMgr()->getScene()->show();

#endif
    grid();
    glFlush();
	//swapBuffers();
    //glutSwapBuffers();
}

void GlWidget::resizeGL(int w, int h)
{
    glViewport (0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    perspectiveGL(45, (GLfloat)w/(GLfloat)h, 0.1, 1000.0);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();

}

void GlWidget::grid()
{
    glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
    int i, j;

    for(i = 0; i < 9; i++)
    {
        glBegin(GL_LINES);
        glColor3ub(255,255,255);
        glVertex3f(-4.0f+i,-4.0f,0.0f);
        glVertex3f(-4.0f+i,4.0f,0.0f);
        glEnd();

        glBegin(GL_LINES);
        glColor3ub(255,255,255);
        glVertex3f(-4.0f,-4.0f+i,0.0f);
        glVertex3f(4.0f,-4.0f+i,0.0f);
        glEnd();
    }
}

void GlWidget::keyPressEvent(QKeyEvent *keyEvent)
{
#ifndef DEBUG_QT
    switch(keyEvent->key())
    {
        case Qt::Key_A:
        cam->OnKeyboard('a');
        break;
        case Qt::Key_E:
        cam->OnKeyboard('e');
        break;
        case Qt::Key_Z:
        cam->OnKeyboard('z');
        break;
        case Qt::Key_D:
        cam->OnKeyboard('d');
        break;
        case Qt::Key_Q:
        cam->OnKeyboard('q');
        break;
        case Qt::Key_S:
        cam->OnKeyboard('s');
        break;
    }
#endif
    //   updateGL();
}

void GlWidget::mousePressEvent(QMouseEvent * m)
{
    if(m->buttons() == Qt::LeftButton)
    {
        if(phase_drawing == NO_DRAWING)
            selection(m->x(),m->y());
        drawObject(m->pos().x(),m->pos().y(),true);
    }
}
/*
void GlWidget::mouseReleaseEvent(QMouseEvent *m)
{
    mousestate = m->buttons();
}*/

void GlWidget::mouseMoveEvent(QMouseEvent *m)
{
    float angleAdd = 1.0f;
    QPoint diff = m->pos() - last_pos;
#ifndef DEBUG_QT
    if(m->buttons() == Qt::RightButton)
        cam->OnMouseMotion(diff.x(),diff.y());

    if(m->buttons() == Qt::LeftButton)
    {
        if(selected_obj != NULL)
        {
            angleAdd *= diff.x()/180.0f*M_PI;
            selected_obj->rotate(angleAdd,Vector3D(mode == MODE_ROTATE_X ? 1.0f : 0.0f, mode == MODE_ROTATE_Y ? 1.0f : 0.0f, mode == MODE_ROTATE_Z ? 1.0f : 0.0f));
        }
    }

    if(m->buttons() == Qt::NoButton)
    {
        drawObject(m->pos().x(),m->pos().y());
    }
#endif
    last_pos = m->pos();
}

void GlWidget::setTime(int value)
{
#ifndef DEBUG_QT
    ObjectAccessor::getObjMgr()->getScene()->setTime(value);
#endif
}

void GlWidget::start()
{
#ifndef DEBUG_QT
	ObjectAccessor::getObjMgr()->getScene()->start();
#endif
}

void GlWidget::stop()
{
#ifndef DEBUG_QT
	ObjectAccessor::getObjMgr()->getScene()->reset();
#endif
}

void GlWidget::pause()
{
#ifndef DEBUG_QT
	ObjectAccessor::getObjMgr()->getScene()->pause(); 
#endif
}

void GlWidget::switchMode(int index)
{
#ifndef DEBUG_QT
    if(mode == MODE_DRAW)
    {
        if(created_obj != NULL)
        {
            ObjectAccessor::getObjMgr()->getScene()->del(created_obj);
            delete created_obj;
            created_obj = NULL;
        }
        phase_drawing = NO_DRAWING;
    }
#endif
    mode = index;
}

void GlWidget::setDraw(int mode)
{
    mode_draw = mode;
    phase_drawing = NO_DRAWING;
#ifndef DEBUG_QT
    if(created_obj)
    {
        ObjectAccessor::getObjMgr()->getScene()->del(created_obj);
        delete created_obj;
        created_obj = NULL;
    }
#endif
}

void GlWidget::timeOutSlot()
{
    QTime t = QTime::currentTime();
    int diff = last_time.msecsTo(t);

    updateGL();
#ifndef DEBUG_QT
    Scene* sc = ObjectAccessor::getObjMgr()->getScene();
	sc->update(diff);
	if(sc->started())
    {
        MainWindow* win = ((MainWindow*)(parentWidget()->parent()));
        win->updateTime(sc->getTime());
    }

#endif
    last_time = t;

}

void GlWidget::selection(int x, int y)
{
#ifndef DEBUG_QT
    GLuint	buffer[512];
    GLint	hits;
    GLint	viewport[4];

    glGetIntegerv(GL_VIEWPORT, viewport);
    glSelectBuffer(512, buffer);
    glRenderMode(GL_SELECT);

    glInitNames();
    glPushName(0);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    gluPickMatrix((GLdouble) x, (GLdouble) (viewport[3]-y), 1.0f, 1.0f, viewport);
    gluPerspective(45.0f, (GLfloat) (viewport[2]-viewport[0])/(GLfloat) (viewport[3]-viewport[1]), 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    ObjectAccessor::getObjMgr()->getScene()->show();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    hits=glRenderMode(GL_RENDER);

    if (hits > 0)
    {
        int	choose = buffer[buffer[0]+1];
        int depth = buffer[1];
        int lastindex = buffer[0]+2+1;
        for (int i = 1; i < hits; i++)
        {
            int size = buffer[lastindex]+1;
            if (buffer[lastindex+1] < GLuint(depth))
            {
                choose = buffer[lastindex+size];
                depth = buffer[lastindex+1];
            }
            lastindex += (size+2);
        }
        setSelection(ObjectAccessor::getObjMgr()->getObject(choose));
    }else setSelection(NULL);

#endif
}

void GlWidget::drawObject(int x, int y, bool update)
{
#ifndef DEBUG_QT
    if(phase_drawing == NO_DRAWING && !update || mode != MODE_DRAW)
        return;

    RayTest ray;
    Vector3D v;
    switch(mode_draw)
    {
    case DRAW_BOX:
        if(phase_drawing == NO_DRAWING)
        {

            if(!ray.test(v,x,y,cam->getPosition()))
                return;

            Box* b = new Box(v,Vector3D());
            created_obj = b;
            b->useShader(sh);
            ObjectAccessor::getObjMgr()->getScene()->add(b);
            phase_drawing = DRAWING_PHASE_1;
        }else if(phase_drawing == DRAWING_PHASE_1)
        {
            if(!ray.test(v,x,y,cam->getPosition()))
                return;

            Box* b = static_cast<Box*>(created_obj);
            float x,y,z;
            b->getLength(x,y,z);
            Vector3D p1 = v-b->getPosition();
            b->setLength(p1.getX(),p1.getY(),z);

            if(update)
                phase_drawing = DRAWING_PHASE_2;
        }else
        {
            Vector3D normal = cam->getTarget();
            normal.setZ(0.0f);
            Box* b = static_cast<Box*>(created_obj);
            Plan pl(Vector3D()-b->getPosition(),normal);
            ray = RayTest(pl);
            if(!ray.test(v,x,y,cam->getPosition()))
                return;

            float x,y,z;

            b->getLength(x,y,z);
            Vector3D p1 = v-b->getPosition();
            b->setLength(x,y,p1.getZ());

            if(update)
            {
                phase_drawing = NO_DRAWING;
                created_obj = NULL;
            }
        }
        break;
    case DRAW_SPHERE:
        if(phase_drawing == NO_DRAWING)
        {

            if(!ray.test(v,x,y,cam->getPosition()))
                return;

            Sphere* b = new Sphere(v);
            b->setSize(0.0f);
            created_obj = b;
			b->setTexture(text);
            b->useShader(sh);
            ObjectAccessor::getObjMgr()->getScene()->add(b);
            phase_drawing = DRAWING_PHASE_1;
        }else
        {
            Sphere* b = static_cast<Sphere*>(created_obj);
            if(!ray.test(v,x,y,cam->getPosition()))
                return;

            double x,y,z;
            Vector3D p1 = v-b->getPosition();
            b->setSize(p1.getLength());

            if(update)
            {
                phase_drawing = NO_DRAWING;
                created_obj = NULL;
            }
        }
        break;
        break;
    case DRAW_DISK:
        break;
    case DRAW_TORUS:
        break;
    case DRAW_SPEC:
        break;
    }

#endif
}
#ifndef DEBUG_QT
void GlWidget::setSelection(Object *obj)
{

    if(selected_obj)
        selected_obj->showRepere(false);


    selected_obj = obj;

    if(selected_obj)
        selected_obj->showRepere(true);
}
#endif
