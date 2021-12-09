#include <GL/glut.h>
#include <bits/stdc++.h>

double mse_dda = 0, mse_bld = 0, cnt1 = 1, cnt2 = 1;

void myInit()
{
	glClearColor(0.9, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 600.0, 0.0, 700.0); // Specify the display area
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

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//body
	glColor3f(0, 0, 0);
	bld(100, 50, 100, 350);
	bld(100, 350, 500, 350);
	bld(500, 350, 500, 50);
	bld(500, 50, 100, 50);

	//coloring the body
	glColor3f(0.26, 0.75, 0.96);
	for (int i = 102; i <= 497; i++)
		bld(i, 52, i, 347);

	//roof
	glColor3f(0, 0, 0);
	bld(100, 350, 300, 600);
	bld(300, 600, 500, 350);
	bld(500, 350, 100, 350);

	//coloring the roof
	glColor3f(0.95, 0.35, 0.36);
	for (int i = 106; i <= 494; i++)
		bld(300, 595, i, 353);

	//door
	glColor3f(0, 0, 0);
	bld(255, 50, 255, 200);
	bld(255, 200, 345, 200);
	bld(345, 200, 345, 50);
	bld(345, 50, 255, 50);

	//coloring the door
	glColor3f(1, 1, 1);
	for (int i = 258; i <= 342; i++)
		bld(i, 53, i, 197);

	//left window
	glColor3f(0, 0, 0);
	bld(150, 150, 150, 200);
	bld(150, 200, 200, 200);
	bld(200, 200, 200, 150);
	bld(200, 150, 150, 150);

	//coloring the left window
	glColor3f(1, 1, 1);
	for (int i = 153; i <= 197; i++)
		bld(i, 153, i, 197);

	//right window
	glColor3f(0, 0, 0);
	bld(400, 150, 400, 200);
	bld(400, 200, 450, 200);
	bld(450, 200, 450, 150);
	bld(450, 150, 400, 150);

	//coloring the right window
	glColor3f(1, 1, 1);
	for (int i = 403; i <= 447; i++)
		bld(i, 153, i, 197);

	std::cout << "MSE - BLD : " << (mse_bld / (double)cnt1) * pow(10, -7) << std::endl;
	std::cout << "MSE - DDA : " << (mse_dda / (double)cnt1) * pow(10, -7) << std::endl;

	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 800) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 740) / 2);
	glutInitWindowSize(800, 740);
	glutCreateWindow("House");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
	return 0;
}