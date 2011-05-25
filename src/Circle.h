#ifndef CIRCLE_H
#define CIRCLE_H
#include<ctime>
#include<iostream>
using namespace std;
#include<GL/glut.h>
const int WIDTH=40;
const int HEIGHT=70;
const float E= 0.9;

class Circle
{
public:
	GLfloat centre[2];
	GLfloat radius;
	GLfloat velocity[2];
	GLfloat g[2];
	GLfloat mass;
	GLint storeTime;
	GLint draggedTime;
	bool ifDragged;
	GLint cursorPos[2];

	Circle(GLfloat r, GLfloat x, GLfloat y, GLfloat velX, GLfloat velY, GLfloat accX, GLfloat accY, GLfloat m)
	{
		radius=r;
		centre[0]= x;
		centre[1]= y;
		velocity[0]= velX;
		velocity[1]= velY;
		g[0]= accX;
		g[1]= accY;
		mass= m;
		storeTime= clock();
		ifDragged=0;

	}
	void draw();
	~Circle()
	{}
	void updatePosition();
	bool ifCollision(Circle&);
	void mouseDragFunc(int, int, int);
};

#endif
