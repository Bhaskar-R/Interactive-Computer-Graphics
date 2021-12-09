#include <GL/glew.h>
#include <GL/freeglut.h>
#include <bits/stdc++.h>

void myInit()
{
	glClearColor(0.9, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 400.0, 0.0, 400.0); // Specify the display area
}

void bld(int x1, int y1, int x2, int y2)
{
	int dx, dy, i, Pk, x, y;
	int incx, incy, inc1, inc2;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);

	incx = (x2 < x1) ? -1 : 1;
	incy = (y2 < y1) ? -1 : 1;
	x = x1;
	y = y1;
	if (dx > dy)
	{
		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();
		Pk = 2 * dy - dx;
		inc1 = 2 * (dy - dx);
		inc2 = 2 * dy;
		for (i = 0; i < dx; i++)
		{
			if (Pk >= 0)
			{
				y += incy;
				Pk += inc1;
			}
			else
				Pk += inc2;
			x += incx;
			glBegin(GL_POINTS);
			glVertex2i(x, y);
			glEnd();
		}
	}
	else
	{
		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();
		Pk = 2 * dx - dy;
		inc1 = 2 * (dx - dy);
		inc2 = 2 * dx;
		for (i = 0; i < dy; i++)
		{
			if (Pk >= 0)
			{
				x += incx;
				Pk += inc1;
			}
			else
				Pk += inc2;
			y += incy;
			glBegin(GL_POINTS);
			glVertex2i(x, y);
			glEnd();
		}
	}
}

void mcd(int h, int k, int r)
{

	int a = 0, b = r;
	int pk = 1 - r;
	while (a <= b)
	{
		glBegin(GL_POINTS);
		glVertex2d(a + h, b + k);	// 2
		glVertex2d(b + h, a + k);	//1
		glVertex2d(-a + h, b + k);	// 3
		glVertex2d(-b + h, a + k);	// 4
		glVertex2d(-b + h, -a + k); //5
		glVertex2d(-a + h, -b + k); //6
		glVertex2d(a + h, -b + k);	// 7
		glVertex2d(b + h, -a + k);	// 8
		glEnd();

		if (pk < 0)
		{
			b = b;
			pk = pk + 2 * a + 1;
		}
		else
		{
			pk = pk + 2 * a + 5 - 2 * b;
			b = b - 1;
		}
		a++;
	}
}

void car()
{
	glClear(GL_COLOR_BUFFER_BIT); // Clear the screen buffer

	glPointSize(3.0);

	// Rectangular part
	glColor3f(1.0f, 0.298f, 0.16f);

	bld(60, 80, 340, 80);
	bld(340, 80, 340, 180);
	bld(340, 180, 60, 180);
	bld(60, 180, 60, 80);

	for (int i = 60; i < 340; i++)
		bld(i, 80, i, 180);

	//big trapezium
	glColor3f(1.0f, 0.298f, 0.16f);

	bld(120, 180, 170, 280);
	bld(170, 280, 300, 280);
	bld(300, 280, 340, 180);
	bld(340, 180, 120, 180);

	for (int i = 170; i < 300; i++)
		bld(i, 180, i, 280);

	for (int i = 180; i < 280; i++)
		bld(120, 180, 170, i);

	for (int i = 180; i < 280; i++)
		bld(340, 180, 300, i);

	//small left trapezium
	glColor3f(0.2f, 0.278f, 0.337f);

	bld(125, 180, 173, 275);
	bld(173, 275, 230, 275);
	bld(230, 275, 230, 180);
	bld(230, 180, 125, 180);

	for (int i = 173; i < 230; i++)
		bld(i, 180, i, 275);

	for (int i = 180; i < 275; i++)
		bld(125, 180, 173, i);

	// small right trapezium
	glColor3f(0.2f, 0.278f, 0.337f);

	bld(240, 180, 240, 275);
	bld(240, 275, 297, 275);
	bld(297, 275, 335, 180);
	bld(335, 180, 240, 180);

	for (int i = 240; i < 297; i++)
		bld(i, 180, i, 275);

	for (int i = 180; i < 275; i++)
		bld(335, 180, 297, i);

	//1st tyre
	glColor3f(0.03137f, 0.12549f, 0.196f);
	int center_x = 130, center_y = 80, radius = 33;
	for (int i = 0; i <= radius; i++)
		mcd(center_x, center_y, i);

	//2nd tyre
	glColor3f(0.03137f, 0.12549f, 0.196f);
	int center_x1 = 280, center_y1 = 80, radius1 = 33;
	for (int i = 0; i <= radius1; i++)
		mcd(center_x1, center_y1, i);

	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1200) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 740) / 2);
	glutInitWindowSize(1200, 740);
	glutCreateWindow("Car");
	glutDisplayFunc(car);
	myInit();
	glutMainLoop();
	return 0;
}
