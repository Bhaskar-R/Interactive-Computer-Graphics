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

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen buffer

    glPointSize(4.0);

    // Rectangular part
    glColor3f(1.0f, 0.298f, 0.16f);

    glBegin(GL_POLYGON);
    glVertex2i(60, 80);
    glVertex2i(340, 80);
    glVertex2i(340, 180);
    glVertex2i(60, 180);
    glEnd();

    //big trapezium
    glColor3f(1.0f, 0.298f, 0.16f);

    glBegin(GL_POLYGON);
    glVertex2i(120, 180);
    glVertex2i(170, 280);
    glVertex2i(300, 280);
    glVertex2i(340, 180);
    glEnd();

    //small left trapezium
    glColor3f(0.2f, 0.278f, 0.337f);

    glBegin(GL_POLYGON);
    glVertex2i(125, 180);
    glVertex2i(173, 275);
    glVertex2i(230, 275);
    glVertex2i(230, 180);
    glEnd();

    // small right trapezium
    glColor3f(0.2f, 0.278f, 0.337f);

    glBegin(GL_POLYGON);
    glVertex2i(240, 180);
    glVertex2i(240, 275);
    glVertex2i(297, 275);
    glVertex2i(335, 180);
    glEnd();

    //1st tyre
    glColor3f(0.03137f, 0.12549f, 0.196f);
    int center_x = 130, center_y = 80, radius = 33;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 1)
        glVertex2i(center_x + (radius * cosf(i)), center_y + (radius * sinf(i)));
    glEnd();

    //2nd tyre
    glColor3f(0.03137f, 0.12549f, 0.196f);
    int center_x1 = 280, center_y1 = 80, radius1 = 33;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 1)
        glVertex2i(center_x1 + (radius1 * cosf(i)), center_y1 + (radius1 * sinf(i)));
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1200) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 740) / 2);
    glutInitWindowSize(1200, 740);
    glutCreateWindow("Car");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
    return 0;
}
