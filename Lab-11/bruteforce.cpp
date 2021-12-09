#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;
vector<pair<int, int>> v;

void myinit()
{
    glClearColor(0.9, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 1200, 0, 740);
}

void bound_it(int x, int y, float *fillColor, float *bc)
{
    float color[3];
    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, color);
    if ((color[0] != bc[0] || color[1] != bc[1] || color[2] != bc[2]) && (color[0] != fillColor[0] || color[1] != fillColor[1] || color[2] != fillColor[2]))
    {
        glColor3f(fillColor[0], fillColor[1], fillColor[2]);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();
        bound_it(x + 1, y, fillColor, bc);
        bound_it(x - 2, y, fillColor, bc);
        bound_it(x, y + 2, fillColor, bc);
        bound_it(x, y - 2, fillColor, bc);
    }
}

void mouse(int btn, int state, int x, int y)
{
    y = 740 - y;
    if (btn == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            float bCol[] = {1, 0, 0};
            float color[] = {0, 0, 1};
            bound_it(x, y, color, bCol);
        }
    }
}

void createpolygon()
{
    glLineWidth(3);
    glPointSize(2);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);

    int x, y;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < v.size(); i++)
    {
        x = v[i].first;
        y = v[i].second;
        glVertex2i(x, y);
    }
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1200) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 740) / 2);
    glutInitWindowSize(1200, 740);
    int x, y, n;
    printf("Enter No. of sides : ");
    cin >> n;
    printf("Enter the coordinates :\n");
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        cin >> y;
        v.push_back(make_pair(x, y));
    }
    glutCreateWindow("Bruteforce - Polygon Filling");
    glutDisplayFunc(createpolygon);
    glutMouseFunc(mouse);
    myinit();
    glutMainLoop();
    return 0;
}
