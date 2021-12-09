#include <bits/stdc++.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#define PI 3.14159265359
using namespace std;

void myInit()
{
	glClearColor(0.9, 1.0, 1.0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-250, 250, -250, 250, -1, 1);
}

//flag is 1 if hyperbola is horizontal
//flag is 0 if hyperbola is vertical
void MidpointHyperbolaAlgo(int cx, int cy, float a, float b, int flag, int xmax, int ymax, int R, int G, int B)
{
	glPointSize(3);
	int p1 = round(((b * b) / 4) + (a / (b * b)) - (a * a));
	int x = a;
	int y = 0;
	// region 1
	while (((x * b * b) > (y * a * a)) and x < xmax and y < ymax)
	{
		if (p1 < 0)
		{
			x = x + 1;
			y = y + 1;
			glBegin(GL_POINTS);
			glColor3ub(R, G, B);
			if (flag == 1)
			{
				glVertex2i(cx + x, cy + y);
				glVertex2i(cx + x, cy - y);
				glVertex2i(cx - x, cy + y);
				glVertex2i(cx - x, cy - y);
			}
			else
			{
				glVertex2i(cy + y, cx + x);
				glVertex2i(cy - y, cx + x);
				glVertex2i(cy + y, cx - x);
				glVertex2i(cy - y, cx - x);
			}
			glEnd();
			p1 = p1 - ((a * a) * (1 + 2 * y)) + (2 * (b * b) * x);
		}
		else
		{
			x = x;
			y = y + 1;
			glBegin(GL_POINTS);
			glColor3ub(R, G, B);
			if (flag == 1)
			{
				glVertex2i(cx + x, cy + y);
				glVertex2i(cx + x, cy - y);
				glVertex2i(cx - x, cy + y);
				glVertex2i(cx - x, cy - y);
			}
			else
			{
				glVertex2i(cy + y, cx + x);
				glVertex2i(cy - y, cx + x);
				glVertex2i(cy + y, cx - x);
				glVertex2i(cy - y, cx - x);
			}
			glEnd();
			p1 = p1 - ((a * a) * (1 + 2 * y));
		}
	}
	// region 2
	int p2 = p1;
	while (y < ymax and x < xmax)
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
				glVertex2i(cx - x, cy + y);
				glVertex2i(cx - x, cy - y);
			}
			else
			{
				glVertex2i(cy + y, cx + x);
				glVertex2i(cy - y, cx + x);
				glVertex2i(cy + y, cx - x);
				glVertex2i(cy - y, cx - x);
			}
			glEnd();
			p2 = p2 + ((b * b) * (1 + (2 * x)));
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
				glVertex2i(cx - x, cy + y);
				glVertex2i(cx - x, cy - y);
			}
			else
			{
				glVertex2i(cy + y, cx + x);
				glVertex2i(cy - y, cx + x);
				glVertex2i(cy + y, cx - x);
				glVertex2i(cy - y, cx - x);
			}
			glEnd();
			p2 = p2 + ((b * b) * (1 + (2 * x))) - (2 * (a * a) * y);
		}
	}
}
void ParametricHyperbolaAlgo(int cx, int cy, int a, int b, int flag, int R, int G, int B)
{
	float t;
	glBegin(GL_POINTS);
	glColor3ub(R, G, B);
	if (flag == 1)
	{
		for (float i = 0; i <= 360; i = i + 0.01)
		{
			glVertex2f(cx + a / cos(i), cy + b * tan(i));
			glVertex2f(cx + a / cos(i), cy - b * tan(i));
			glVertex2f(cx - a / cos(i), cy + b * tan(i));
			glVertex2f(cx - a / cos(i), cy - b * tan(i));
		}
	}
	else
	{
		for (float i = 0; i <= 360; i = i + 0.01)
		{
			glVertex2f(cx + b * tan(i), cy + a / cos(i));
			glVertex2f(cx - b * tan(i), cy + a / cos(i));
			glVertex2f(cx + b * tan(i), cy - a / cos(i));
			glVertex2f(cx - b * tan(i), cy - a / cos(i));
		}
	}
	glEnd();
}

void GeneralHyperbolaAlgo(int cx, int cy, int a, int b, int flag, int xmax, int ymax, int R, int G, int B)
{
	float x = a;
	float y = 0;

	while (x <= xmax and y < ymax)
	{
		glPointSize(3);
		glBegin(GL_POINTS);
		glColor3ub(R, G, B);
		if (flag == 1)
		{
			glVertex2f(cx + x, cy + y);
			glVertex2f(cx - x, cy + y);
			glVertex2f(cx - x, cy - y);
			glVertex2f(cx + x, cy - y);
		}
		else
		{

			glVertex2f(cy + y, cx + x);
			glVertex2f(cy + y, cx - x);
			glVertex2f(cy - y, cx - x);
			glVertex2f(cy - y, cx + x);
		}
		glEnd();

		y += 0.01;
		x = a * (sqrt(b * b + y * y)) / b;
	}
}
void drawHyperbola()
{
	glPointSize(3);
	srand(time(0));
	int R = rand() % 256;
	int G = rand() % 256;
	int B = rand() % 256;
	int flag = rand() % 2;
	int a = (rand() % 61);
	int b = (rand() % 61);
	int cx = (rand() % 51);
	int cy = (rand() % 51);

	// using general equation
	// GeneralHyperbolaAlgo(cx, cy, a, b, flag, 500, 500, R, G, B);

	// using parametric form
	// ParametricHyperbolaAlgo(cx, cy, a, b, flag, R, G, B);

	// using Midpoint Hyperbola Drawing algo
	MidpointHyperbolaAlgo(cx, cy, a, b, flag, 500, 500, R, G, B);

	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1200) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 740) / 2);
	glutInitWindowSize(1200, 740);
	glutCreateWindow("Hyperbola");
	glutDisplayFunc(drawHyperbola);
	myInit();
	glutMainLoop();
	return 0;
}