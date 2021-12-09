#include <GL/glew.h>
#include <GL/freeglut.h>
#include <bits/stdc++.h>
using namespace std;

float mse_dda = 0, mse_bld = 0, cnt1 = 1, cnt2 = 1;
void myInit()
{
	glClearColor(0.9, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 800.0, 0.0, 800.0); // Specify the display area
}

void bld(int x1, int y1, int x2, int y2)
{
	glPointSize(3);
	int dx, dy, i, Pk, x, y;
	int incx, incy, inc1, inc2;
	int bldx = 0, bldy = 0;
	dx = abs(x2 - x1);
	dy = abs(y2 - y1);

	incx = (x2 < x1) ? -1 : 1;
	incy = (y2 < y1) ? -1 : 1;
	x = x1;
	y = y1;

	double bfx = x1, bfy = y1;
	double c;
	if (x1 == x2)
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
			bldx += x;
			bldy += y;
			glVertex2i(x, y);
			bfy += 1;
			mse_bld += (pow((x - bfx), 2)) + (pow((y - bfy), 2));
			cnt1 += dy;
			glEnd();
		}
	}
	else
	{
		double slope = (y2 - y1) / (x2 - x1);
		c = y1 - slope * x1;

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
				bldx += x;
				bldy += y;
				glVertex2i(x, y);
				bfx += 1;
				bfy += slope * bfx + c;
				cnt1 += dx;
				mse_bld += (pow((x - bfx), 2)) + (pow((y - bfy), 2));
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
				bldx += x;
				bldy += y;
				glVertex2i(x, y);
				bfy += 1;
				bfx += (bfy - c) / slope;
				mse_bld += (pow((x - bfx), 2)) + (pow((y - bfy), 2));
				cnt1 += dy;
				glEnd();
			}
		}
	}
	// dda algo
	bfx = x1, bfy = y1;
	float ddax = 0, dday = 0;
	if (x2 == x1)
	{
		if (y1 < y2)
		{
			for (int i = y1; i <= y2; i++)
			{
				ddax = x1;
				dday = i;
				bfy += 1;
				mse_dda += (pow((ddax - bfx), 2)) + (pow((dday - bfy), 2));
				cnt2 += dy;
			}
		}
		else
		{
			for (int i = y1; i >= y2; i--)
			{
				ddax = x1;
				dday = i;
				bfy += 1;
				mse_dda += (pow((ddax - bfx), 2)) + (pow((dday - bfy), 2));
				cnt2 += dy;
			}
		}
	}
	else
	{
		double slope = (y2 - y1) / (x2 - x1);
		double absslope = (slope >= 0) ? (slope) : (-1.0 * slope);
		if (absslope <= 1.0)
		{
			if (x1 < x2)
			{
				for (int i = x1; i <= x2; i++)
				{
					ddax = i;
					dday = y1;
					y1 = y1 + slope;
					bfx += 1;
					bfy += slope * bfx + c;
					mse_dda += (pow((ddax - bfx), 2)) + (pow((dday - bfy), 2));
					cnt2 += dx;
				}
			}
			else
			{
				for (int i = x1; i >= x2; i--)
				{
					ddax = i;
					dday = y1;
					y1 = y1 - slope;
					bfx += 1;
					bfy += slope * bfx + c;
					mse_dda += (pow((ddax - bfx), 2)) + (pow((dday - bfy), 2));
					cnt2 += dx;
				}
			}
		}
		else
		{
			if (y1 < y2)
			{
				for (int i = y1; i <= y2; i++)
				{
					ddax = x1;
					dday = i;
					x1 = x1 + (1.0 / slope);
					bfy += 1;
					bfx += (bfy - c) / slope;
					mse_dda += (pow((ddax - bfx), 2)) + (pow((dday - bfy), 2));
					cnt2 += dy;
				}
			}
			else
			{
				for (int i = y1; i >= y2; i--)
				{
					ddax += x1;
					dday += i;
					x1 = x1 - (1.0 / slope);
					bfy += 1;
					bfx += (bfy - c) / slope;
					mse_dda += (pow((ddax - bfx), 2)) + (pow((dday - bfy), 2));
					cnt2 += dy;
				}
			}
		}
	}
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);
	//Center as (400,400) and radius as 150
	bld(475, 270, 325, 270);
	bld(325, 270, 250, 400);
	bld(250, 400, 325, 530);
	bld(325, 530, 475, 530);
	bld(475, 530, 550, 400);
	bld(550, 400, 475, 270);

	cout << "MSE - BLD : " << (mse_bld / (double)cnt1) * pow(10, -7) << endl;
	cout << "MSE - DDA : " << (mse_dda / (double)cnt2) * pow(10, -7) << endl;
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
