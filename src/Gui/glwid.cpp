#include "glwidget.h"
#include "ui_glwidget.h"

GlWidget::GlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GlWidget)
{
    ui->setupUi(this);
}

GlWidget::~GlWidget()
{
    delete ui;
}
