#ifndef CIRCLE1_H
#define CIRCLE1_H
#define PI 3.14159265358979323846
#include "circle.h"
#include<cmath>

void Circle::draw()
{
	glPushMatrix();
	glTranslatef(centre[0], centre[1], 0.0);
	glutSolidSphere(radius, 20, 20);
	glPopMatrix();
}

void Circle::updatePosition()
{
	if(storeTime<clock()- 10 && ifDragged==0)
	{
		centre[0]= centre[0] + velocity[0]+ 0.5*g[0];
		centre[1]= centre[1] + velocity[1]+ 0.5*g[1];
		velocity[0]= velocity[0] + g[0];
 		velocity[1]= velocity[1] + g[1];
		if(centre[0]+ radius>= WIDTH/2 || centre[0]- radius<= -WIDTH/2)
		{
		   velocity[0]= -E*velocity[0];
		   if(centre[0]+radius> WIDTH/2)
		   {
		      centre[0]= WIDTH/2-radius;
		   }
		   if(centre[0]-radius< -WIDTH/2)
		   {
		      centre[0]= -WIDTH/2+ radius;
           }
		}

		if(centre[1]+ radius>= HEIGHT/2 || centre[1] - radius<= -HEIGHT/2)
		{
		   velocity[1]= -E*velocity[1];

		   if(centre[1]+radius> HEIGHT/2)
		   {
		      centre[1]= HEIGHT/2-radius;
		   }
		   if(centre[1]-radius< -HEIGHT/2)
		   {
		      centre[1]= -HEIGHT/2+ radius;
           }
        }
	
	storeTime= clock();
	glutPostRedisplay();
	}
}


bool Circle::ifCollision(Circle &c)
{
	
	//in frame of passed object
	GLfloat v[2]={velocity[0]- c.velocity[0], velocity[1]- c.velocity[1]};
	GLfloat vLength= sqrt(v[0]*v[0] + v[1]*v[1]);
	GLfloat c1c2= sqrt(pow(centre[0]- c.centre[0], 2) + pow(centre[1]- c.centre[1], 2));

	//test 1 i.e. velocity vector is long enough the collision may take place
	if(vLength< c1c2- (radius+ c.radius))
	{
		return false;
	}

	//test 2

	GLfloat length= (v[0]*(c.centre[0]- centre[0])+ v[1]*(c.centre[1]- centre[1]))/vLength;
	if(length<=0)
	{
		return false;
	}

	if(c1c2*c1c2- length*length> (radius+ c.radius)*(radius+ c.radius))
	{
		return false;
	}

	GLfloat T= (radius+ c.radius)*(radius+ c.radius)- (c1c2*c1c2- length*length);
	GLfloat distance= length- sqrt(T);
	if(distance> vLength)
	{
		return false;
	}

	GLfloat fraction= distance/vLength;
	centre[0]= centre[0]+ velocity[0]*fraction;
	centre[1]= centre[1]+ velocity[1]*fraction;
	c.centre[0]= c.centre[0]+ c.velocity[0]*fraction;
	c.centre[1]= c.centre[1]+ c.velocity[1]*fraction;

	GLfloat vectorAlongLine[2]= {centre[0]- c.centre[0], centre[1]- c.centre[1]};
	GLfloat mag= sqrt(vectorAlongLine[0]*vectorAlongLine[0]+ vectorAlongLine[1]*vectorAlongLine[1]);
	vectorAlongLine[0]= vectorAlongLine[0]/mag;
	vectorAlongLine[1]= vectorAlongLine[1]/mag; //normalized vector along the line of contact is obtained

	GLfloat a1= velocity[0]*vectorAlongLine[0]+ velocity[1]*vectorAlongLine[1];
	GLfloat a2= c.velocity[0]*vectorAlongLine[0]+ c.velocity[1]*vectorAlongLine[1];

	GLfloat optimizedP= 2*(a1-a2)/(mass+ c.mass);
	
	velocity[0]= velocity[0]- optimizedP*c.mass*vectorAlongLine[0];
	velocity[1]= velocity[1]- optimizedP*c.mass*vectorAlongLine[1];

	c.velocity[0]= c.velocity[0]+ optimizedP*mass*vectorAlongLine[0];
	c.velocity[1]= c.velocity[1]+ optimizedP*mass*vectorAlongLine[1];

	glutPostRedisplay(); //veryImportant to print the newly positioned spheres
	return true;
}

void Circle::mouseDragFunc(int state, int x, int y)
{
	if(state==GLUT_DOWN && ifDragged==0 && (radius*10*radius*10 >= pow(centre[0]*10-x, 2)+ pow(centre[1]*10- y, 2)))
	{
		ifDragged=1;
		draggedTime=clock();
		cursorPos[0]=x;
		cursorPos[1]=y;
	}

	else if(state==GLUT_UP && ifDragged==1)
	{
		ifDragged=0;
		draggedTime=clock()-draggedTime; //to store the time gap
		velocity[0]= (GLfloat)(x- cursorPos[0])/(draggedTime);//multiplied by 10 as 10ms is refresh time and divided by 10 to make sure that velocity is right no acoording to pixels!!
		velocity[1]= (GLfloat)(y- cursorPos[1])/(draggedTime);//conversion to GLfloat so that the result is accurate enough. without conversion precision is lost
		glutPostRedisplay();
	}
}


#endif
