#include <bits/stdc++.h>
#include <GL/freeglut.h>
#include <GL/glut.h>

void myInit()
{
    glClearColor(0.9, 0.9, 0.9, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, 450, 0, 500);
}

void DrawPoint(int x, int y, int xmin, int xmax, int ymin, int ymax)
{
    if (x >= xmin && x <= xmax && y >= ymin && y <= ymax)
    {
        glColor3f(1, 0, 0);
        glBegin(GL_POINTS);
        glVertex2d(x, y);
        glEnd();
    }
    else
    {
        glColor3f(0, 0, 1);
        glBegin(GL_POINTS);
        glVertex2d(x, y);
        glEnd();
    }
}

void pointclipping()
{
    glPointSize(3);
    int xmin, xmax, ymin, ymax;
    ymin = 20 + rand() % 100;
    xmin = 20 + rand() % 100;
    xmax = xmin + 250 + rand() % 100;
    ymax = ymin + 250 + rand() % 100;

    glBegin(GL_POLYGON);
    glVertex2d(xmin, ymin);
    glVertex2d(xmax, ymin);
    glVertex2d(xmax, ymax);
    glVertex2d(xmin, ymax);
    glEnd();

    for (int i = 0; i < 100; i++)
    {
        int x = rand() % 500;
        int y = rand() % 500;
        DrawPoint(x, y, xmin, xmax, ymin, ymax);
    }
    glFlush();
}

int main(int argc, char **argv)
{
    srand(time(0));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1200) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 740) / 2);
    glutInitWindowSize(1200, 740);
    glutCreateWindow("Point Clippping");
    glutDisplayFunc(pointclipping);
    myInit();
    glutMainLoop();
    return 0;
}