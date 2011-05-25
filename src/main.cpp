#include "Circle.h"
using namespace std;
enum Status{CONTINUE, PAUSED, DRAGGED};
Status gameStatus=CONTINUE;
int storeTime= clock();
GLfloat xDrag;
GLfloat yDrag;
GLint dragTime;

Circle c1(4.0, 0.0, -10.0, -1.0, 0.1, 0.0, -0.01, 1.0);
Circle c2(4.0, 0.0, 0.0, 0.1, 0.1, 0.0, -0.01, 1.0);
Circle c3(4.0, 0.0, 15.0, 0.1, 0.1, 0.0, -0.01, 1.0);
Circle c4(4.0, 9.0, 10.0, 0.0, 0.0, 0.0, -0.01, 1.0);
Circle c5(4.0, -9.0, 10.0, 0.0, 0.0, 0.0, -0.01, 1.0);

GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };
void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	GLfloat light_model_ambient[]= {0.4, 0.4, 0.4, 1.0};
	GLfloat light_position[]= {5.0, 5.0, 5.0, 0.0};
	GLfloat light_material_specular[]= {1.0, 1.0, 1.0, 1.0};

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, light_material_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_model_ambient);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glColor3f(1.0, 0.0, 0.0);
	c1.draw();

	glColor3f(1.0, 0.0, 1.0);
	c2.draw();

	glColor3f(0.0, 0.0, 1.0);
	c3.draw();

	glColor3f(0.0, 1.0, 0.0);
	c4.draw();

	glColor3f(1.0, 1.0, 0.0);
	c5.draw();

	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2, -20, 20);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'p':
		if(gameStatus==CONTINUE)
		{
			gameStatus=PAUSED;
		}

		else
		{
			gameStatus=CONTINUE;
		}
		glutPostRedisplay();
		break;
	default:
		break;
	}
}



void update()
{
	if(gameStatus==CONTINUE)
	{
		c1.ifCollision(c2);
		c1.ifCollision(c3);
		c1.ifCollision(c4);
		c1.ifCollision(c5);
		c2.ifCollision(c3);
		c2.ifCollision(c4);
		c2.ifCollision(c5);
		c3.ifCollision(c4);
		c3.ifCollision(c5);
		c4.ifCollision(c5);

		c1.updatePosition();
		c2.updatePosition();
		c3.updatePosition();
		c4.updatePosition();
		c5.updatePosition();
		
		
	}

}

void mouse(int button, int state, int x, int y)
{
	
	if(button==GLUT_LEFT_BUTTON)
	{
		x=x-WIDTH*10/2;
		y=HEIGHT*10/2-y;

		c1.mouseDragFunc(state, x, y);
		c2.mouseDragFunc(state, x, y);
		c3.mouseDragFunc(state, x, y);
		c4.mouseDragFunc(state, x, y);
		c5.mouseDragFunc(state, x, y);
		if(c1.ifDragged || c2.ifDragged || c3.ifDragged || c4.ifDragged || c5.ifDragged)
		{
			gameStatus=DRAGGED;
			glutPostRedisplay();
		}

		else
		{
			gameStatus=CONTINUE;
			glutPostRedisplay();
		}

	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIDTH*10, HEIGHT*10);
	glutCreateWindow(">>crg<<");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutIdleFunc(update);
	glutMainLoop();
	return 0;
}