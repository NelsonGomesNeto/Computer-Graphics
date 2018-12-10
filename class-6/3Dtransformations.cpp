#include <GL/freeglut.h>

struct Point { int x, y; };

void keyboardHandler(unsigned char key, int x, int y)
{
  if (key == 'q') exit(0);
}

void drawTriangle(Point a, Point b, Point c)
{
  glBegin(GL_TRIANGLES);
    glVertex2d(a.x, a.y);
    glVertex2d(b.x, b.y);
    glVertex2d(c.x, c.y);
  glEnd();
}

void displayRect()
{
  glClear(GL_COLOR_BUFFER_BIT);

  // glLoadIdentity();
  // gluOrtho2D(0, 600, 0, 400);


  glColor3f(1, 0, 0);
  drawTriangle({100, 0}, {200, 200}, {200, 0});

  glTranslatef(-100, 0, 0);

  drawTriangle({100, 0}, {200, 200}, {200, 0});

  glScaled(2, 1, 0);
  glTranslatef(100, 0, 0);

  drawTriangle({0, 0}, {100, 200}, {100, 0});

  glFlush();
}

void init()
{
  glClearColor(0, 0, 0, 0);
  glMatrixMode(GL_MODELVIEW);
  gluOrtho2D(0, 600, 0, 400);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowSize(600, 400);
  glutCreateWindow("Retangulos");

  init();

  glutDisplayFunc(displayRect);
  glutKeyboardFunc(keyboardHandler);
  glutMainLoop();
  return(0);
}
