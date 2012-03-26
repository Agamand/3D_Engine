#ifndef GUI_H
#define GUI_H

#include <QtGui/QWidget>
#include "ui_gui.h"
#include <QtOpengl>
#include <QGLWidget>

class Gui : public QGLWidget
{
	Q_OBJECT

public:
	Gui(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Gui();

sign



private:
	Ui::GuiClass ui;
};

#endif // GUI_H
