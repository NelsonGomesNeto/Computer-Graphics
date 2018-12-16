#if _WIN32
  #ifndef _WIN32
    #include <windows.h>
  #endif
#endif
#include <stdio.h>
#include <GL/freeglut.h>
#include <vector>
#include "cube.h"
using namespace std;

const int width = 800, height = 800;
double xOffset = 0, yOffset = 0, zOffset = 0, xAngle = 0, yAngle = 0, zAngle = 0, diff = 0, cubeSize = 4.0 / n;
Cube cube;

struct Point { int x, y; };
Point mouse, startMouse = {0, 0}; bool started = false; int axes;
void passiveMotionHandler(int x, int y)
{
  diff = y - startMouse.y;
}

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
    case '1': if (!started) started = true, startMouse.x = x, startMouse.y = y, axes = key - '0'; else started = false; break;
    case '2': if (!started) started = true, startMouse.x = x, startMouse.y = y, axes = key - '0'; else started = false; break;
    case '3': if (!started) started = true, startMouse.x = x, startMouse.y = y, axes = key - '0'; else started = false; break;
    default: moveCube(cube, key); break;
  }
}

void scheduleUpdate(int value)
{
  glutTimerFunc(10, scheduleUpdate, 1);
  if (started) switch (axes)
  {
    case 1: xAngle += diff / 1000.0; break;
    case 2: yAngle += diff / 1000.0; break;
    case 3: zAngle += diff / 1000.0; break;
    default: break;
  }
  glutPostRedisplay();
}

void drawArrow()
{
  glBegin(GL_LINES);
    glVertex3d(0, 0, 0);
    glVertex3d(3, 0, 0);
  glEnd();
}
void drawSpaceVectors()
{
  glLineWidth(8);
  glPushMatrix();
    // glTranslated(-8*cubeSize, -5*cubeSize, 0);
    glColor3ub(255, 0, 0);
    drawArrow(); // x
    glPushMatrix();
      glRotated(90, 0, 0, 1);
      glColor3ub(0, 255, 0);
      drawArrow(); // y
    glPopMatrix();
    glPushMatrix();
      glRotated(90, 0, 1, 0);
      glColor3ub(0, 0, 255);
      drawArrow(); // z
    glPopMatrix();
  glPopMatrix();
}

void drawPiece(Piece &piece, double size, int i, int j, int k)
{
  glLineWidth(1);
  glColor3ub(0, 0, 0);
  // glColor3ub(255, 255, 255);
  glutWireCube(cubeSize);

  if (i == 0)
  {
    glPushMatrix();
      glTranslated(0, 0, cubeSize / 2.0);
        glColor3dv(colorMap[piece.color[0]]);
        glRectd(-cubeSize / 2.0, -cubeSize / 2.0, cubeSize / 2.0, cubeSize / 2.0);
    glPopMatrix();
  }
  else if (i == n - 1)
  {
    glPushMatrix();
      glTranslated(0, 0, -cubeSize / 2.0);
        glColor3dv(colorMap[piece.color[2]]);
        glRectd(-cubeSize / 2.0, -cubeSize / 2.0, cubeSize / 2.0, cubeSize / 2.0);
    glPopMatrix();
  }

  if (j == 0)
  {
    glPushMatrix();
      glRotated(90, 1, 0, 0);
      glTranslated(0, 0, -cubeSize / 2.0);
        glColor3dv(colorMap[piece.color[1]]);
        glRectd(-cubeSize / 2.0, -cubeSize / 2.0, cubeSize / 2.0, cubeSize / 2.0);
    glPopMatrix();
  }
  else if (j == n - 1)
  {
    glPushMatrix();
      glRotated(90, 1, 0, 0);
      glTranslated(0, 0, cubeSize / 2.0);
        glColor3dv(colorMap[piece.color[3]]);
        glRectd(-cubeSize / 2.0, -cubeSize / 2.0, cubeSize / 2.0, cubeSize / 2.0);
    glPopMatrix();
  }

  if (k == 0)
  {
    glPushMatrix();
      glRotated(90, 0, 1, 0);
      glTranslated(0, 0, -cubeSize / 2.0);
        glColor3dv(colorMap[piece.color[4]]);
        glRectd(-cubeSize / 2.0, -cubeSize / 2.0, cubeSize / 2.0, cubeSize / 2.0);
    glPopMatrix();
  }
  else if (k == n - 1)
  {
    glPushMatrix();
      glRotated(90, 0, 1, 0);
      glTranslated(0, 0, cubeSize / 2.0);
        glColor3dv(colorMap[piece.color[5]]);
        glRectd(-cubeSize / 2.0, -cubeSize / 2.0, cubeSize / 2.0, cubeSize / 2.0);
    glPopMatrix();
  }
}
void drawCube(Cube &c)
{
  for (int i = 0; i < n; i ++)
  {
    if (i == 0 || i == n - 1)
    {
      for (int j = 0; j < n; j ++)
      {
        for (int k = 0; k < n; k ++)
        {
          drawPiece(c.pieces[i][j][k], cubeSize, i, j, k);
          glTranslated(cubeSize, 0, 0);
        }
        glTranslated(-n*cubeSize, -cubeSize, 0);
      }
      glTranslated(0, n*cubeSize, -cubeSize);
    }
    else
    {
      int j = 0, k = 0;
      while (k < n) { drawPiece(c.pieces[i][j][k], cubeSize, i, j, k); glTranslated(cubeSize, 0, 0); k ++; } glTranslated(-cubeSize, -cubeSize, 0), k --, j ++;
      while (j < n) { drawPiece(c.pieces[i][j][k], cubeSize, i, j, k); glTranslated(0, -cubeSize, 0); j ++; } glTranslated(-cubeSize, cubeSize, 0), j --, k --;
      while (k >= 0) { drawPiece(c.pieces[i][j][k], cubeSize, i, j, k); glTranslated(-cubeSize, 0, 0); k --; } glTranslated(cubeSize, cubeSize, 0), k ++, j --;
      while (j >= 1) { drawPiece(c.pieces[i][j][k], cubeSize, i, j, k); glTranslated(0, cubeSize, 0); j --; }
      glTranslated(0, 0, -cubeSize);
    }
  }
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
    glRotated(xAngle, 1, 0, 0); glRotated(yAngle, 0, 1, 0); glRotated(zAngle, 0, 0, 1);
    glTranslated(-n / 2 * cubeSize + xOffset, n / 2 * cubeSize + yOffset, n / 2 * cubeSize + zOffset);

    glColor3ub(0, 0, 255);
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
  gluLookAt(5, 5, 6, 0, 0, 0, 0, 1, 0);
}

void init()
{
  glClearColor(0, 0, 0, 0);
  glEnable(GL_DEPTH_TEST);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(1000, 100);
    glutCreateWindow("Cube");
    init();
  glutDisplayFunc(display);
  glutTimerFunc(10, scheduleUpdate, 1);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboardHandler);
  glutPassiveMotionFunc(passiveMotionHandler);
  glutMainLoop();
  return(0);
}
