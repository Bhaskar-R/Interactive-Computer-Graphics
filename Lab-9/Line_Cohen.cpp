#include <bits/stdc++.h>
#include <GL/freeglut.h>
#include <GL/glut.h>

void myInit()
{
    glClearColor(0.9, 0.9, 0.9, 0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Cohen(int x1, int y1, int x2, int y2, int xmin, int xmax, int ymin, int ymax)
{
    //Region codes
    int b1 = (y1 - ymax) > 0;
    int b2 = (ymin - y1) > 0;
    int b3 = (x1 - xmax) > 0;
    int b4 = (xmin - x1) > 0;
    int bp1 = (y2 - ymax) > 0;
    int bp2 = (ymin - y2) > 0;
    int bp3 = (x2 - xmax) > 0;
    int bp4 = (xmin - x2) > 0;

    // case1
    if (!(b1 | b2 | b3 | b4 | bp1 | bp2 | bp3 | bp4))
    {
        // draw line;
        glColor3f(1, 0, 0);
        glBegin(GL_LINES);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
        glEnd();
    }
    else if ((b1 & bp1) || (b2 & bp2) || (b3 & bp3) || (b4 && bp4))
    {
        // reject lines drawn in blue
        glColor3f(0, 0, 1);
        glBegin(GL_LINES);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
        glEnd();
    }
    else
    {
        // clip them
        int delX = x2 - x1;
        int delY = y2 - y1;
        while (b1 | b2 | b3 | b4 | bp1 | bp2 | bp3 | bp4)
        {

            if (b1 == 1)
            {
                // intersect y = ymax
                x1 = x1 + delX * (ymax - y1) / delY;
                y1 = ymax;
            }
            else if (b2 == 1)
            {
                // intersect y = ymin
                x1 = x1 + delX * (ymin - y1) / delY;
                y1 = ymin;
            }
            else if (b3 == 1)
            {
                // intersect x = xmax
                x1 = xmax;
                y1 = y1 + delY * (xmax - x1) / delX;
            }
            else if (b4 == 1)
            {
                // intersect x = xmin
                x1 = xmin;
                y1 = y1 + delY * (xmin - x1) / delX;
            }

            if (bp1 == 1)
            {
                // intersect y = ymax
                x2 = x2 + delX * (ymax - y2) / delY;
                y2 = ymax;
            }
            else if (bp2 == 1)
            {
                // intersect y = ymin
                x2 = x2 + delX * (ymin - y2) / delY;
                y2 = ymin;
            }
            else if (bp3 == 1)
            {
                // intersect x = xmax
                x2 = xmax;
                y2 = y2 + delY * (xmax - x2) / delX;
            }
            else if (bp4 == 1)
            {
                // intersect x = xmin
                x2 = xmin;
                y2 = y2 + delY * (xmin - x2) / delX;
            }

            b1 = (y1 - ymax) > 0;
            b2 = (ymin - y1) > 0;
            b3 = (x1 - xmax) > 0;
            b4 = (xmin - x1) > 0;
            bp1 = (y2 - ymax) > 0;
            bp2 = (ymin - y2) > 0;
            bp3 = (x2 - xmax) > 0;
            bp4 = (xmin - x2) > 0;

            if ((b1 & bp1) || (b2 & bp2) || (b3 & bp3) || (b4 && bp4))
            {
                // reject
                glColor3f(0, 0, 1);
                glBegin(GL_LINES);
                glVertex2d(x1, y1);
                glVertex2d(x2, y2);
                glEnd();
                return;
            }
        }

        // draw line;
        glColor3f(0, 1, 0);
        glBegin(GL_LINES);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
        glEnd();
    }
}

void render()
{
    gluOrtho2D(0, 500, 0, 500);
    glPointSize(3);
    int xmin, xmax, ymin, ymax;
    ymin = 50 + rand() % 20;
    xmin = 70 + rand() % 20;
    xmax = xmin + 200 + rand() % 100;
    ymax = ymin + 200 + rand() % 100;

    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    glVertex2d(xmin, ymin);
    glVertex2d(xmax, ymin);
    glVertex2d(xmax, ymax);
    glVertex2d(xmin, ymax);
    glEnd();

    glColor3f(1, 0, 0);
    for (int i = 0; i < 45; i++)
    {
        int x1 = rand() % 500;
        int y1 = rand() % 500;
        int x2 = rand() % 500;
        int y2 = rand() % 500;
        Cohen(x1, y1, x2, y2, xmin, xmax, ymin, ymax);
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
    glutCreateWindow("Line Clippping Cohen_Sutherland");
    glutDisplayFunc(render);
    myInit();
    glutMainLoop();
    return 0;
}