#include "gui.h"

Gui::Gui(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
}

Gui::~Gui()
{

}
