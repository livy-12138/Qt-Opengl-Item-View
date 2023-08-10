#include "test_Widget.h"
#include"helloWidget.h"
#include<QString>
#include<QFileInfo>
#include<QPainter>
#include<QKeyEvent>
#include<QMouseEvent>
#include<QDebug>
#include<QFileDialog>
#include<QMenu>
#include<QAction>

test_Widget::test_Widget(QWidget *parent)
    : QMainWindow(parent)
{
    setMouseTracking(TRUE);
    ui.setupUi(this);
    setCentralWidget(ui.openGLWidget);
    resize(800, 800);
    setWindowTitle("OpenGL");
    QMenuBar* bar = menuBar();
    //将菜单栏放入到窗口中
    setMenuBar(bar);
    //创建菜单
    QMenu* fileMenu = bar->addMenu("File");
    QMenu* viewMenu = bar->addMenu("View");
    QMenu* helpMenu = bar->addMenu("Help");
    //创建菜单项
    QAction* openAction = fileMenu->addAction("open");
    QAction* pointAction = viewMenu->addAction("point");
    viewMenu->addSeparator();
    QAction* lineAction = viewMenu->addAction("line");
    viewMenu->addSeparator();
    QAction* faceAction = viewMenu->addAction("face");
    viewMenu->addSeparator();
    //添加分隔线
    //工具栏可以有多个
    QToolBar* toolBar = new QToolBar(this);
    addToolBar(toolBar);//默认在上面
    toolBar->addAction(openAction);
    toolBar->addSeparator();
    toolBar->addAction(pointAction);
    toolBar->addSeparator();
    toolBar->addAction(lineAction);
    toolBar->addSeparator();
    toolBar->addAction(faceAction);
    toolBar->addSeparator();
    openAction->setIcon(QIcon("F:\\qtApplication\\25qt\\file.png"));
    pointAction->setIcon(QIcon("F:\\qtApplication\\25qt\\circle1.jpg"));
    lineAction->setIcon(QIcon("F:\\qtApplication\\25qt\\circle2.jpg"));
    faceAction->setIcon(QIcon("F:\\qtApplication\\25qt\\circle3.jpg"));
    connect(openAction, &QAction::triggered, [=]() {
        filePath = QFileDialog::getOpenFileName(this, "open","F:\\qtApplication\\25qt\\models");
        ui.openGLWidget->filepath = filePath.toStdString();
    });
    connect(pointAction, &QAction::triggered, [=]() {
        ui.openGLWidget->drawShape(helloWidget::Point);
    });
    connect(lineAction, &QAction::triggered, [=]() {
        ui.openGLWidget->drawShape(helloWidget::Line);
    });
    connect(faceAction, &QAction::triggered, [=]() {
        ui.openGLWidget->drawShape(helloWidget::Face);
    });

}

test_Widget::~test_Widget()
{
    
}
