/********************************************************************************
** Form generated from reading UI file 'test_Widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_WIDGET_H
#define UI_TEST_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "hellowidget.h"

QT_BEGIN_NAMESPACE

class Ui_test_WidgetClass
{
public:
    QWidget *centralWidget;
    helloWidget *openGLWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *test_WidgetClass)
    {
        if (test_WidgetClass->objectName().isEmpty())
            test_WidgetClass->setObjectName(QString::fromUtf8("test_WidgetClass"));
        test_WidgetClass->resize(600, 400);
        centralWidget = new QWidget(test_WidgetClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        openGLWidget = new helloWidget(centralWidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(80, 50, 300, 200));
        test_WidgetClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(test_WidgetClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 22));
        test_WidgetClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(test_WidgetClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        test_WidgetClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(test_WidgetClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        test_WidgetClass->setStatusBar(statusBar);

        mainToolBar->addSeparator();

        retranslateUi(test_WidgetClass);

        QMetaObject::connectSlotsByName(test_WidgetClass);
    } // setupUi

    void retranslateUi(QMainWindow *test_WidgetClass)
    {
        test_WidgetClass->setWindowTitle(QCoreApplication::translate("test_WidgetClass", "test_Widget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class test_WidgetClass: public Ui_test_WidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_WIDGET_H
