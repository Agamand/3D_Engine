#include "mainwindow.h"
#include "glwidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    time = 0;
    max_time = 10000;
    connect(ui->Time,SIGNAL(valueChanged(int)),this,SLOT(updateTime(int)));
    connect(ui->actualTime,SIGNAL(valueChanged(int)),this,SLOT(updateTime(int)));
    connect(ui->maxTime,SIGNAL(valueChanged(int)),this,SLOT(updateMaxTime(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *keyEvent)
{
    this->ui->gl->keyPressEvent(keyEvent);
}

void MainWindow::updateTime(int value)
{
    if(value > (int)max_time)
        value = max_time;
    else if (value < 0)
        value = 0;

    time = value;
	ui->gl->setTime(time);
    ui->Time->setValue(time);
    ui->actualTime->setValue(time);
}

void MainWindow::updateMaxTime(int value)
{
    if (value < 0)
        value = 1;

	ui->Time->setMaximum(value);
	ui->actualTime->setMaximum(value);

    if(value < max_time)
    {
        max_time = value;
        updateTime(time);
    }

    max_time = value;

	//ui->maxTime->setMaximum(max_time);
	ui->maxTime->setValue(max_time);
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->gl->start();

}

void MainWindow::on_comboBox_activated(int index)
{
    ui->gl->switchMode(index);
}

void MainWindow::on_pushButton_clicked()
{
    ui->gl->stop();
    updateTime(0);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->gl->pause();
}
