#include <bits/stdc++.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
using namespace std;
vector<pair<int, int>> vertex;

void myInit()
{
	glClearColor(0.9, 0.9, 0.9, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glOrtho(0, 1000, 0, 1000, -1, 1);
}

void Point()
{
	srand(time(0));
	glBegin(GL_LINES);
	glPointSize(3);
	glColor3f(0, 0, 0);
	for (int i = 1; i < vertex.size(); i++)
	{
		glVertex2i(vertex[i - 1].first, vertex[i - 1].second);
		glVertex2i(vertex[i].first, vertex[i].second);
	}
	glVertex2i(vertex[0].first, vertex[0].second);
	glVertex2i(vertex[vertex.size() - 1].first, vertex[vertex.size() - 1].second);
	glEnd();
	int num = rand() % 50 + 50;
	glPointSize(3.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < num; i++)
	{
		int x = rand() % 1000;
		int y = rand() % 1000;
		int flag = 0;
		for (int i = 1; i < vertex.size(); i++)
		{
			int temp = (vertex[i].first - vertex[(i - 1)].first) * (y - vertex[(i - 1)].second) - (vertex[i].second - vertex[(i - 1)].second) * (x - vertex[(i - 1)].first);
			if (temp < 0)
			{
				flag = 1;
				break;
			}
		}
		int mark = (vertex[0].first - (vertex[vertex.size() - 1]).first) * (y - (vertex[vertex.size() - 1]).second) - (vertex[0].second - (vertex[vertex.size() - 1]).second) * (x - (vertex[vertex.size() - 1]).first);
		if (mark < 0)
			flag = 1;
		if (flag)
			glColor3f(0, 0, 1);
		else
			glColor3f(1, 0, 0);
		glVertex2i(x, y);
	}
	glEnd();
	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1200) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 740) / 2);
	glutInitWindowSize(1200, 740);
	cout << "Enter number of vertices in polygon" << endl;
	int n;
	cin >> n;
	cout << "Enter the vertices in sequential order" << endl;
	for (int i = 0; i < n; i++)
	{
		int x, y;
		cin >> x >> y;
		vertex.push_back(make_pair(x, y));
	}
	glutCreateWindow("Point");
	glutDisplayFunc(Point);
	myInit();
	glutMainLoop();
	return 0;
}
