#include <GL/glew.h>
#include <GL/freeglut.h>
#include <bits/stdc++.h>

void myInit()
{
    glClearColor(0.9, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 400.0, 0.0, 400.0);
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(4.0);

    // Rectangular part of house
    glColor3f(0.4862f, 0.513f, 1.0f);

    glBegin(GL_POLYGON);
    glVertex2i(110, 60);
    glVertex2i(290, 60);
    glVertex2i(290, 260);
    glVertex2i(110, 260);
    glEnd();

    //left window
    glColor3f(0.4901f, 0.9294f, 1.0f);

    glBegin(GL_POLYGON);
    glVertex2i(133, 100);
    glVertex2i(158, 100);
    glVertex2i(158, 140);
    glVertex2i(133, 140);
    glEnd();

    //right window
    glColor3f(0.4901f, 0.9294f, 1.0f);

    glBegin(GL_POLYGON);
    glVertex2i(243, 100);
    glVertex2i(243, 140);
    glVertex2i(268, 140);
    glVertex2i(268, 100);
    glEnd();

    //door
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_POLYGON);
    glVertex2i(180, 60);
    glVertex2i(180, 140);
    glVertex2i(220, 140);
    glVertex2i(220, 60);
    glEnd();

    // House's top triangle part
    glColor3f(0.2431f, 0.1725f, 0.2549f);
    glBegin(GL_TRIANGLES);
    glVertex2i(110, 260);
    glVertex2i(290, 260);
    glVertex2i(200, 390);
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1200) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 740) / 2);
    glutInitWindowSize(1200, 740);
    glutCreateWindow("House");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
    return 0;
}
