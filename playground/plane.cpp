#ifndef _WIN32
  #if _WIN32
    #include <windows.h>
  #endif
#endif
#include <string>
using namespace std;
#include <math.h>
#include <GL/freeglut.h>
struct Point
{
  double x, y;
  string to_string() { return("(" + std::to_string(x) + ", " + std::to_string(y) + ")"); }
};
Point mouse = {0, 0};
const int width = 800, height = 800, dx[4] = {0, 1, 1, 0}, dy[4] = {0, 0, 1, 1};
int plane = 0, planeScale = 20;
const double pi = acos(-1);
double degToRad(double a) { return(a*pi/180.0); }

void printText(string s, double x, double y)
{
  glRasterPos2d(x, y);
  for (int i = 0; i < s.size(); i++) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
  glRasterPos2d(-x, -y);
}

void scheduleUpdate(int v)
{
  glutTimerFunc(10, scheduleUpdate, 1);
  glLoadIdentity();
  gluOrtho2D(width * (1 - dx[plane]), width * dx[plane], height * (1 - dy[plane]), height * dy[plane]);
  glutPostRedisplay();
}

void keyboardHandler(unsigned char key, int x, int y)
{
  if (key >= '1' && key <= '4') plane = key - '1';
}

void passiveMotionHandler(int x, int y)
{
  mouse.x = dx[plane] * x + (1 - dx[plane]) * (width - x), mouse.y = dy[plane] * (height - y) + (1 - dy[plane]) * y;
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT); glClearColor(1, 1, 1, 1);

  glColor3ub(0, 0, 0);
  for (int i = 0; i < width; i += planeScale)
  {
    glBegin(GL_LINES);
      glVertex2d(0, i);
      glVertex2d(width, i);
    glEnd();
  }
  for (int j = 0; j < height; j += planeScale)
  {
    glBegin(GL_LINES);
      glVertex2d(j, 0);
      glVertex2d(j, height);
    glEnd();
  }

  printText(mouse.to_string(), mouse.x, mouse.y);

  glColor3ub(255, 0, 0);
  glBegin(GL_TRIANGLE_FAN);
    glVertex2d(-10, -10);
    glVertex2d(-10, 10);
    glVertex2d(10, 10);
    glVertex2d(10, -10);
  glEnd();
  glLineWidth(1);

  glFlush();
}

void init()
{
  gluOrtho2D(width * (1 - dx[plane]), width * dx[plane], height * (1 - dy[plane]), height * dy[plane]);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(800, 100);
    glutCreateWindow("Plane");
    init();

  glutDisplayFunc(display);
  glutTimerFunc(10, scheduleUpdate, 1);
  glutKeyboardFunc(keyboardHandler);
  glutPassiveMotionFunc(passiveMotionHandler);

  glutMainLoop();
}