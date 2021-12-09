#include <GL/glew.h>
#include <GL/freeglut.h>
#include <bits/stdc++.h>

void myInit()
{
	glClearColor(0.9, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 800.0, 0.0, 800.0); // Specify the display area
}

void dda(float x1, float y1, float x2, float y2)
{
	glPointSize(3);
	glBegin(GL_POINTS);
	float slope = 0;
	if (x2 == x1)
	{
		if (y1 < y2)
		{
			for (int i = y1; i <= y2; i++)
			{
				glVertex2f(round(x1), i);
			}
		}
		else
		{
			for (int i = y1; i >= y2; i--)
			{
				glVertex2f(round(x1), i);
			}
		}
	}
	else
	{
		slope = (y2 - y1) / (x2 - x1);
		float absslope = (slope >= 0) ? (slope) : (-1.0 * slope);
		if (absslope <= 1.0)
		{
			if (x1 < x2)
			{
				for (int i = x1; i <= x2; i++)
				{
					glVertex2f(i, round(y1));
					y1 = y1 + slope;
				}
			}
			else
			{
				for (int i = x1; i >= x2; i--)
				{
					glVertex2f(i, round(y1));
					y1 = y1 - slope;
				}
			}
		}
		else
		{
			if (y1 < y2)
			{
				for (int i = y1; i <= y2; i++)
				{
					glVertex2f(round(x1), i);
					x1 = x1 + (1.0 / slope);
				}
			}
			else
			{
				for (int i = y1; i >= y2; i--)
				{
					glVertex2f(round(x1), i);
					x1 = x1 - (1.0 / slope);
				}
			}
		}
	}
	glEnd();
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);
	//Center as (400,400) and radius as 150
	dda(475, 270, 325, 270);
	dda(325, 270, 250, 400);
	dda(250, 400, 325, 530);
	dda(325, 530, 475, 530);
	dda(475, 530, 550, 400);
	dda(550, 400, 475, 270);

	for (int i = 327; i < 477; i++)
	{
		dda(i, 272, i, 530);
	}
	// for(int i=)
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1200) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 740) / 2);
	glutInitWindowSize(1200, 740);
	glutCreateWindow("Hexagon");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
	return 0;
}
