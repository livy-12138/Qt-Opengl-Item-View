#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_test_Widget.h"
#include<QOpenGLFunctions_4_5_Compatibility>
#include<QString>
class test_Widget : public QMainWindow
{
    Q_OBJECT

public:
    test_Widget(QWidget *parent = nullptr);
    ~test_Widget();
private:
    Ui::test_WidgetClass ui;
    QString filePath;

};



