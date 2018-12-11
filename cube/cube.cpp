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
double xOffset = 0, yOffset = 0, zOffset = 0.5, cubeSize = 0.5;
struct Piece { int color[6] = {0, 1, 2, 3, 4, 5}; }; // 0 - face, 1 - top, 2 - back, 3 - down, 4 - left, 5 - right
const double colorMap[6][3] = {{253 / 255.0, 126 / 255.0, 0}, {255 / 255.0, 0, 0}, {0, 255 / 255.0, 0}, {0, 0, 255 / 255.0}, {255 / 255.0, 255 / 255.0, 255 / 255.0}, {255 / 255.0, 241 / 255.0, 25 / 255.0}};
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

void drawPiece(Piece &piece, double size)
{
  glPushMatrix();
    glTranslated(0, 0, -cubeSize / 2.0);
      glColor3dv(colorMap[piece.color[0]]);
      glRectd(-cubeSize / 2.0, -cubeSize / 2.0, cubeSize / 2.0, cubeSize / 2.0);
    glTranslated(0, 0, cubeSize);
      glColor3dv(colorMap[piece.color[1]]);
      glRectd(-cubeSize / 2.0, -cubeSize / 2.0, cubeSize / 2.0, cubeSize / 2.0);
  glPopMatrix();

  glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslated(0, 0, -cubeSize / 2.0);
      glColor3dv(colorMap[piece.color[2]]);
      glRectd(-cubeSize / 2.0, -cubeSize / 2.0, cubeSize / 2.0, cubeSize / 2.0);
    glTranslated(0, 0, cubeSize);
      glColor3dv(colorMap[piece.color[3]]);
      glRectd(-cubeSize / 2.0, -cubeSize / 2.0, cubeSize / 2.0, cubeSize / 2.0);
  glPopMatrix();

  glPushMatrix();
    glRotated(90, 1, 0, 0);
    glTranslated(0, 0, -cubeSize / 2.0);
      glColor3dv(colorMap[piece.color[4]]);
      glRectd(-cubeSize / 2.0, -cubeSize / 2.0, cubeSize / 2.0, cubeSize / 2.0);
    glTranslated(0, 0, cubeSize);
      glColor3dv(colorMap[piece.color[5]]);
      glRectd(-cubeSize / 2.0, -cubeSize / 2.0, cubeSize / 2.0, cubeSize / 2.0);
  glPopMatrix();
}
void drawCube(Cube &c)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      for (int k = 0; k < n; k++)
      {
        drawPiece(c.pieces[i][j][k], cubeSize);
        glTranslated(cubeSize, 0, 0);
      }
      glTranslated(-n * cubeSize, -cubeSize, 0);
    }
    glTranslated(0, n * cubeSize, cubeSize);
  }
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
    glColor3ub(0, 0, 255);
    glTranslated(xOffset - n / 2 * cubeSize, yOffset + n / 2 * cubeSize, zOffset - n / 2 * cubeSize);
    drawCube(cube);
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
  glEnable(GL_DEPTH_TEST);
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
