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
}

void GlWidget::initializeGL()
{
#ifndef DEBUG_QT
    // Init Object manager
    new ObjectAccessor(new Scene(OPTION_ENABLE_TEXTURE));
    // Init Camera
    cam = new Camera(Vector3D(0.0f,0.0f,0.0f));

	Robot* rob = new Robot();

	ObjectAccessor::getObjMgr()->getScene()->add(rob->getBase());
	selected_obj = NULL;

#endif
    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    perspectiveGL(45,this->width()/this->height(),0.1,1000);
    glClearColor(0, 0, 0, 0.0);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_LIGHT1);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
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
        selection(m->x(),m->y());
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
    mode = index;
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
