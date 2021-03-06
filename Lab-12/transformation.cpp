#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#define PI 3.14159

//DDA line drawing algo
void drawline(int X1, int Y1, int X2, int Y2)
{
	glColor3f(0.875, 0.875, 0.875);
	glPointSize(1);
	double x, y, dx, dy, length;
	int i;
	dx = (double)abs(X2 - X1);
	dy = (double)abs(Y2 - Y1);
	if (dx >= dy)
		length = dx;
	else
		length = dy;

	dx = (X2 - X1) / length;
	dy = (Y2 - Y1) / length;
	x = (double)X1;
	y = (double)Y1;
	i = 1;
	while (i <= length)
	{
		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();
		x = x + dx;
		y = y + dy;
		i = i + 1;
	}
	glEnd();
}

void translate(int a, int b)
{
	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(4);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-200 + a, 0 + b, 0);
	glVertex3f(-150 + a, -200 + b, 0);
	glVertex3f(150 + a, -200 + b, 0);
	glVertex3f(200 + a, 0 + b, 0);
	glVertex3f(0 + a, 200 + b, 0);
	glEnd();
}

void rotate(int angle)
{
	double theta = angle * PI / 180.0;
	double cosine = cos(theta);
	double sine = sin(theta);
	glColor3f(0.2, 1.0, 0.0);
	glLineWidth(4);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-200 * cosine - 0 * sine, -200 * sine + 0 * cosine, 0);
	glVertex3f(-150 * cosine - (-200) * sine, -150 * sine + (-200) * cosine, 0);
	glVertex3f(150 * cosine - (-200) * sine, 150 * sine + (-200) * cosine, 0);
	glVertex3f(200 * cosine - (0) * sine, 200 * sine + (0) * cosine, 0);
	glVertex3f(0 * cosine - (200) * sine, 0 * sine + (200) * cosine, 0);
	glEnd();
}

void scale(int sx, int sy)
{
	glColor3f(1, 0, 0.9);
	glLineWidth(4);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-200 * sx, 0 * sy, 0);
	glVertex3f(-150 * sx, -200 * sy, 0);
	glVertex3f(150 * sx, -200 * sy, 0);
	glVertex3f(200 * sx, 0 * sy, 0);
	glVertex3f(0 * sx, 200 * sy, 0);
	glEnd();
}

void reflect()
{
	//Along x axis(Y=0)
	glColor3f(0.6, 0.2, 1.0);
	glLineWidth(4);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-200, 0, 0);
	glVertex3f(-150, 200, 0);
	glVertex3f(150, 200, 0);
	glVertex3f(200, 0, 0);
	glVertex3f(0, -200, 0);
	glEnd();

	//Along y axis(X=0)
	glColor3f(0.7, 0.8, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(200, 0, 0);
	glVertex3f(150, -200, 0);
	glVertex3f(-150, -200, 0);
	glVertex3f(-200, 0, 0);
	glVertex3f(0, 200, 0);
	glEnd();

	//Along x=y
	glColor3f(0.3, 0.2, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -200, 0);
	glVertex3f(-200, -150, 0);
	glVertex3f(-200, 150, 0);
	glVertex3f(0, 200, 0);
	glVertex3f(200, 0, 0);
	glEnd();

	//Along y=-x
	glColor3f(0.9, 0.1, 0.4);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 200, 0);
	glVertex3f(200, 150, 0);
	glVertex3f(200, -150, 0);
	glVertex3f(0, -200, 0);
	glVertex3f(-200, 0, 0);
	glEnd();
}

void shear(int b, int c)
{
	glColor3f(1.0, 0.6, 0.3);
	glLineWidth(4);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-200 + b * 0, 0 + c * -200, 0);
	glVertex3f(-150 + b * -200, -200 + c * -150, 0);
	glVertex3f(150 + b * -200, -200 + c * 150, 0);
	glVertex3f(200 + b * 0, 0 + c * 200, 0);
	glVertex3f(0 + b * 200, 200 + c * 0, 0);
	glEnd();
}

void transform()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//Axes
	drawline(0, -600, 0, 600);
	drawline(-600, 0, 600, 0);
	//draw polygon
	glColor3f(0.5, 0.8, 1.0);
	glLineWidth(4);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-200, 0, 0);
	glVertex3f(-150, -200, 0);
	glVertex3f(150, -200, 0);
	glVertex3f(200, 0, 0);
	glVertex3f(0, 200, 0);
	glEnd();

	//Translation
	int a = 240, b = 250;
	translate(a, b);

	//Rotate
	int theta = 90;
	rotate(theta);

	//Scaling
	int sx = 2, sy = 2;
	scale(sx, sy);

	//Reflect
	reflect();

	//Shearing
	int sfx = 0, sfy = 1;
	shear(sfx, sfy);
	glFlush();
}

void myinit(void)
{
	glClearColor(0.9, 0.9, 0.9, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 600, 480);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-600.0, 600.0, -480.0, 480.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1200) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 740) / 2);
	glutInitWindowSize(1200, 740);
	glutCreateWindow("Basic Tranformations");
	glutDisplayFunc(transform);
	myinit();
	glFlush();
	glutMainLoop();
	return 0;
}