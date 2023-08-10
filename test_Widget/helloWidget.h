#ifndef OPENGLWIDGET_H  
#define OPENGLWIDGET_H
#include<glm/glm.hpp>
#include <QOpenGLWidget>
#include<QOpenGLFunctions_4_5_Compatibility>
#include <glm/detail/type_vec.hpp>
#include<string>
#include<QOpenGLShaderProgram>
#include<QTimer>
using namespace std;
class helloWidget :public QOpenGLWidget,QOpenGLFunctions_4_5_Compatibility
{
	Q_OBJECT
public:
	enum Shape{Point,Line,Face};
	explicit helloWidget(QWidget* parent = nullptr);
	~helloWidget();
	void drawShape(helloWidget::Shape shape);
	void drawCube();
	void drawModel();

	string filepath = "F://qtApplication//26qt//models//camel.off";
	
signals: 
public slots:
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent (QMouseEvent* event);

	void rotate(int dx, int dy);
	void translate(int dx, int dy);
	void scale(int dx, int dy);
protected:
	
	virtual void initializeGL();
	virtual void resizeGL(int w, int h);
	virtual void paintGL();
	std::vector<float> vertices; //���ļ��ж�ȡ�Ķ�������
	std::vector<int> faces;   //���ļ��ж�ȡ���涥������
	int nVertices = 0;
	int nFaces = 0;
	int nEdges = 0;
	unsigned int VBO, VAO;
	unsigned int EBO;
	QTimer timer;
	QOpenGLShaderProgram shaderProgram;
	Shape m_shape;
	
	float angle = 0.0;

	int MouseButtonIndex = -1;//-1��ʾδ�����κ���갴��,0��ʾ����������,1��ʾ��������Ҽ�,2��ʾ��������м�

	QVector3D m_rotation;
	QVector3D m_translation;
	QVector3D m_scale = {1,1,1};
	QMatrix4x4 m_transform;
	QPoint m_lastPos;

	QMatrix4x4 matrix;
};
#endif
