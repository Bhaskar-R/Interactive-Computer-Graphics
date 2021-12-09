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

//flag is 1 if parabola is horizontal
//flag is 0 if parabola is vertical
void MidpointParabolaAlgo(int cx, int cy, int a, int flag, int xmax, int ymax, int R, int G, int B)
{
	glPointSize(3);
	// decision parameter for region 1
	if (flag == 0)
		ymax = xmax;
	int p1;
	p1 = round(1 - 2 * a);
	int x = 0;
	int y = 0;
	// region 1
	while (y < 2 * a)
	{
		if (p1 < 0)
		{
			x = x;
			y = y + 1;
			glBegin(GL_POINTS);
			glColor3ub(R, G, B);
			if (flag == 1)
			{
				glVertex2i(cx + x, cy + y);
				glVertex2i(cx + x, cy - y);
			}
			else
			{
				glVertex2i(cy + y, cx + x);
				glVertex2i(cy - y, cx + x);
			}
			glEnd();
			p1 = p1 + 1 + 2 * y;
		}
		else
		{
			x = x + 1;
			y = y + 1;
			glBegin(GL_POINTS);
			glColor3ub(R, G, B);
			if (flag == 1)
			{
				glVertex2i(cx + x, cy + y);
				glVertex2i(cx + x, cy - y);
			}
			else
			{
				glVertex2i(cy + y, cx + x);
				glVertex2i(cy - y, cx + x);
			}
			glEnd();
			p1 = p1 + 1 + 2 * y - 4 * a;
		}
	}
	// region 2
	int p2 = round(0.25 - 2 * a);
	x = a;
	y = 2 * a;
	while (y < ymax)
	{
		if (p2 > 0)
		{
			x = x + 1;
			y = y;
			glBegin(GL_POINTS);
			glColor3ub(R, G, B);
			if (flag == 1)
			{
				glVertex2i(cx + x, cy + y);
				glVertex2i(cx + x, cy - y);
			}
			else
			{
				glVertex2i(cy + y, cx + x);
				glVertex2i(cy - y, cx + x);
			}
			glEnd();
			p2 = p2 - 4 * a;
		}
		else
		{
			x = x + 1;
			y = y + 1;
			glBegin(GL_POINTS);
			glColor3ub(R, G, B);
			if (flag == 1)
			{
				glVertex2i(cx + x, cy + y);
				glVertex2i(cx + x, cy - y);
			}
			else
			{
				glVertex2i(cy + y, cx + x);
				glVertex2i(cy - y, cx + x);
			}
			glEnd();
			p2 = p2 - 4 * a + 2 * y;
		}
	}
}

void ParametricParabolaAlgo(int cx, int cy, int a, int flag, int R, int G, int B)
{
	float t;
	glBegin(GL_POINTS);
	glColor3ub(R, G, B);
	for (int i = 0; i <= 300; i++)
	{
		t = i / 100.0;
		if (flag == 1)
		{
			glVertex2f(cx + a * t * t, cy + 2 * a * t);
			glVertex2f(cx + a * t * t, cy - 2 * a * t);
		}
		else
		{
			glVertex2f(cx + 2 * a * t, cy + a * t * t);
			glVertex2f(cx - 2 * a * t, cy + a * t * t);
		}
	}
	glEnd();
}

void GeneralParabolaAlgo(int cx, int cy, int a, int flag, int xmax, int ymax, int R, int G, int B)
{
	float x = 0;
	float y = 0;
	if (flag == 1)
		ymax = xmax;
	while (x <= a and y <= 2 * a)
	{
		glBegin(GL_POINTS);
		glColor3ub(R, G, B);
		if (flag == 0)
		{
			glVertex2f(cx + y, cy + x);
			glVertex2i(cx - y, cy + x);
		}
		else
		{
			glVertex2f(cx + x, cy + y);
			glVertex2i(cx + x, cy - y);
		}
		glEnd();

		x += 0.01;
		y = sqrt(4 * a * x);
	}
	while (y > 2 * a and y <= ymax)
	{

		glBegin(GL_POINTS);
		glColor3ub(R, G, B);
		if (flag == 0)
		{
			glVertex2f(cx + y, cy + x);
			glVertex2i(cx - y, cy + x);
		}
		else
		{
			glVertex2f(cx + x, cy + y);
			glVertex2i(cx + x, cy - y);
		}
		glEnd();

		x = (y * y) / (4 * a);
		y += 0.01;
	}
}

void drawParabola()
{
	glPointSize(3);
	srand(time(0));
	int R = rand() % 256;
	int G = rand() % 256;
	int B = rand() % 256;
	int flag = rand() % 2;
	int a = (rand() % 61);
	// int a = -50;
	int cx = (rand() % 51);
	int cy = (rand() % 51);

	// using general equation
	// GeneralParabolaAlgo(cx, cy, a, flag, 500, 500, R, G, B);

	// using parametric form
	// ParametricParabolaAlgo(cx, cy, a, flag, R, G, B);

	// using Midpoint Parabola Drawing algo
	MidpointParabolaAlgo(cx, cy, a, flag, 500, 500, R, G, B);

	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1200) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 740) / 2);
	glutInitWindowSize(1200, 740);
	glutCreateWindow("Parabola");
	glutDisplayFunc(drawParabola);
	myInit();
	glutMainLoop();
	return 0;
}