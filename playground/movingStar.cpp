#ifndef _WIN32
  #include <windows.h>
#endif
#include <vector>
using namespace std;
#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>
const int width = 400, height = 400, inf = 1<<20;
const double pi = acos(-1);
double degToRad(double a) { return(a*pi/180.0); }
struct Point { double x, y; };
Point position = {200, 200}; double angle, dx = 5, dy = 9;

void fpsControl(int v)
{
  glutTimerFunc(10, fpsControl, 1);
  glutPostRedisplay();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glLineWidth(50);
  glBegin(GL_LINES);
    glColor3ub(0, 0, 120);
    Point sum = {0, 0}, p = {0, 0}, center, minp = {inf, inf}, maxp = {-inf, -inf};
    vector<Point> star;
    double size = 200, a = angle, da = degToRad(144);
    for (int i = 0; i < 5; i ++)
    {
      star.push_back(p);
      p.x += size * cos(a), p.y += size * sin(a);
      star.push_back(p);
      sum.x += p.x, sum.y += p.y;
      a += da;
    } sum.x /= 5.0, sum.y /= 5.0;
    center.x = sum.x + position.x, center.y += sum.y + position.y;
    for (Point s: star)
    {
      glVertex2d(center.x - s.x, center.y - s.y);
      if (center.x - s.x < minp.x) minp.x = center.x - s.x;
      else if (center.x - s.x > maxp.x) maxp.x = center.x - s.x;
      if (center.y - s.y < minp.y) minp.y = center.y - s.y;
      else if (center.y - s.y > maxp.y) maxp.y = center.y - s.y;
    }

    position.x += dx, position.y += dy;
    if (position.x <= 0 + size / 2.0 || position.x >= width - size / 2.0) dx *= -1;
    if (position.y <= 0 + size / 2.0 || position.y >= height - size / 2.0) dy *= -1;
    angle += degToRad(1);
    if (angle >= degToRad(360)) angle = 0;
  glEnd();

  glFlush();
}

void init()
{
  glClearColor(1, 1, 1, 0);
  gluOrtho2D(0, width, 0, height);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Hello World");
    init();

  glutDisplayFunc(display);
  glutTimerFunc(10, fpsControl, 1);
  glutMainLoop();

  return (0);
}