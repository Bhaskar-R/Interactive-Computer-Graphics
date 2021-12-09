#include <GL/glew.h>
#include <GL/freeglut.h>
#include <bits/stdc++.h>

void myInit()
{
	glClearColor(0.9, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 400.0, 0.0, 400.0); // Specify the display area
}

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT); // Clear the screen buffer

	glPointSize(4.0);

	srand((unsigned int)time(NULL));
	int color1 = rand() % 255;
	int color2 = rand() % 255;
	int color3 = rand() % 255;

	//Number 0
	glColor3ub(color1, color2, color3);

	glBegin(GL_POLYGON);
	glVertex2i(100, 90);
	glVertex2i(120, 90);
	glVertex2i(120, 310);
	glVertex2i(100, 310);
	glEnd();

	glColor3ub(color1, color2, color3);

	glBegin(GL_POLYGON);
	glVertex2i(170, 90);
	glVertex2i(190, 90);
	glVertex2i(190, 310);
	glVertex2i(170, 310);
	glEnd();

	glColor3ub(color1, color2, color3);

	glBegin(GL_POLYGON);
	glVertex2i(100, 310);
	glVertex2i(190, 310);
	glVertex2i(190, 335);
	glVertex2i(100, 335);
	glEnd();

	glColor3ub(color1, color2, color3);

	glBegin(GL_POLYGON);
	glVertex2i(100, 65);
	glVertex2i(190, 65);
	glVertex2i(190, 90);
	glVertex2i(100, 90);
	glEnd();

	//Number 9
	glColor3ub(color1, color2, color3);

	glBegin(GL_POLYGON);
	glVertex2i(300, 90);
	glVertex2i(320, 90);
	glVertex2i(320, 310);
	glVertex2i(300, 310);
	glEnd();

	glColor3ub(color1, color2, color3);

	glBegin(GL_POLYGON);
	glVertex2i(230, 310);
	glVertex2i(320, 310);
	glVertex2i(320, 335);
	glVertex2i(230, 335);
	glEnd();
	glColor3ub(color1, color2, color3);

	glBegin(GL_POLYGON);
	glVertex2i(230, 65);
	glVertex2i(320, 65);
	glVertex2i(320, 90);
	glVertex2i(230, 90);
	glEnd();
	glColor3ub(color1, color2, color3);

	glBegin(GL_POLYGON);
	glVertex2i(230, 220);
	glVertex2i(250, 220);
	glVertex2i(250, 310);
	glVertex2i(230, 310);
	glEnd();

	glColor3ub(color1, color2, color3);

	glBegin(GL_POLYGON);
	glVertex2i(230, 195);
	glVertex2i(320, 195);
	glVertex2i(320, 220);
	glVertex2i(230, 220);
	glEnd();

	glFlush();
}

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1200) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 740) / 2);
	glutInitWindowSize(1200, 740);
	glutCreateWindow("Roll Number");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
	return 0;
}
