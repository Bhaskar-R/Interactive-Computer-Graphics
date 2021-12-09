#include <bits/stdc++.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
using namespace std;
const int SIZE = 1000;

void myInit()
{
	glClearColor(0.9, 0.9, 0.9, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 1000, 0, 1000);
}

double spoint(double p1, double p2, double p3, double p4, double q1, double q2, double q3, double q4)
{
	double res = 0;
	if (p1 < 0)
		res = (q1 / p1 > res) ? q1 / p1 : res;
	if (p2 < 0)
		res = (q2 / p2 > res) ? q2 / p2 : res;
	if (p3 < 0)
		res = (q3 / p3 > res) ? q3 / p3 : res;
	if (p4 < 0)
		res = (q4 / p4 > res) ? q4 / p4 : res;
	return res;
}

double epoint(double p1, double p2, double p3, double p4, double q1, double q2, double q3, double q4)
{
	double res = 1;
	if (p1 > 0)
		res = ((q1 / p1) < res) ? q1 / p1 : res;
	if (p2 > 0)
		res = ((q2 / p2) < res) ? q2 / p2 : res;
	if (p3 > 0)
		res = ((q3 / p3) < res) ? q3 / p3 : res;
	if (p4 > 0)
		res = ((q4 / p4) < res) ? q4 / p4 : res;
	return res;
}
void draw()
{
	srand(time(0));
	int n = 25;
	int a_count = 0, r_count = 0;
	vector<vector<int>> lines;
	for (int i = 0; i < n; i++)
		lines.push_back({rand() % SIZE, rand() % SIZE, rand() % SIZE, rand() % SIZE});

	int x_min, x_max, y_min, y_max;
	y_min = 50 + rand() % 500;
	x_min = 70 + rand() % 500;
	x_max = x_min + 200 + rand() % 500;
	y_max = y_min + 200 + rand() % 500;

	glBegin(GL_POLYGON);
	glVertex2d(x_min, y_min);
	glVertex2d(x_max, y_min);
	glVertex2d(x_max, y_max);
	glVertex2d(x_min, y_max);
	glEnd();

	glPointSize(2);
	glBegin(GL_POINTS);
	for (int i = 0; i < n; i++)
	{
		double x1 = lines[i][0], y1 = lines[i][1], x2 = lines[i][2], y2 = lines[i][3];
		int delx = x2 - x1, dely = y2 - y1;
		double p1 = -delx, p2 = delx, p3 = -dely, p4 = dely;
		double q1 = x1 - x_min, q2 = x_max - x1, q3 = y1 - y_min, q4 = y_max - y1;
		double u1, u2;

		glColor3f(1, 0, 0);
		glBegin(GL_LINES);
		glVertex2d(x1, y1);
		glVertex2d(x2, y2);
		glEnd();
		if ((p1 == 0 || p2 == 0) && (q1 < 0 || q2 < 0))
			r_count++;
		else if ((p3 == 0 || p4 == 0) && (q3 < 0 || q4 < 0))
			r_count++;
		else
		{
			u1 = spoint(p1, p2, p3, p4, q1, q2, q3, q4);
			u2 = epoint(p1, p2, p3, p4, q1, q2, q3, q4);

			if (u1 <= u2)
			{
				x2 = x1 + u2 * delx;
				y2 = y1 + u2 * dely;
				x1 = x1 + u1 * delx;
				y1 = y1 + u1 * dely;

				glColor3f(0, 1, 0);
				glBegin(GL_LINES);
				glVertex2d(x1, y1);
				glVertex2d(x2, y2);
				glEnd();
				a_count++;
			}
			else
				r_count++;
		}
	}
	glEnd();
	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1200) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 740) / 2);
	glutInitWindowSize(1200, 740);
	glutCreateWindow("Line Clipping Liang_Barsky");
	glutDisplayFunc(draw);
	myInit();
	glutMainLoop();
	return 0;
}
