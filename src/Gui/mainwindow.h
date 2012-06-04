#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTreeWidget>
#include <QStandardItemModel>
#include <QStandardItem>

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
    QStandardItemModel* getModelObjectTree() {return model_tree_obj;}

public slots:
    void updateTime(int);
    void updateMaxTime(int);

private slots:
    void on_pushButton_3_clicked();

    void on_comboBox_activated(int index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

	void on_select_plein();
	void on_select_fil();
	void on_select_point();

private:
    Ui::MainWindow *ui;
    unsigned int time; // in ms
    unsigned int max_time;
    QTimer* t;
    QStandardItemModel * model_tree_obj;
};

#endif // MAINWINDOW_H
