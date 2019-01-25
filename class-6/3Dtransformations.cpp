#if _WIN32
  #ifndef _WIN32
    #include <windows.h>
  #endif
#endif
#include <GL/freeglut.h>
#include <stdio.h>

struct Point { double x, y; };

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

  glPushMatrix();
    glColor3f(1, 0, 0);
    drawTriangle({100, 0}, {200, 200}, {200, 0});

    glColor3f(0, 1, 0);
    glTranslated(100, 0, 0);
    drawTriangle({-100, 0}, {0, 200}, {0, 0});

    glColor3f(0, 0, 1);
    double matrixd[4][4];
    memset(matrixd, 0, sizeof(matrixd)); 
    matrixd[0][0] = 2, matrixd[3][0] = -100;
    matrixd[1][1] = 1;
    matrixd[2][2] = matrixd[3][3] = 1;
    // glMultMatrixd(&matrixd[0][0]);
    glScaled(2, 1, 1);
    glTranslated(-100, 0, 0);
    drawTriangle({100, 0}, {200, 200}, {200, 0});

    glGetDoublev(GL_MODELVIEW_MATRIX, &matrixd[0][0]);
    for (int i = 0; i < 4; i ++)
      for (int j = 0; j < 4; j ++)
        printf("%3.3lf%c", matrixd[i][j], j < 3 ? ' ' : '\n');

  glPopMatrix();

  glFlush();
}

void init()
{
  glClearColor(0, 0, 0, 0);
  glMatrixMode(GL_MODELVIEW);
  gluOrtho2D(0, 600, 0, 600);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowSize(600, 600);
  glutCreateWindow("Retângulos");

  init();

  glutDisplayFunc(displayRect);
  glutKeyboardFunc(keyboardHandler);
  glutMainLoop();
  return(0);
}
