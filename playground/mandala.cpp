#if _WIN32
  #ifndef _WIN32
    #include <windows.h>
  #endif
#endif
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>
const int width = 800, height = 800;
double penSize = 3;
struct Vector
{
  double x, y, z;
  double mag() { return(sqrt(x*x + y*y + z*z)); }
  void operator+=(const Vector &a) { x += a.x, y += a.y, z += a.z; }
  Vector operator-(const Vector &a) { return(Vector({x - a.x, y - a.y, z - a.z})); }
  void normalize() { double m = mag(); x /= m, y /= m, z /= m; }
  void limit(double l) { double m = mag(); x *= l / m, y *= l / m, z *= l / m; }
};
int reflections = 1;

Vector pen = {0, 0, 0}, mouse = {0, 0, 0}, speed = {0, 0, 0}, acceleration = {0, 0, 0};
bool drawing = false;
void mouseHandler(int button, int state, int x, int y)
{
  mouse.x = x, mouse.y = y;
  if (!drawing && state == GLUT_DOWN) drawing = true;
  else if (drawing && state == GLUT_UP) drawing = false;
}
void motionHandler(int x, int y)
{
  mouse.x = x, mouse.y = y;
}

void update(int value)
{
  glutTimerFunc(1, update, 1);
  Vector dv = mouse - pen; dv.normalize();
  acceleration += dv; acceleration.limit(0.1);
  speed += acceleration;
  speed.limit(1); pen += speed;
  glutPostRedisplay();
}

void display()
{
  // glClear(GL_COLOR_BUFFER_BIT);

  if (drawing)
  {
    double angle = (double) 360 / reflections;
    glColor3ub(255, 255, 255);
    glPointSize(penSize);
    glPushMatrix();
      glTranslated(width >> 1, height >> 1, 0);
      glBegin(GL_POINTS); glVertex2d(pen.x - (width >> 1), pen.y - (height >> 1)); glEnd();
      for (int i = 1; i <= reflections; i ++)
      {
        glRotated(angle, 0, 0, 1);
        glBegin(GL_POINTS); glVertex2d(pen.x - (width >> 1), pen.y - (height >> 1)); glEnd();
      }
    glPopMatrix();
  }

  glutSwapBuffers();
}

void init()
{
  gluOrtho2D(0, width, height, 0);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(400, 100);
    glutCreateWindow("Mandala");
    init();
  glutDisplayFunc(display);
  glutTimerFunc(10, update, 1);
  glutMouseFunc(mouseHandler);
  glutMotionFunc(motionHandler);
  glutPassiveMotionFunc(motionHandler);
  glutMainLoop();
}