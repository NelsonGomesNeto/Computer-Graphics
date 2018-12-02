#ifndef _WIN32
  #include <windows.h>
#endif
#include <math.h>
#include <GL/freeglut.h>
const int width = 800, height = 800;
const double pi = acos(-1), tau = 2 * acos(-1), gravitationConstant = 100;
double degToRad(double a) { return(a*pi/180.0); }
struct Point { double x, y; };
struct Object { Point position, speed, acceleration; double mass; };
Object sun = {{400, 400}, {0, 0}, {0, 0}, 50}, earth = {{200, 400}, {0, 50}, {0, 0}, 1};

void scheduleUpdate(int v)
{
  glutTimerFunc(10, scheduleUpdate, 1);
  earth.acceleration.x = earth.speed.x * earth.speed.mass
  glutPostRedisplay();
}

void drawCircle(Point position, int radious, int triangles)
{
  glBegin(GL_TRIANGLE_FAN);
    glVertex2d(position.x, position.y);
    for (int i = 0; i <= triangles; i ++)
      glVertex2d(position.x + radious * cos((double) i / triangles * tau), position.y + radious * sin((double) i / triangles * tau));
  glEnd();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  drawCircle(sun.position, sun.mass, 10);
  drawCircle(earth.position, earth.mass, 10);

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
    glutInitWindowPosition(400, 100);
    glutCreateWindow("Window name");
    init();
  glutDisplayFunc(display);
  glutTimerFunc(10, scheduleUpdate, 1);
  glutMainLoop();
}