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
struct Point { double x, y; };
struct Line { Point pi, pf; };
Line line;

void readLine()
{
  FILE *file = fopen("class-3/in", "r");
  fscanf(file, "%lf %lf %lf %lf", &line.pi.x, &line.pi.y, &line.pf.x, &line.pf.y);
  fclose(file);
}

void keyboardHandler(unsigned char key, int x, int y)
{
  switch (key)
  {
    case 'r': line.pf.x = x, line.pf.y = height - y; break;
    case 'a': readLine(); break;
    default:
      break;
  }
  glutPostRedisplay();
}

void simpleLineAlgorithm()
{
  double a = (line.pf.y - line.pi.y) / (line.pf.x - line.pi.x);
  for (double x = line.pi.x; x <= line.pf.x; x ++) glVertex2d(x, (line.pi.y + a * (x - line.pi.x)));
}

void bresenham()
{
  Line aux = line;
  // line.pi.x += 400, line.pf.x += 400;
  // If the line is steeper, we better swap x by y and continue drawing going up
  bool steep = abs(line.pf.y - line.pi.y) > abs(line.pf.x - line.pi.x);
  if (steep) swap(line.pi.x, line.pi.y), swap(line.pf.x, line.pf.y);
  if (line.pi.x > line.pf.x) swap(line.pi.x, line.pf.x), swap(line.pi.y, line.pf.y);
  printf("(%3.3lf, %3.3lf) -> (%3.3lf, %3.3lf)\n", line.pi.x, line.pi.y, line.pf.x, line.pf.y);

  int dx, dy, E, NE, d, x, y, yStep = line.pi.y > line.pf.y ? -1 : 1;
  dx = line.pf.x - line.pi.x, dy = line.pf.y - line.pi.y;
  d = 2 * dy - dx;
  E = 2 * dy, NE = 2 * (dy - dx);
  x = line.pi.x, y = line.pi.y;
  glRectd(x - 0.5, y - 0.5, x + 0.5, y + 0.5);
  // glVertex2d(x, y);
  while (x < line.pf.x)
  {
    if (d <= 0) d += E, x ++;
    else d += NE, x ++, y += yStep;
    printf("(%d, %d)\n", x, y);
    // if (steep) glVertex2d(y, x); else glVertex2d(x, y);
    if (steep) glRectd(y - 0.5, x - 0.5, y + 0.5, x + 0.5); else glRectd(x - 0.5, y - 0.5, x + 0.5, y + 0.5);
  }
  line = aux;
}

void drawLine()
{
  // glBegin(GL_POINTS);
    simpleLineAlgorithm();
    bresenham();
  // glEnd();
}

void scheduleUpdate(int value)
{
  // glutTimerFunc(10, scheduleUpdate, 1);
  // glutPostRedisplay();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3ub(0, 0, 255);
  drawLine();

  glutSwapBuffers();
}

void init()
{
  gluOrtho2D(0, 10, 0, 10);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(400, 100);
    glutCreateWindow("Title");
    init();
  glutDisplayFunc(display);
  glutTimerFunc(10, scheduleUpdate, 1);
  glutKeyboardFunc(keyboardHandler);
  glutMainLoop();
}