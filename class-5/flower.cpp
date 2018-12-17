#ifndef _WIN32
  #if _WIN32
    #include <windows.h>
  #endif
#endif
#include <math.h>
#include "./../rainbow.h"
#include <GL/freeglut.h>
const double pi = acos(-1);
int max(int a, int b) { return(a > b ? a : b); }
double degToRad(double a) { return (a * pi / 180.0); }
const int width = 800, height = 800;
double zAngle = 0, diff = 0, petalSize = 200; bool rotating = false;
struct Point { int x, y; };
Point mouse;
int petalsAmount = 4;

void passiveMotionHandler(int x, int y)
{
  diff = (y - mouse.y) / 1.0 * 100;
}

void keyboardHandler(unsigned char key, int x, int y)
{
  switch (key)
  {
    case '1': if (!rotating) rotating = true, mouse.x = x, mouse.y = y, diff = 0; else rotating = false; break;
    case 'a': petalsAmount ++; break;
    case 'd': petalsAmount --; break;
    default: break;
  }
}

void scheduleUpdate(int v)
{
  glutTimerFunc(10, scheduleUpdate, 1);
  if (rotating) zAngle += diff;
  glutPostRedisplay();
}

void drawPetals()
{
  double spacing = 360.0 / petalsAmount;
  petalSize = 800.0 / petalsAmount;
  glPushMatrix();
    glTranslated(width / 2.0, height / 2.0, 0);
    glRotated(zAngle, 0, 0, 1);
    for (int i = 0, s = 0, ds = max(1, rainbowSize / petalsAmount); i < petalsAmount; i ++, s += ds)
    {
      glColor3dv(rainbowArray[s % rainbowSize]);
      glBegin(GL_TRIANGLES);
        glVertex2d(0, 0);
        glVertex2d(-petalSize / 2.0, -200);
        glVertex2d(petalSize / 2.0, -200);
      glEnd();
      glRotated(spacing, 0, 0, 1);
    }
  glPopMatrix();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3ub(0, 94, 0);
  glRectd(4 * width / 10.0, 0, 6 * width / 10.0, height / 2.0); // body
  drawPetals();

  glFlush();
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
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Input");
    init();
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboardHandler);
  glutPassiveMotionFunc(passiveMotionHandler);
  glutTimerFunc(10, scheduleUpdate, 1);
  glutMainLoop();
}
