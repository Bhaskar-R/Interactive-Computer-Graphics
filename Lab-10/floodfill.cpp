#include <bits/stdc++.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
using namespace std;
const int SIZE = 1000;

int round_(double val)
{
	float dec = abs(val - (int)val);
	if (val > 0)
	{
		if (dec < 0.5)
			return (int)val;
		else
			return (int)val + 1;
	}
	else
	{
		if (dec <= 0.5)
			return (int)val;
		else
			return (int)val - 1;
	}
}

void drawLine(double x1, double y1, double x2, double y2)
{
	glBegin(GL_POINTS);
	double slope = (y2 - y1) / (x2 - x1);
	if (slope >= -1 && slope <= 1)
	{

		if (x2 < x1)
		{ //(x1,y1) is made to have lesser abscissa
			double temp1, temp2;
			temp1 = x1;
			temp2 = y1;
			x1 = x2;
			y1 = y2;
			x2 = temp1;
			y2 = temp2;
		}
		double y = y1;
		for (double x = x1; x <= x2; x++)
		{
			glVertex2d(x, (double)round_(y));
			y = y + slope;
		}
	}
	else
	{

		if (y2 < y1)
		{ //(x1,y1) is made to have lesser ordinate
			double temp1, temp2;
			temp1 = x1;
			temp2 = y1;
			x1 = x2;
			y1 = y2;
			x2 = temp1;
			y2 = temp2;
		}
		double x = x1;
		for (double y = y1; y <= y2; y++)
		{
			glVertex2d((double)round_(x), y);
			x += 1 / slope;
		}
	}
	glEnd();
}

void draw()
{
	srand(time(0));
	glClear(GL_COLOR_BUFFER_BIT);
	int n = 3 + rand() % (6);
	vector<pair<double, double>> points;
	for (int i = 0; i < n; i++)
		points.push_back({rand() % SIZE, rand() % SIZE});
	points.push_back({points[0].first, points[0].second});

	//polygon
	glPointSize(1);
	glColor3f(0, 1, 0);
	for (int i = 0; i < n; i++)
		drawLine(points[i].first, points[i].second, points[i + 1].first, points[i + 1].second);
	glFlush();
}

void floodFill(GLint x, GLint y, float prevColor[3], float newColor[3])
{
	float color[3];
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
	if (color[0] == prevColor[0] && color[1] == prevColor[1] && color[2] == prevColor[2])
	{
		glColor3f(newColor[0], newColor[1], newColor[2]);
		glBegin(GL_POINTS);
		glVertex2d(x, y);
		glEnd();
		glFlush();

		floodFill(x + 1, y, prevColor, newColor);
		floodFill(x, y + 1, prevColor, newColor);
		floodFill(x - 1, y, prevColor, newColor);
		floodFill(x, y - 1, prevColor, newColor);
	}
}

void click(int button, int state, int x, int y)
{
	float prevColor[3] = {1, 1, 1};
	float newColor[3] = {1, 0, 0};
	floodFill(x, SIZE - y, prevColor, newColor);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(SIZE, SIZE);
	glutCreateWindow("Flood Fill");
	glClearColor(1, 1, 1, 0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, SIZE, 0, SIZE);
	glutDisplayFunc(draw);
	glutMouseFunc(click);
	glutMainLoop();
	return 0;
}
