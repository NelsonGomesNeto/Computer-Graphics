#include <stdio.h>
#ifdef _WIN32
    #include <windows.h>  // For MS Windows
#endif
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include "./../sleep.h"
#include <GL/freeglut.h>  // GLUT, includes glu.h and gl.h

double getTime()
{
  return(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}

double min(double a, double b) { return(a < b ? a : b); }
double max(double a, double b) { return(a > b ? a : b); }

struct Object { double x, y, dx, dy; };
struct Point { double x, y; }
double newSpeed() { double s = (rand() % 100) / 1000.0; return(s != 0 ? s : 0.01); }
void move(Object &object)
{
  if (object.x + object.dx - 0.01 < -1 || object.x + object.dx + 0.01 > 1)
    object.dx = newSpeed() * (object.dx > 0 ? 1 : -1) * -1;
  if (object.y + object.dy - 0.01 < -1 || object.y + object.dy + 0.01 > 1)
    object.dy = newSpeed() * (object.dy > 0 ? 1 : -1) * -1;
  object.x += object.dx, object.y += object.dy;
}

// TODO
void bresenham(Point p1, Point p2)
{
  double m = (p2.y - p1.y) / (p2.x - p1.x);

}

Object block = {0, 0, 0.01, 0.02};

void init()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
  glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
}

void display() {
  double start = getTime();

  // Draw a Red 1x1 Square centered at origin
  glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex2f(-0.01 + block.x, -0.01 + block.y);    // x, y
    glVertex2f( 0.01 + block.x, -0.01 + block.y);
    glVertex2f( 0.01 + block.x,  0.01 + block.y);
    glVertex2f(-0.01 + block.x,  0.01 + block.y);
  glEnd();

  move(block);

  glFlush();  // Render now

  double end = getTime();
  mysleep(max(0, 1000.0/60.0 - (end - start)));

  glutPostRedisplay();
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
  srand(time(NULL));
  glutInit(&argc, argv);                 // Initialize GLUT
  glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
  glutInitWindowSize(320, 320);   // Set the window's initial width & height
  glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
  init();
  glutDisplayFunc(display); // Register display callback handler for window re-paint
  glutMainLoop();           // Enter the infinitely event-processing loop
  return 0;
}
