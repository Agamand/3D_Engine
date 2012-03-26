/********************************************************************************
** Form generated from reading UI file 'gui.ui'
**
** Created: Mon 26. Mar 02:51:15 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>
#include <phonon/seekslider.h>

QT_BEGIN_NAMESPACE

class Ui_GuiClass
{
public:
    QWidget *maingl;
    Phonon::SeekSlider *seekSlider;

    void setupUi(QWidget *GuiClass)
    {
        if (GuiClass->objectName().isEmpty())
            GuiClass->setObjectName(QString::fromUtf8("GuiClass"));
        GuiClass->resize(871, 571);
        maingl = new QWidget(GuiClass);
        maingl->setObjectName(QString::fromUtf8("maingl"));
        maingl->setGeometry(QRect(0, 0, 661, 501));
        seekSlider = new Phonon::SeekSlider(GuiClass);
        seekSlider->setObjectName(QString::fromUtf8("seekSlider"));
        seekSlider->setGeometry(QRect(0, 520, 661, 20));

        retranslateUi(GuiClass);

        QMetaObject::connectSlotsByName(GuiClass);
    } // setupUi

    void retranslateUi(QWidget *GuiClass)
    {
        GuiClass->setWindowTitle(QApplication::translate("GuiClass", "Gui", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GuiClass: public Ui_GuiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
