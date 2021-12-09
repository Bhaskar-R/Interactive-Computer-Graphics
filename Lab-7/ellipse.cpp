#include <bits/stdc++.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#define PI 3.14159265359

void myInit()
{
	glClearColor(0.9, 1.0, 1.0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-250, 250, -250, 250, -1, 1);
}

void GeneralEllipse(int cx, int cy, int a, int b, int rr, int rg, int rb)
{
	int x = 0;
	int y = b;
	int dx = a * a * y;
	int dy = b * b * x;

	while (y >= 0)
	{
		glBegin(GL_POINTS);
		glColor3ub(rr, rg, rb);
		glVertex2i(cx + x, cy + y);
		glVertex2i(cx - x, cy + y);
		glVertex2i(cx - x, cy - y);
		glVertex2i(cx + x, cy - y);
		glEnd();

		if (dy < dx)
		{
			x = x + 1;
			y = round(sqrt(((a * a * b * b) - (b * b * (x) * (x))) / (a * a)));
		}
		else
		{
			y = y - 1;
			x = round(sqrt(((a * a * b * b) - (a * a * (y) * (y))) / (b * b)));
		}
		dx = a * a * y;
		dy = b * b * x;
	}
}

void ParametricEllipse(int cx, int cy, int a, int b, int rr, int rg, int rb)
{
	glBegin(GL_POINTS);
	glColor3ub(rr, rg, rb);
	for (int i = 0; i <= 360; i++)
	{
		GLfloat theta = i * PI / 180;
		glVertex2f(cx + a * cos(theta), cy + b * sin(theta));
	}
	glEnd();
}

void MidpointEllipse(int cx, int cy, int a, int b, int rr, int rg, int rb)
{
	// decision parameter for region 1
	float p1 = (b * b) - (a * a * b) + (0.25 * a * a);
	int x = 0;
	int y = b;
	int dx = 2 * a * a * y;
	int dy = 2 * b * b * x;

	// region 1
	while (dy <= dx)
	{
		glBegin(GL_POINTS);
		glColor3ub(rr, rg, rb);
		glVertex2i(cx + x, cy + y);
		glVertex2i(cx - x, cy + y);
		glVertex2i(cx - x, cy - y);
		glVertex2i(cx + x, cy - y);
		glEnd();

		x = x + 1;
		if (p1 < 0)
		{
			dy = dy + (2 * b * b);
			p1 = p1 + dy + (b * b);
		}
		else
		{
			dy = dy + (2 * b * b);
			dx = dx - (2 * a * a);
			p1 = p1 + dy - dx + (b * b);
			y = y - 1;
		}
	}

	// decision parameter for region 2
	float p2 = ((b * b) * ((x + 0.5) * (x + 0.5))) + ((a * a) * ((y - 1) * (y - 1))) - (a * a * b * b);

	//region 2
	while (y >= 0)
	{
		glBegin(GL_POINTS);
		glColor3ub(rr, rg, rb);
		glVertex2i(cx + x, cy + y);
		glVertex2i(cx - x, cy + y);
		glVertex2i(cx - x, cy - y);
		glVertex2i(cx + x, cy - y);
		glEnd();

		y = y - 1;
		if (p2 > 0)
		{
			dx = dx - (2 * a * a);
			p2 = p2 + (a * a) - dx;
		}
		else
		{
			x = x + 1;
			dy = dy + (2 * b * b);
			dx = dx - (2 * a * a);
			p2 = p2 + dy - dx + (a * a);
		}
	}
}

void drawEllipse()
{
	glPointSize(3);
	srand(time(0));
	int rr = rand() % 256;
	int rg = rand() % 256;
	int rb = rand() % 256;

	int a = (rand() % 51) + 50;
	int b = (rand() % 51) + 50;
	int cx = (rand() % 51);
	int cy = (rand() % 51);

	// using general equation
	GeneralEllipse(cx, cy, a, b, rr, rg, rb);

	// using parametric form
	ParametricEllipse(cx, cy, a, b, rr, rg, rb);

	// midpoint
	MidpointEllipse(cx, cy, a, b, rr, rg, rb);

	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1200) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 740) / 2);
	glutInitWindowSize(1200, 740);
	glutCreateWindow("Ellipse");
	glutDisplayFunc(drawEllipse);
	myInit();
	glutMainLoop();
	return 0;
}