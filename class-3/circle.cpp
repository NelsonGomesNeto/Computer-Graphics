#if _WIN32
  #ifndef _WIN32
    #include <windows.h>
  #endif
#endif
#include <stdio.h>
#include <GL/freeglut.h>
#include <algorithm>
using namespace std;
const int width = 800, height = 800;
int radious = 5;
struct Point { int x, y; };
Point start = {width / 2, height / 2}, speed = {1, 2};

void keyboardHandler(unsigned char key, int x, int y)
{
  switch (key)
  {
    case '+': radious ++; break;
    case '-': radious --; break;
    default:
      break;
  }
  glutPostRedisplay();
}

void circlePoints(int x, int y)
{
  glVertex2d(x, y);
  glVertex2d(x, -y);
  glVertex2d(-x, y);
  glVertex2d(-x, -y);
  glVertex2d(y, x);
  glVertex2d(y, -x);
  glVertex2d(-y, x);
  glVertex2d(-y, -x);
}
void midPointCircle()
{
  int x, y;
  double d;
  x = start.x * 0 + 0, y = start.y * 0 + radious;
  d = (double) 5 / 4 - radious;

  circlePoints(x, y);
  while (y > x)
  {
    if (d < 0) d += 2 * x + 3, x ++;
    else d += 2 * (x - y) + 5, x ++, y --;
    circlePoints(x, y);
  }
}

void drawCircle()
{
  // glPushMatrix();
  glTranslated(start.x, start.y, 0);
  glBegin(GL_POINTS);
    midPointCircle();
  glEnd();
  glTranslated(-start.x, -start.y, 0);
  // glPopMatrix();
}

void scheduleUpdate(int value)
{
  glutTimerFunc(10, scheduleUpdate, 1);
  start.x += speed.x, start.y += speed.y;
  if (start.x < 0 || start.x > width) speed.x *= -1;
  if (start.y < 0 || start.y > height) speed.y *= -1;
  glutPostRedisplay();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3ub(0, 0, 255);
  for (int i = 0; i < 10000; i ++) drawCircle();

  glutSwapBuffers();
}

void init()
{
  gluOrtho2D(0, width, 0, height);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(400, 100);
    glutCreateWindow("Circle");
    init();
  glutDisplayFunc(display);
  glutTimerFunc(10, scheduleUpdate, 1);
  glutKeyboardFunc(keyboardHandler);
  glutMainLoop();
}