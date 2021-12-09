#include <GL/glew.h>
#include <GL/freeglut.h>
#include <bits/stdc++.h>

void draw(void)
{
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
	glColor3f(1, 1, 0);

	// Rectangle
	glRecti(150, 150, 490, 270);

	// Circle 1
	int center_x = 220, center_y = 320, radius = 50;
	glBegin(GL_POINTS);
	for (int i = 0; i < 360; i += 1)
		glVertex2i(center_x + (radius * cosf(i)), center_y + (radius * sinf(i)));
	glEnd();

	// Circle 2
	center_x = 420, center_y = 320, radius = 50;
	glBegin(GL_POINTS);
	for (int i = 0; i < 360; i += 1)
		glVertex2i(center_x + (radius * cosf(i)), center_y + (radius * sinf(i)));
	glEnd();

	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 640) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 480) / 2);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Shapes");
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(draw);
	glutMainLoop();

	return 0;
}
