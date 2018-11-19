#include <stdio.h>
#include <windows.h>  // For MS Windows
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include "./../sleep.h"
#include <GL/freeglut.h>  // GLUT, includes glu.h and gl.h

double getTime()
{
  return(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}

struct Object { double x, y, dx, dy; };
void move(Object &object)
{
  if (object.x + object.dx - 0.5 < -1 || object.x + object.dx + 0.5 > 1)
    object.dx = (rand() % 100) / 1000.0 * (object.dx > 0 ? 1 : -1) * -1;
  if (object.y + object.dy - 0.5 < -1 || object.y + object.dy + 0.5 > 1)
    object.dy = (rand() % 100) / 1000.0 * (object.dy > 0 ? 1 : -1) * -1;
  object.x += object.dx, object.y += object.dy;
}

Object block = {0, 0, 0.01, 0.02};

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

  move(block);

  glFlush();  // Render now

  double end = getTime();
  sleep(1000.0/60.0 - (end - start));

  glutPostRedisplay();
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
  srand(time(NULL));
  glutInit(&argc, argv);                 // Initialize GLUT
  glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
  glutInitWindowSize(320, 320);   // Set the window's initial width & height
  glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
  glutDisplayFunc(display); // Register display callback handler for window re-paint
  glutIdleFunc(display);
  glutMainLoop();           // Enter the infinitely event-processing loop
  return 0;
}
