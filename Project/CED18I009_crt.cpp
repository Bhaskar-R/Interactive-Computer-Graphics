#include <bits/stdc++.h>
#include <GL/freeglut.h>
using namespace std;
#define PI 3.14159

float x_position = 107.0, x1_position = 237.0, y_position = 270.0, x, y, w, h;

void myInit()
{
	glClearColor(0.9, 0.9, 0.9, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	gluOrtho2D(0, 450, 0, 500);
}

void ParametricEllipse(int cx, int cy, int a, int b, int rr, int rg, int rb)
{
	glBegin(GL_POINTS);
	glColor3ub(rr, rg, rb);
	for (float i = 0; i <= 360; i += 0.2)
	{
		GLfloat theta = i * PI / 180;
		glVertex2f(cx + a * cos(theta), cy + b * sin(theta));
	}
	glEnd();
}

void MidpointEllipse(int cx, int cy, int a, int b, int rr, int rg, int rb)
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

void display()
{
	glPointSize(2);

	//Fluorescent screen
	ParametricEllipse(370, 270, 40, 130, 256, 256, 256);

	glLineWidth(2);
	//outer body
	glBegin(GL_LINES);
	glVertex2d(70, 320);
	glVertex2d(240, 320);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(70, 220);
	glVertex2d(240, 220);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(70, 210);
	glVertex2d(70, 330);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(240, 320);
	glVertex2d(370, 400);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(240, 220);
	glVertex2d(370, 140);
	glEnd();

	// Connector
	glBegin(GL_LINES);
	glVertex2d(45, 210);
	glVertex2d(45, 330);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(45, 210);
	glVertex2d(70, 210);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(45, 330);
	glVertex2d(70, 330);
	glEnd();

	for (int i = 45; i < 70; i++)
	{
		glBegin(GL_LINES);
		glVertex2d(i, 210);
		glVertex2d(i, 330);
		glEnd();
	}
	// for (int i = 210; i < 330; i++)
	// {
	// 	glBegin(GL_LINES);
	// 	glVertex2d(45, i);
	// 	glVertex2d(70, i);
	// 	glEnd();
	// }

	//connector pins
	//pin-1
	glColor3b(43, 43, 43);
	glBegin(GL_POLYGON);
	glVertex2d(35, 225);
	glVertex2d(45, 225);
	glVertex2d(45, 230);
	glVertex2d(35, 230);
	glEnd();

	//pin-2
	glBegin(GL_POLYGON);
	glVertex2d(35, 245);
	glVertex2d(45, 245);
	glVertex2d(45, 250);
	glVertex2d(35, 250);
	glEnd();

	//pin-3
	glBegin(GL_POLYGON);
	glVertex2d(35, 267);
	glVertex2d(45, 267);
	glVertex2d(45, 272);
	glVertex2d(35, 272);
	glEnd();

	//pin-4
	glBegin(GL_POLYGON);
	glVertex2d(35, 290);
	glVertex2d(45, 290);
	glVertex2d(45, 295);
	glVertex2d(35, 295);
	glEnd();

	//pin-5
	glBegin(GL_POLYGON);
	glVertex2d(35, 310);
	glVertex2d(45, 310);
	glVertex2d(45, 315);
	glVertex2d(35, 315);
	glEnd();

	//Filament
	glBegin(GL_LINES);
	glVertex2d(70, 292);
	glVertex2d(115, 292);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(70, 248);
	glVertex2d(115, 248);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(115, 248);
	glVertex2d(115, 267);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(115, 272);
	glVertex2d(115, 292);
	glEnd();

	//centre filament rod
	glBegin(GL_LINES);
	glVertex2d(70, 272);
	glVertex2d(95, 272);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(70, 267);
	glVertex2d(95, 267);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2d(95, 267);
	glVertex2d(108, 267);
	glVertex2d(108, 272);
	glVertex2d(95, 272);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(109, 265);
	glVertex2d(109, 274);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(107, 265);
	glVertex2d(109, 265);
	glEnd();
	glBegin(GL_LINES);
	glVertex2d(107, 274);
	glVertex2d(109, 274);
	glEnd();

	//Focusing Anodes
	glBegin(GL_LINES);
	glVertex2d(120, 248);
	glVertex2d(120, 267);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(120, 272);
	glVertex2d(120, 292);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(120, 248);
	glVertex2d(180, 248);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(120, 292);
	glVertex2d(180, 292);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(130, 248);
	glVertex2d(130, 265);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(130, 274);
	glVertex2d(130, 292);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(140, 248);
	glVertex2d(140, 265);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(140, 274);
	glVertex2d(140, 292);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(150, 248);
	glVertex2d(150, 265);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(150, 274);
	glVertex2d(150, 292);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(160, 248);
	glVertex2d(160, 265);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(160, 274);
	glVertex2d(160, 292);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(170, 248);
	glVertex2d(170, 265);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(170, 274);
	glVertex2d(170, 292);
	glEnd();

	// last layer of focusing anodes
	glBegin(GL_LINES);
	glVertex2d(185, 244);
	glVertex2d(185, 265);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(185, 274);
	glVertex2d(185, 296);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(175, 244);
	glVertex2d(184, 244);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(175, 296);
	glVertex2d(184, 296);
	glEnd();

	// horizontal deflecting plates
	//top plate
	glBegin(GL_POLYGON);
	glVertex2d(190, 280);
	glVertex2d(205, 280);
	glVertex2d(215, 289);
	glVertex2d(200, 289);
	glEnd();

	//top magnet
	glBegin(GL_LINES);
	glVertex2d(202, 281);
	glVertex2d(202, 350);
	glEnd();
	glBegin(GL_LINES);
	glVertex2d(203, 281);
	glVertex2d(203, 350);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(200, 350);
	glVertex2d(205, 350);
	glVertex2d(205, 358);
	glVertex2d(200, 358);
	glEnd();

	//bottom plate
	glBegin(GL_POLYGON);
	glVertex2d(190, 250);
	glVertex2d(205, 250);
	glVertex2d(215, 259);
	glVertex2d(200, 259);
	glEnd();

	//bottom magnet
	glBegin(GL_LINES);
	glVertex2d(202, 249);
	glVertex2d(202, 193);
	glEnd();
	glBegin(GL_LINES);
	glVertex2d(203, 249);
	glVertex2d(203, 193);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(200, 185);
	glVertex2d(205, 185);
	glVertex2d(205, 193);
	glVertex2d(200, 193);
	glEnd();

	//vertical deflecting plates
	glColor3b(60, 60, 60);
	glBegin(GL_POLYGON);
	glVertex2d(230, 261);
	glVertex2d(245, 261);
	glVertex2d(245, 285);
	glVertex2d(230, 285);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2d(220, 258);
	glVertex2d(235, 258);
	glVertex2d(235, 282);
	glVertex2d(220, 282);
	glEnd();

	//Electrons beam from filament to deflecting plates
	glColor3f(0, 0, 1);
	glBegin(GL_POLYGON);
	glVertex2f(x_position, 270);
	glVertex2f(x_position, 269);
	glVertex2f(x_position + 2, 269);
	glVertex2f(x_position + 2, 270);
	glEnd();

	//Electrons beam from deflecting plates to point on the screen
	glBegin(GL_POLYGON);
	glVertex2f(x1_position, y_position);
	glVertex2f(x1_position, y_position - 1);
	glVertex2f(x1_position + 2, y_position - 1);
	glVertex2f(x1_position + 2, y_position);
	glEnd();

	glFlush();
}

void timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0); //1000/60 -> indicates that we are displaying 60 frames per second
	if (x_position < 237)
		x_position += 1;

	//when above the horizontal line
	if (y >= 270)
	{
		if (w > h)
		{
			if (x1_position < x and x_position == 237 and y_position < y and h != 0)
				x1_position += w / h;
			if (y_position < y and x_position == 237 and x1_position < x)
				y_position += 1;
		}
		else
		{
			if (x1_position < x and x_position == 237 and y_position < y)
				x1_position += 1;
			if (y_position < y and x_position == 237 and x1_position < x and w != 0)
				y_position += h / w;
		}
	}
	else
	{
		if (w > h)
		{
			if (x1_position < x and x_position == 237 and y_position > y and h != 0)
				x1_position += w / h;
			if (y_position > y and x_position == 237 and x1_position < x)
				y_position -= 1;
		}
		else
		{
			if (x1_position < x and x_position == 237 and y_position > y)
				x1_position += 1;
			if (y_position > y and x_position == 237 and x1_position < x and w != 0)
				y_position -= h / w;
		}
	}
	// when the point is on the horizontal line
	if (h == 0)
		if (x1_position < x and x_position == 237)
			x1_position += 1;
}

void welcomeScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(3);
	glColor3f(0, 0, 0);
	glRasterPos3f(189, 330, 0);
	string s = "Simulation of Cathode Ray Tube";
	for (auto i : s)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, i);

	glColor3f(0, 0, 0);
	glRasterPos3f(225, 290, 0);
	s = "by";
	for (auto i : s)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, i);

	glColor3f(0, 0, 0);
	glRasterPos3f(215, 260, 0);
	s = "Bhaskar R";
	for (auto i : s)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, i);

	glColor3f(0, 0, 0);
	glRasterPos3f(214, 235, 0);
	s = "CED18I009";
	for (auto i : s)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, i);

	glFlush();
}

int checkinside(int x, int y)
{
	float val = (((x - 370) * (x - 370)) / 1600.0) + (((y - 270) * (y - 270)) / 16900.0) - 1;
	if (val < 0.0)
		return 0;
	else
		return 1;
}

int check_x(int x)
{
	while (x <= 330 or x >= 410)
	{
		cout << "\nEnter a Valid X" << endl;
		cout << "[330 < x < 410]   X = ";
		cin >> x;
	}
	return x;
}

int check_y(int y)
{
	while (y <= 140 or y >= 400)
	{
		cout << "\nEnter a Valid Y" << endl;
		cout << "[140 < y < 400]   Y = ";
		cin >> y;
	}
	return y;
}

void click(int button, int state, int click_x, int click_y)
{
	x = (click_x / 1920.0) * 450.0;
	y = ((1020.0 - click_y) / 1020.0) * 500.0;
	w = x - 237;
	h = y >= 270 ? y - 270 : 270 - y;
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(display);
	glutPostRedisplay();
	glutTimerFunc(0, timer, 0);
}

void mytimer(int)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(display);
	glutPostRedisplay();
	glutTimerFunc(0, timer, 0);
}

int main(int argc, char **argv)
{
	srand(time(0));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
	cout << "\nPixel to be lit on CRT Screen" << endl;
	cout << "[330 < x < 410]   X = ";
	cin >> x;
	x = check_x(x);
	cout << "[140 < y < 400]   Y = ";
	cin >> y;
	y = check_y(y);
	while (checkinside(x, y)) // Checking whether the point is inside the screen or not
	{
		cout << "\nEntered Point is outside the Screen\n";
		cout << "[330 < x < 410]   X = ";
		cin >> x;
		x = check_x(x);
		cout << "[140 < y < 400]   Y = ";
		cin >> y;
		y = check_y(y);
	}
	w = x - 237;
	h = y >= 270 ? y - 270 : 270 - y;
	glutCreateWindow("Simulation of Cathode Ray Tube");
	glutDisplayFunc(welcomeScreen);
	glutTimerFunc(3100, mytimer, 0);
	myInit();
	glutMainLoop();
	return 0;
}