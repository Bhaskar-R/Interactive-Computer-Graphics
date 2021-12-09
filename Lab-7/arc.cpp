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

void MidpointEllipse(int cx, int cy, int a, int b, int rr, int rg, int rb)
{
	//Decision parameter for region 1
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
			y = y;
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

void fillEllipse(int cx, int cy, int a, int b, int startAngle, int endAngle, int rr, int rg, int rb)
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

		int angle[4] = {0};
		int alpha;
		alpha = (atan2((y - cy), (x - cx)) * 180) / PI;
		angle[0] = alpha;
		angle[1] = 180 - alpha;
		angle[2] = 180 + alpha;
		angle[3] = 360 - alpha;

		if (angle[0] >= startAngle && angle[0] <= endAngle)
			glVertex2i(cx + x, cy + y);

		if (angle[1] >= startAngle && angle[1] <= endAngle)
			glVertex2i(cx - x, cy + y);

		if (angle[2] >= startAngle && angle[2] <= endAngle)
			glVertex2i(cx - x, cy - y);

		if (angle[3] >= startAngle && angle[3] <= endAngle)
			glVertex2i(cx + x, cy - y);
		glEnd();

		x = x + 1;
		if (p1 < 0)
		{
			dy = dy + (2 * b * b);
			p1 = p1 + dy + (b * b);
			y = y;
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

		int angle[4] = {0};
		int alpha;
		alpha = (atan2((y - cy), (x - cx)) * 180) / PI;
		angle[0] = alpha;
		angle[1] = 180 - alpha;
		angle[2] = 180 + alpha;
		angle[3] = 360 - alpha;

		if (angle[0] >= startAngle && angle[0] <= endAngle)
			glVertex2i(cx + x, cy + y);

		if (angle[1] >= startAngle && angle[1] <= endAngle)
			glVertex2i(cx - x, cy + y);

		if (angle[2] >= startAngle && angle[2] <= endAngle)
			glVertex2i(cx - x, cy - y);

		if (angle[3] >= startAngle && angle[3] <= endAngle)
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

void InvertedfillEllipse(int cx, int cy, int a, int b, int startAngle, int endAngle, int rr, int rg, int rb)
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

		int angle[4] = {0};
		int alpha;
		alpha = (atan2((y - cy), (x - cx)) * 180) / PI;
		angle[0] = alpha;
		angle[1] = 180 - alpha;
		angle[2] = 180 + alpha;
		angle[3] = 360 - alpha;

		if ((angle[0] <= startAngle || angle[0] >= endAngle))
			glVertex2i(cx + x, cy + y);

		if ((angle[1] <= startAngle || angle[1] >= endAngle))
			glVertex2i(cx - x, cy + y);

		if ((angle[2] <= startAngle || angle[2] >= endAngle))
			glVertex2i(cx - x, cy - y);

		if ((angle[3] <= startAngle || angle[3] >= endAngle))
			glVertex2i(cx + x, cy - y);
		glEnd();

		x = x + 1;
		if (p1 < 0)
		{
			dy = dy + (2 * b * b);
			p1 = p1 + dy + (b * b);
			y = y;
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

		int angle[4] = {0};
		int alpha;
		alpha = (atan2((y - cy), (x - cx)) * 180) / PI;
		angle[0] = alpha;
		angle[1] = 180 - alpha;
		angle[2] = 180 + alpha;
		angle[3] = 360 - alpha;

		if ((angle[0] <= startAngle || angle[0] >= endAngle))
			glVertex2i(cx + x, cy + y);

		if ((angle[1] <= startAngle || angle[1] >= endAngle))
			glVertex2i(cx - x, cy + y);

		if ((angle[2] <= startAngle || angle[2] >= endAngle))
			glVertex2i(cx - x, cy - y);

		if ((angle[3] <= startAngle || angle[3] >= endAngle))
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

void MidpointPartialEllipse(int cx, int cy, int a, int b, int startAngle, int endAngle, int rr, int rg, int rb)
{
	// Angle correction
	if ((endAngle - startAngle) >= 360 || (endAngle - startAngle) <= (-360))
	{
		startAngle = 0;
		endAngle = 360;
		MidpointEllipse(cx, cy, a, b, rr, rg, rb);
	}
	else
	{
		if (startAngle >= 0 && endAngle >= 0)
		{
			if (endAngle >= startAngle)
			{
				fillEllipse(cx, cy, a, b, startAngle, endAngle, rr, rg, rb);
			}
			else
			{
				fillEllipse(cx, cy, a, b, endAngle, startAngle, rr, rg, rb);
			}
		}
		else if (startAngle >= 0 && endAngle <= 0)
		{
			endAngle = 360 + endAngle;
			InvertedfillEllipse(cx, cy, a, b, startAngle, endAngle, rr, rg, rb);
		}
		else if (startAngle <= 0 && endAngle <= 0)
		{
			startAngle = 360 + startAngle;
			endAngle = 360 + endAngle;
			if (endAngle >= startAngle)
			{
				fillEllipse(cx, cy, a, b, startAngle, endAngle, rr, rg, rb);
			}
			else
			{
				fillEllipse(cx, cy, a, b, endAngle, startAngle, rr, rg, rb);
			}
		}
		else if (startAngle <= 0 && endAngle >= 0)
		{
			startAngle = 360 + startAngle;
			InvertedfillEllipse(cx, cy, a, b, endAngle, startAngle, rr, rg, rb);
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

	int startAngle = (rand() % 721) - 360;
	int endAngle = (rand() % 721) - 360;
	int a = (rand() % 51) + 50;
	int b = (rand() % 51) + 50;
	int cx = (rand() % 101) - 50;
	int cy = (rand() % 101) - 50;

	MidpointPartialEllipse(cx, cy, a, b, startAngle, endAngle, rr, rg, rb);

	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1200) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 740) / 2);
	glutInitWindowSize(1200, 740);
	glutCreateWindow("ARC");
	glutDisplayFunc(drawEllipse);
	myInit();
	glutMainLoop();
	return 0;
}
