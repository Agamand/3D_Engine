#ifndef GLWIDGET_H
#define GLWIDGET_H

//#define DEBUG_QT

#ifndef DEBUG_QT
#include "../Camera/Camera.h"
#include "../Math/Vector.h"
#include "../Shader/Shader.h"
#include "../Scene/Animation.h"
#include "../Physics/Physics.h"
#include "../ObjectAccessor/ObjectAccessor.h"
#include "../Robot.h"
#include "../Math/Geom.h"
#endif

#include <QGLWidget>
#include <QTimer>
#include <QTime>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPoint>
#define _USE_MATH_DEFINES
#include <math.h>
#define SECONDES 1000
#define FPS 120.0f
#define TIMER  1 //SECONDES/FPS



enum mode
{
    MODE_NOTHING,
    MODE_ROTATE_X,
    MODE_ROTATE_Y,
    MODE_ROTATE_Z,
    MODE_DRAW
};

enum Draw
{
    DRAW_BOX,
    DRAW_SPHERE,
    DRAW_DISK,
    DRAW_TORUS,
    DRAW_SPEC
};

enum Phase_Drawing
{
    NO_DRAWING,
    DRAWING_PHASE_1,
    DRAWING_PHASE_2,
    DRAWING_PHASE_3
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
    void setDraw(int mode);
    void setGLmode(int mode)
    {
        glPolygonMode(GL_FRONT_AND_BACK,mode);
    }
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
    void drawObject(int x, int y, bool update = false);
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
    Object* created_obj;
	Texture* text;
    Shader* sh;
#endif
    QPoint last_pos;
    int mode;
    int mode_draw;
    int phase_drawing;
    
};

#endif // GLWIDGET_H
