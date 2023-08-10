#include "helloWidget.h"
#include<iostream>
#include<string>
#include<fstream>
#include<QDebug>
#include<QOpenGLShaderProgram>
#include<QTime>
#include <GL/glut.h>
#include<QMainWindow>
#include<QMouseEvent>

#define pi 3.14
using namespace std;
helloWidget::helloWidget(QWidget* parent) :QOpenGLWidget(parent)
{
}

void helloWidget::initializeGL()
{
	initializeOpenGLFunctions();
	std::ifstream fin;
	std::string a;
	fin.open(filepath);
	if (!fin)
	{
		qDebug() << ("�ļ�����\n");
		return;
	}
	fin >> a; //���������ַ���"OFF"
	fin >> nVertices >> nFaces >> nEdges; //����㡢�桢����Ŀ
	// @TODO���޸Ĵ˺�����ȡOFF�ļ�����άģ�͵���Ϣ
	// ��ȡÿ�����������
	vector<float> vertices;
	vector<int>faces;
	float num1, num2, num3;
	for (int i = 0; i < nVertices; i++) {
		fin >> num1 >> num2 >> num3;
		vertices.push_back(num1);
		vertices.push_back(num2);
		vertices.push_back(num3);
	}
	int n1, n2, n3;
	for (int i = 0; i < nFaces; i++) {
		int num;
		fin >> num;
		fin >> n1 >> n2 >> n3;
		faces.push_back(n1);
		faces.push_back(n2);
		faces.push_back(n3);
	}
	fin.close();

	// ���������������
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// ��������ʼ�����㻺�����
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), NULL, GL_STATIC_DRAW);//
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//��0������ȡ3��ֵ����������Ǳ�׼�����ֵ���Ͳ����ٱ�׼����
	//����VAO����ĵ�һ������ֵ
	glEnableVertexAttribArray(0);
	// @TODO���޸���ɺ��ٴ�����ע�ͣ��������ᱨ��
	// �ֱ��ȡ����
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), &vertices[0]);
	//������ɫ��
	//������ɫ��
	shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "://test_Widget//vertice.vert");
	shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "://test_Widget//fragment.frag");
	//������ɫ��
	bool success = shaderProgram.link();
	if (!success) {
		qDebug() << "the bind is fail";
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//���������
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(float), &faces[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);//���
	glBindVertexArray(0);//����ڹ�����ɺ���
	
}
void helloWidget::mousePressEvent(QMouseEvent* event)
{
	m_lastPos = event->pos();
}

void helloWidget::mouseMoveEvent(QMouseEvent* event)
{
	int dx = event->x() - m_lastPos.x();
	int dy = event->y() - m_lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		rotate(dx, dy);
	}
	else if (event->buttons() & Qt::RightButton) {
		translate(dx, dy);
	}
	else if (event->buttons() & Qt::MidButton) {
		scale(dx, dy);
	}
	m_lastPos = event->pos();
	update();
}

void helloWidget::rotate(int dx, int dy)
{
	m_rotation.setX(m_rotation.x() + dy);
	m_rotation.setY(m_rotation.y() + dx);

	QQuaternion xRot = QQuaternion::fromAxisAndAngle(1, 0, 0, m_rotation.x());//x��y��z�������ת�Ƕ�
	QQuaternion yRot = QQuaternion::fromAxisAndAngle(0, 1, 0, m_rotation.y());
	m_transform.setToIdentity();
	m_transform.scale(m_scale);
	m_transform.translate(m_translation);
	m_transform.rotate(xRot * yRot);
}

void helloWidget::translate(int dx ,int dy)
{
	m_translation.setX(m_translation.x() + dx * 0.01);
	m_translation.setY(m_translation.y() - dy * 0.01);
	//���任��������Ϊ��λ����
	m_transform.setToIdentity();
	m_transform.scale(m_scale);
	//��������ƽ�Ƶ���ȷ��λ��
	m_transform.translate(m_translation);
	//����ת�任����Ӧ�õ�m_transform��
	m_transform.rotate(QQuaternion::fromAxisAndAngle(1, 0, 0, m_rotation.x()));
	m_transform.rotate(QQuaternion::fromAxisAndAngle(0, 1, 0, m_rotation.y()));
}

void helloWidget::scale(int dx, int dy)
{
	m_scale.setX(m_scale.x() + dy * 0.01);
	m_scale.setY(m_scale.y() + dy * 0.01);

	m_transform.setToIdentity();
	m_transform.scale(m_scale);
	//��������ƽ�Ƶ���ȷ��λ��
	m_transform.translate(m_translation);
	//����ת�任����Ӧ�õ�m_transform��
	m_transform.rotate(QQuaternion::fromAxisAndAngle(1, 0, 0, m_rotation.x()));
	m_transform.rotate(QQuaternion::fromAxisAndAngle(0, 1, 0, m_rotation.y()));
}

void helloWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
}
void helloWidget::drawCube()
{
	glBegin(GL_POINTS);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glEnd();
}
void helloWidget::drawModel()
{
	switch (m_shape) {
	case Point:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//���������
		glPointSize(2.0f);
		shaderProgram.setUniformValue("theMatrix", matrix);
		glDrawArrays(GL_POINTS, 0, nVertices);
		break;
	case Line:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//���������
		shaderProgram.setUniformValue("theMatrix", matrix);
		glDrawElements(GL_TRIANGLES, nFaces * 3, GL_UNSIGNED_INT, 0);
		break;
	case Face:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//����
		shaderProgram.setUniformValue("theMatrix", matrix);
		glDrawElements(GL_TRIANGLES, nFaces * 3, GL_UNSIGNED_INT, 0);
		break;
	}
}
void helloWidget::paintGL()
{
	qDebug() << glGetString(GL_VERSION) << endl;
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 1.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(12.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	initializeGL();
	shaderProgram.bind();
	glBindVertexArray(VAO);

	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	matrix.perspective(45.0f,1, 1, 3);
	glPushMatrix();
	glMultMatrixf(m_transform.constData());
	if(1){
		drawCube();
	}
	else {
		matrix.setToIdentity();
		matrix *= m_transform;
		drawModel();
	}
	
	
	glPopMatrix();

	shaderProgram.removeAllShaders();
	}
	

void helloWidget::drawShape(helloWidget::Shape shape)
{
	m_shape = shape;
	update();
}

helloWidget::~helloWidget()
{
//	makeCurrent();
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
	//glDeleteProgram(shaderProgram);
	doneCurrent(); 
}