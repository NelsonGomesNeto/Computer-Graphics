#if _WIN32
  #ifndef _WIN32
    #include <windows.h>
  #endif
#endif
#include <stdio.h>
#include <GL/freeglut.h>
#include <vector>
using namespace std;

const int width = 600, height = 600, n = 3;
double xOffset = 0, yOffset = 0, zOffset = 1.5, cubeSize = 0.5;
struct Piece { int color[6]; }; // 0 - face, 1 - top, 2 - back, 3 - down, 4 - left, 5 - right
struct Cube { Piece pieces[n][n][n]; };
Cube cube;

void keyboardHandler(unsigned char key, int x, int y)
{
  switch (key)
  {
    case 'z': zOffset += 0.05; break;
    case 'Z': zOffset -= 0.05; break;
    case 'x': xOffset += 0.05; break;
    case 'X': xOffset -= 0.05; break;
    case 'y': yOffset += 0.05; break;
    case 'Y': yOffset -= 0.05; break;
    default: break;
  }
}

void scheduleUpdate(int value)
{
  glutTimerFunc(10, scheduleUpdate, 1);
  glutPostRedisplay();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  printf("zOffset: %.3lf\n", zOffset);

  glPushMatrix();
    glColor3ub(0, 0, 255);
    glTranslated(xOffset - n / 2 * cubeSize, yOffset + n / 2 * cubeSize, zOffset - n / 2 * cubeSize);
    for (int i = 0; i < n; i ++) // depth
    {
      for (int j = 0; j < n; j ++) // height
      {
        for (int k = 0; k < n; k ++); // width
        {
          glutSolidCube(cubeSize);
          glTranslated(0, cubeSize, 0);
        }
        glTranslated(-n * cubeSize, -cubeSize, 0);
      }
      glTranslated(n * cubeSize, n * cubeSize, -cubeSize);
    }
  glPopMatrix();

  glutSwapBuffers();
}

void reshape(int w, int h)
{
  glViewport(0, 0, w, h);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluPerspective(60, (double) w / h, 1, 20);
  gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
}

void init()
{
  glClearColor(0, 0, 0, 0);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(1000, 100);
    glutCreateWindow("Cube");
    init();
  glutDisplayFunc(display);
  glutTimerFunc(10, scheduleUpdate, 1);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboardHandler);
  glutMainLoop();
  return(0);
}
