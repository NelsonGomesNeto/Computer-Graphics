#if _WIN32
  #ifndef _WIN32
    #include <windows.h>
  #endif
#endif
#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>
#include <vector>
#include "cube.h"
#include "../printText.h"
#include "../quaternions.h"
using namespace std;

const int width = 800, height = 800; const double pi = acos(-1);
double xOffset = 0, yOffset = 0, zOffset = 0, xAngle = 0, yAngle = 0, zAngle = 0, diff = 0, xDiff = 0, yDiff = 0, cubeSize = 4.0 / n;
double degToRad(double angle) { return(angle*pi/180.0); };
Cube cube; Quaternions orientation;

struct Point { int x, y; };
Point mouse, startMouse = {0, 0}; bool rotating = false, mouseRotating = false; int axes;
void passiveMotionHandler(int x, int y)
{

  if (rotating) diff = (y - startMouse.y) / 100.0;
  if (mouseRotating) xDiff = (x - startMouse.x) / 100.0, yDiff = (y - startMouse.y) / 100.0;
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
    case '1': if (!rotating) rotating = true, startMouse.x = x, startMouse.y = y, axes = key - '0'; else rotating = false, diff = 0; break;
    case '2': if (!rotating) rotating = true, startMouse.x = x, startMouse.y = y, axes = key - '0'; else rotating = false, diff = 0; break;
    case '3': if (!rotating) rotating = true, startMouse.x = x, startMouse.y = y, axes = key - '0'; else rotating = false, diff = 0; break;
    case '4': if (!mouseRotating) mouseRotating = true, startMouse.x = x, startMouse.y = y, axes = key - '0'; else mouseRotating = false, xDiff = yDiff = 0; break;
    default: moveCube(cube, key); break;
  }
}

void scheduleUpdate(int value)
{
  glutTimerFunc(10, scheduleUpdate, 1);
  if (rotating || mouseRotating) switch (axes)
  {
    case 1: xAngle += diff; break;
    case 2: yAngle += diff; break;
    case 3: zAngle += diff; break;
    case 4: xAngle += yDiff, yAngle += xDiff; break;
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
    glTranslated(-n / 2 * cubeSize + xOffset, (n / 2 + 2) * cubeSize + yOffset, n / 2 * cubeSize + zOffset);
    glColor3ub(255 * (axes == 1), 255 * (axes == 2), 255 * (axes == 3));
    if (rotating) printText("Rotating: " + (string)(axes == 1 ? "x" : axes == 2 ? "y" : "z") + "-axes", 0, 0);
    glColor3ub(255, 255, 255);
    printText("(" + to_string(xAngle) + ", " + to_string(yAngle) + ", " + to_string(zAngle) + ")", 0, -cubeSize / 2.0);
  glPopMatrix();

  glPushMatrix();
    // double sinY = sin(degToRad(yAngle)), sinY2 = sin(degToRad(90+yAngle)), cosY = cos(degToRad(yAngle)), cosY2 = cos(degToRad(0+yAngle));
    // double sinX = sin(degToRad(xAngle)), sinX2 = sin(degToRad(0+xAngle)), cosX = cos(degToRad(xAngle)), cosX2 = cos(degToRad(90+xAngle));
    // // (0, 0) -> (0, 0, 1)
    // // (90, 90) -> (1, 0, 0)
    // // (180, 180) -> (0, 0, 1)
    // // (0, 90) -> (1, 0, 0)
    // // (0, 180) -> (0, 0, -1)
    // // (90, 0) -> (0, -1, 0)
    // // (180, 0) -> (0, 0, -1)
    // double zTurn = 1 - sinY * cosX + sinX * cosY;
    // double zTurn2 = sinY2 * cosX2 + sinX2 * cosY2;
    // double zTurn3 = cosX * cosY;
    // glRotated(xAngle, 1, 0, 0); glRotated(yAngle, 0, cosX, -sinX); glRotated(zAngle, sinY, sinX * cosY, zTurn3);
    double cosX = cos(degToRad(xAngle * 0.5)), sinX = sin(degToRad(xAngle * 0.5));
    double cosY = cos(degToRad(yAngle * 0.5)), sinY = sin(degToRad(yAngle * 0.5));
    double cosZ = cos(degToRad(zAngle * 0.5)), sinZ = sin(degToRad(zAngle * 0.5));
    orientation = {cosZ*cosY*cosX + sinZ*sinY*sinX,
                   cosZ*cosY*sinX - sinZ*sinY*cosX,
                   sinZ*cosY*sinX + cosZ*sinY*cosX,
                   sinZ*cosY*cosX - cosZ*sinY*sinX};
    double rot[4][4], lol[16]; orientation.fillMat4(rot);
    // for (int i = 0; i < 4; i ++) for (int j = 0; j < 4; j ++) printf("%3.3lf%c", rot[i][j], j < 3 ? ' ' : '\n');
    glMultMatrixd(&rot[0][0]);
    glGetDoublev(GL_MODELVIEW_MATRIX, lol);
    for (int i = 0; i < 4; i ++) for (int j = 0; j < 4; j ++) printf("%3.3lf%c", lol[i*4+j], j < 3 ? ' ' : '\n'); printf("\n");
    // printf("(%3.3lf, %3.3lf, %3.3lf [%3.3lf] {%3.3lf})\n", sinY, sinX * cosY, zTurn, zTurn2, zTurn3);
    drawSpaceVectors();

    // glPushMatrix();
    //   glTranslated(0, (n / 2 + 2) * cubeSize, 0);
    // glPopMatrix();

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
