#include <bits/stdc++.h>
#include <GL/freeglut.h>
using namespace std;
const int P_limit = 30;

void myInit()
{
	glClearColor(0.9, 0.9, 0.9, 0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 400, 0, 400);
}

// y-value of point of intersection of two lines
int intersect_y(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	int top = (x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4);
	int bot = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	return top / bot;
}
// x-value of point of intersection of two lines
int intersect_x(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	int top = (x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4);
	int bot = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	return top / bot;
}

void clip_(int p_vertices[][2], int &p_size, int x1, int y1, int x2, int y2)
{
	int New_points[P_limit][2], temp_size = 0;
	for (int i = 0; i < p_size; i++)
	{
		int j = (i + 1) % p_size;
		int ix = p_vertices[i][0];
		int iy = p_vertices[i][1];
		int jx = p_vertices[j][0];
		int jy = p_vertices[j][1];

		int i_ = (x2 - x1) * (iy - y1) - (y2 - y1) * (ix - x1);
		int j_ = (x2 - x1) * (jy - y1) - (y2 - y1) * (jx - x1);

		//Both point inside
		if (i_ < 0 && j_ < 0)
		{
			New_points[temp_size][0] = jx;
			New_points[temp_size][1] = jy;
			temp_size++;
		}
		//First point is outside
		else if (i_ >= 0 && j_ < 0)
		{
			New_points[temp_size][0] = intersect_x(x1, y1, x2, y2, ix, iy, jx, jy);
			New_points[temp_size][1] = intersect_y(x1, y1, x2, y2, ix, iy, jx, jy);
			temp_size++;

			New_points[temp_size][0] = jx;
			New_points[temp_size][1] = jy;
			temp_size++;
		}
		//Second point is outside
		else if (i_ < 0 && j_ >= 0)
		{
			//Only point of intersection with edge is added
			New_points[temp_size][0] = intersect_x(x1, y1, x2, y2, ix, iy, jx, jy);
			New_points[temp_size][1] = intersect_y(x1, y1, x2, y2, ix, iy, jx, jy);
			temp_size++;
		}
	}
	p_size = temp_size;
	for (int i = 0; i < p_size; i++)
	{
		p_vertices[i][0] = New_points[i][0];
		p_vertices[i][1] = New_points[i][1];
	}
}

void Sutherland_(int p_vertices[][2], int &p_size, int Window_[][2], int window_size)
{
	for (int i = 0; i < window_size; i++)
	{
		int j = (i + 1) % window_size;
		clip_(p_vertices, p_size, Window_[i][0], Window_[i][1], Window_[j][0], Window_[j][1]);
	}
}

void display()
{
	int points = (rand() % 150) + 10;
	glClear(GL_COLOR_BUFFER_BIT);
	int xmin, xmax, ymin, ymax;
	xmin = ((rand() % 100) + 50);
	xmax = ((rand() % 100) + 250);
	ymin = ((rand() % 100) + 50);
	ymax = ((rand() % 100) + 250);
	int window_size = 4;

	int Window_[][2] = {{xmin, ymin}, {xmin, ymax}, {xmax, ymax}, {xmax, ymin}};
	glPointSize(3);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.5, 0.5, 0.8);
	glVertex2f(xmin, ymax);
	glVertex2f(xmin, ymin);
	glVertex2f(xmax, ymin);
	glVertex2f(xmax, ymax);
	glEnd();

	int p_size = 5;
	int p_vertices[20][2] = {{90, 150}, {150, 375}, {250, 300}, {220, 200}, {160, 100}};

	Sutherland_(p_vertices, p_size, Window_, window_size);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	for (int i = 0; i < p_size; i++)
		glVertex2d(p_vertices[i][0], p_vertices[i][1]);
	glEnd();
	glFlush();
}

int main(int argc, char **argv)
{
	srand(time(0));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1200) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 740) / 2);
	glutInitWindowSize(1200, 740);
	glutCreateWindow("Sutherland - Polygon Clipping");
	glutDisplayFunc(display);
	myInit();
	glutMainLoop();
	return 0;
}
