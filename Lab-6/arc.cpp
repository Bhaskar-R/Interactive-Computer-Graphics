#include <bits/stdc++.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#define PI 3.141

void myInit()
{
	glClearColor(0.9, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-250, 250, -250, 250, -1, 1);
}

void mcdpartial(int cx, int cy, int r, int startAngle, int endAngle)
{
	glPointSize(3);
	r = abs(r);
	int d = 1 - r;
	int x = 0;
	int y = r;
	int y_f = floor(y / sqrt(2)) - 1;
	if (startAngle < 0 and endAngle > 0)
	{
		int startAngle1 = 360 + startAngle;
		mcdpartial(cx, cy, r, startAngle1, 0);
	}

	if (startAngle < 0 and endAngle < 0)
	{
		startAngle = 360 + startAngle;
		endAngle = 360 + endAngle;
	}

	if (startAngle > endAngle)
		std::swap(startAngle, endAngle);

	if (endAngle > 360)
	{
		startAngle = startAngle - endAngle % 360;
		endAngle = 360;
	}

	while (y != y_f)
	{
		glBegin(GL_POINTS);
		glColor3f(1, 0, 0);
		int angle[8] = {0};
		int alpha;
		alpha = (atan((float)y / x) * 180) / PI;
		angle[0] = alpha;
		angle[1] = 90 - alpha;
		angle[2] = 270 + alpha;
		angle[3] = 360 - alpha;
		angle[4] = 180 + alpha;
		angle[5] = 270 - alpha;
		angle[6] = 270 - alpha;
		angle[7] = 180 - alpha;

		if (angle[0] >= startAngle && angle[0] <= endAngle)
			glVertex2i(cx + x, cy + y);

		if (angle[1] >= startAngle && angle[1] <= endAngle)
			glVertex2i(cx + y, cy + x);

		if (angle[2] >= startAngle && angle[2] <= endAngle)
			glVertex2i(cx + y, cy - x);

		if (angle[3] >= startAngle && angle[3] <= endAngle)
			glVertex2i(cx + x, cy - y);

		if (angle[4] >= startAngle && angle[4] <= endAngle)
			glVertex2i(cx - x, cy - y);

		if (angle[5] >= startAngle && angle[5] <= endAngle)
			glVertex2i(cx - y, cy - x);

		if (angle[6] >= startAngle && angle[6] <= endAngle)
			glVertex2i(cx - y, cy + x);

		if (angle[7] >= startAngle && angle[7] <= endAngle)
			glVertex2i(cx - x, cy + y);

		glEnd();

		x = x + 1;
		if (d < 0)
		{
			d += (2 * x) + 3;
			y = y;
		}
		else
		{
			d += (2 * (x - y)) + 5;
			y = y - 1;
		}
	}
}

void Arc()
{
	glClear(GL_COLOR_BUFFER_BIT);
	mcdpartial(0, 0, 200, 230, 260);

	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1200) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 740) / 2);
	glutInitWindowSize(1200, 740);
	glutCreateWindow("Arc");
	glutDisplayFunc(Arc);
	myInit();
	glutMainLoop();
	return 0;
}