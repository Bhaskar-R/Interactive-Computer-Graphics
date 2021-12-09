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

	//Letter I
	glColor3ub(color1, color2, color3);

	glBegin(GL_POLYGON);
	glVertex2i(60, 90);
	glVertex2i(80, 90);
	glVertex2i(80, 310);
	glVertex2i(60, 310);
	glEnd();

	glColor3ub(color1, color2, color3);

	glBegin(GL_POLYGON);
	glVertex2i(20, 310);
	glVertex2i(120, 310);
	glVertex2i(120, 335);
	glVertex2i(20, 335);
	glEnd();

	glColor3ub(color1, color2, color3);

	glBegin(GL_POLYGON);
	glVertex2i(20, 65);
	glVertex2i(120, 65);
	glVertex2i(120, 90);
	glVertex2i(20, 90);
	glEnd();

	// Letter C
	glColor3ub(color1, color2, color3);

	glBegin(GL_POLYGON);
	glVertex2i(150, 90);
	glVertex2i(170, 90);
	glVertex2i(170, 310);
	glVertex2i(150, 310);
	glEnd();

	glColor3ub(color1, color2, color3);

	glBegin(GL_POLYGON);
	glVertex2i(150, 310);
	glVertex2i(230, 310);
	glVertex2i(230, 335);
	glVertex2i(150, 335);
	glEnd();

	glColor3ub(color1, color2, color3);

	glBegin(GL_POLYGON);
	glVertex2i(150, 65);
	glVertex2i(230, 65);
	glVertex2i(230, 90);
	glVertex2i(150, 90);
	glEnd();

	//Letter G
	glColor3ub(color1, color2, color3);

	glBegin(GL_POLYGON);
	glVertex2i(260, 90);
	glVertex2i(280, 90);
	glVertex2i(280, 310);
	glVertex2i(260, 310);
	glEnd();

	glColor3ub(color1, color2, color3);

	glBegin(GL_POLYGON);
	glVertex2i(260, 310);
	glVertex2i(350, 310);
	glVertex2i(350, 335);
	glVertex2i(260, 335);
	glEnd();

	glColor3ub(color1, color2, color3);

	glBegin(GL_POLYGON);
	glVertex2i(260, 65);
	glVertex2i(340, 65);
	glVertex2i(340, 90);
	glVertex2i(260, 90);
	glEnd();

	glColor3ub(color1, color2, color3);

	glBegin(GL_POLYGON);
	glVertex2i(340, 65);
	glVertex2i(360, 65);
	glVertex2i(360, 160);
	glVertex2i(340, 160);
	glEnd();

	glColor3ub(color1, color2, color3);

	glBegin(GL_POLYGON);
	glVertex2i(310, 160);
	glVertex2i(360, 160);
	glVertex2i(360, 190);
	glVertex2i(310, 190);
	glEnd();

	glFlush();
}

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1200) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 740) / 2);
	glutInitWindowSize(1200, 740);
	glutCreateWindow("ICG");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
	return 0;
}
