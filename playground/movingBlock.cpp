#include <stdio.h>
#ifdef _WIN32
    #include <windows.h>  // For MS Windows
#endif
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <chrono>
#include "./../sleep.h"
#include <GL/freeglut.h>  // GLUT, includes glu.h and gl.h

const double FPS = 60;
const double pi = 3.141592653589793;
double getTime()
{
  return(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}

double min(double a, double b) { return(a < b ? a : b); }
double max(double a, double b) { return(a > b ? a : b); }

struct Object { double x, y, dx, dy; };
double newSpeed() { double s = (rand() % 100) / 1000.0; return(s != 0 ? s : 0.01); }
void move(Object &object)
{
  if (object.x + object.dx - 0.5 < -1 || object.x + object.dx + 0.5 > 1)
    object.dx = newSpeed() * (object.dx > 0 ? 1 : -1) * -1;
  if (object.y + object.dy - 0.5 < -1 || object.y + object.dy + 0.5 > 1)
    object.dy = newSpeed() * (object.dy > 0 ? 1 : -1) * -1;
  object.x += object.dx, object.y += object.dy;
}

Object block = {0, 0, 0.01, 0.02};

void init()
{
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0, 200, 0, 150);
}

void display() {
  double start = getTime();

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
  glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

  // Draw a Red 1x1 Square centered at origin
  glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex2f(-0.5f + block.x, -0.5f + block.y);    // x, y
    glVertex2f( 0.5f + block.x, -0.5f + block.y);
    glVertex2f( 0.5f + block.x,  0.5f + block.y);
    glVertex2f(-0.5f + block.x,  0.5f + block.y);
  glEnd();

  glBegin(GL_POLYGON);              // Each set of 4 vertices form a quad
    glColor3f(0.0f, 0.0f, 1.0f); // Blue
    double star_x[5], star_y[5], x = 0, y = 0, cx = 0, cy = 0, size = 0.25, angle = 72*pi/180.0;
    star_x[0] = star_y[0] = 0;
    for (int i = 1; i < 5; i ++)
    {
      x += size * cos(angle), y += size * sin(angle);
      angle += -144*pi/180.0;
      cx += x, cy += y;
      star_x[i] = x, star_y[i] = y;
    } cx /= 5.0, cy /= 5.0;
    for (int i = 0; i < 5; i ++)
    {
      printf("%d - {%.3g, %.3g}\n", i, cx - star_x[i], cy - star_y[i]);
      glVertex2f(cx - star_x[i], cy - star_y[i]);
    }
  glEnd();

  move(block);

  glFlush();  // Render now

  double end = getTime();
  // printf("{%.3g, %.3g, %.3g, %.3g} %.3g\n", block.x, block.y, block.dx, block.dy, end - start);
  mysleep(max(0, 1000.0/FPS - (end - start)));

  glutPostRedisplay();
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
  srand(time(NULL));
  glutInit(&argc, argv);                 // Initialize GLUT
  glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
  glutInitWindowSize(320, 320);   // Set the window's initial width & height
  // init(); Defines our canvas
  glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
  glutDisplayFunc(display); // Register display callback handler for window re-paint
  glutMainLoop();           // Enter the infinitely event-processing loop
  return 0;
}
/*
x - pi
y - 180
x*180 = y*pi
x = y*pi/180
*/
