#if _WIN32
  #ifndef _WIN32
    #include <windows.h>
  #endif
#endif
#include "../printText.h"
#include <GL/freeglut.h>
#include <complex>
using namespace std;
const int width = 1000, height = 1000;
int w = width, h = height;
double dw = 1, dh = 1, sw = 0, sh = 0, limit = 1e3;
int steps = 10;
bool bitmap[10001][10001];

complex<double> f(complex<double> c, complex<double> z) { return(z*z + c); }
bool diverges(complex<double> c)
{
  complex<double> z = 0;
  for (int i = 0; i < steps; i ++)
  {
    complex<double> res = f(c, z);
    if (res.real() < -limit || res.real() > limit || res.imag() < -limit || res.imag() > limit) return(true);
    z = res;
  }
  return(false);
}

void fillMandelBrotSet()
{
  double wShift = -w * dw / 2.0 + sw, hShift = -h * dh / 2.0 + sh;
  for (double i = 0; i <= h; i ++)
    for (double j = 0; j <= w; j ++)
      bitmap[(int) i][(int) j] = diverges(complex(wShift + j * dw, hShift + i * dh));
}

void keyboardHandler(unsigned char key, int x, int y)
{
  switch (key)
  {
    case 'r': fillMandelBrotSet(); break;
    case 'c': memset(bitmap, false, sizeof(bitmap)); break;
    case '1': dw /= 2.0; break;
    case '2': dw *= 2.0; break;
    case '3': dh /= 2.0; break;
    case '4': dh *= 2.0; break;
    case '5': steps *= 2; break;
    case '6': steps /= 2; break;
    case 'a': sw += 10*dw; break;
    case 'd': sw -= 10*dw; break;
    case 'w': sh += 10*dh; break;
    case 's': sh -= 10*dh; break;
    case 'f': w ++; break;
    case 'F': w --; break;
    case 'g': h ++; break;
    case 'G': h --; break;
    default: break;
  }
}

void scheduleUpdate(int value)
{
  glutTimerFunc(10, scheduleUpdate, 1);
  fillMandelBrotSet();
  glutPostRedisplay();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3ub(0, 0, 100);
  glColor3ub(255, 255, 255);
  for (int i = 0; i <= h; i ++)
    for (int j = 0; j <= w; j ++)
      if (bitmap[i][j])
        glRectd(j * (double) width / w, i * (double) height / h, (j + 1) * (double) width / w, (i + 1) * (double) height / h);

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
    glutCreateWindow("Title");
    init();
  glutTimerFunc(10, scheduleUpdate, 1);
  glutKeyboardFunc(keyboardHandler);
  glutDisplayFunc(display);
  glutMainLoop();
}