#ifndef GLWID_H
#define GLWID_H

#include <QWidget>
#include <QGLWidget>
namespace Ui {
class GlWidget;
}

class GlWidget : public QGLWidget
{
    Q_OBJECT
    
public:
    explicit GlWidget(QWidget *parent = 0);
    ~GlWid();
    
private:
    Ui::GlWidget *ui;
};

#endif // GLWID_H
