#include "test_Widget.h"
#include"helloWidget.h"
#include <QtWidgets/QApplication>
#include<GL/freeglut.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    test_Widget w;
    w.show();
    return a.exec();
}
