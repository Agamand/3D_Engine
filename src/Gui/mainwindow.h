#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent( QKeyEvent *keyEvent );

public slots:
    void updateTime(int);
    void updateMaxTime(int);

private slots:
    void on_pushButton_3_clicked();

    void on_comboBox_activated(int index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    unsigned int time; // in ms
    unsigned int max_time;
    QTimer* t;
};

#endif // MAINWINDOW_H
