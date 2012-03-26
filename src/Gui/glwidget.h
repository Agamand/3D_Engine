#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <QTime>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPoint>
#define _USE_MATH_DEFINES
#include <math.h>
#define SECONDES 1000
#define FPS 60
#define TIMER SECONDES/FPS

//#define DEBUG_QT

#ifndef DEBUG_QT
#include "../Camera/Camera.h"
#include "../Math/Vector.h"
#include "../Shader/Shader.h"
#include "../Scene/Animation.h"
#include "../Physics/Physics.h"
#include "../ObjectAccessor/ObjectAccessor.h"
#include "../Robot.h"
#endif
enum mode
{
    MODE_NOTHING,
    MODE_ROTATE_X,
    MODE_ROTATE_Y,
    MODE_ROTATE_Z
};

class GlWidget : public QGLWidget
{
    Q_OBJECT
public:
    GlWidget(QWidget *parent=0 );
    void keyPressEvent( QKeyEvent *keyEvent );
    void mousePressEvent(QMouseEvent *);
 //   void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void setTime(int value);
    void start();
    void stop();
    void pause();
    void switchMode(int index);
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void grid();
signals:
    
public slots:
    void timeOutSlot();

private:
    void selection(int x, int y);
#ifndef DEBUG_QT
    void setSelection(Object*);
#endif
    void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
    {
        double fH = tan( fovY / 360 * M_PI ) * zNear;
        double fW = fH * aspect;
        glFrustum(-fW, fW, -fH, fH, zNear, zFar);
    }
    QTimer* timer;
    QTime last_time;
#ifndef DEBUG_QT
    Camera * cam;
	Object* selected_obj;
#endif
    QPoint last_pos;
    int mode;
    
};

#endif // GLWIDGET_H
