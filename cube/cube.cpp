#if _WIN32
  #ifndef _WIN32
    #include <windows.h>
  #endif
#endif
#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>
#include <vector>
#include "solver.h"
// #include "cube.h"
#include "../printText.h"
#include "../quaternions.h"
using namespace std;

const int width = 800, height = 800; const double pi = acos(-1);
double xOffset = 0, yOffset = 0, zOffset = 0, xAngle = 0, yAngle = 0, zAngle = 0, diff = 0, xDiff = 0, yDiff = 0, cubeSize = 4.0 / n;
double degToRad(double angle) { return(angle*pi/180.0); };
Cube cube; Quaternions orientation = {1, 0, 0, 0}; double rotationMatrix[4][4]; int number = 1;
bool BORDER = true;

struct Point { int x, y; };
Point mouse = {0, 0}; bool rotating = false, mouseRotating = false; int axis;
void passiveMotionHandler(int x, int y)
{
  if (rotating) diff = (y - mouse.y) / 100.0;
  if (mouseRotating) xDiff = (x - mouse.x) / 100.0, yDiff = (y - mouse.y) / 100.0;
}

void keyboardHandler(unsigned char key, int x, int y)
{
  switch (key)
  {
    case 'x': xOffset += 0.05; break;
    case 'X': xOffset -= 0.05; break;
    case 'y': yOffset += 0.05; break;
    case 'Y': yOffset -= 0.05; break;
    case 'z': zOffset += 0.05; break;
    case 'Z': zOffset -= 0.05; break;
    case 'q': if (!rotating) rotating = true, mouse.x = x, mouse.y = y, axis = 1; else rotating = false, diff = 0; break;
    case 'w': if (!rotating) rotating = true, mouse.x = x, mouse.y = y, axis = 2; else rotating = false, diff = 0; break;
    case 'e': if (!rotating) rotating = true, mouse.x = x, mouse.y = y, axis = 3; else rotating = false, diff = 0; break;
    case 'a': if (!mouseRotating) mouseRotating = true, mouse.x = x, mouse.y = y, axis = 4; else mouseRotating = false, xDiff = yDiff = 0; break;
    case 'd': readScramble(cube); break;
    // case '2': bfs(cube); break;
    case 's': solve(cube); break;
    case ' ': number = 0; break;
    default:
      if (key >= '0' && key <= '9')
      {
        number = number * 10 + key - '0'; number = min(number, n);
      }
      else
      {
        if (number) moveCube(cube, key, number - 1);
      }
      break;
  }
}

void scheduleUpdate(int value)
{
  glutTimerFunc(10, scheduleUpdate, 1);
  if (rotating || mouseRotating) switch (axis)
  {
    case 1: xAngle += diff; orientation *= Quaternions({cos(degToRad(diff*0.5)), sin(degToRad(diff*0.5)), 0, 0}); break;
    case 2: yAngle += diff; orientation *= Quaternions({cos(degToRad(-diff*0.5)), 0, sin(degToRad(-diff*0.5)), 0}); break;
    case 3: zAngle += diff; orientation *= Quaternions({cos(degToRad(diff*0.5)), 0, 0, sin(degToRad(diff*0.5))}); break;
    case 4:
      xAngle += yDiff, yAngle += xDiff;
      orientation *= Quaternions({cos(degToRad(-yDiff*0.5)), sin(degToRad(-yDiff*0.5)), 0, 0});
      orientation *= Quaternions({cos(degToRad(xDiff*0.5)), 0, sin(degToRad(xDiff*0.5)), 0});
      break;
    default: break;
  }
  orientation.normalize();
  glutPostRedisplay();
}

void drawArrow()
{
  glBegin(GL_LINES);
    glVertex3d(0, 0, 0);
    glVertex3d(3.5, 0, 0);
  glEnd();
}
void drawSpaceVectors()
{
  glLineWidth(8);
  glPushMatrix();
    glColor3ub(255, 0, 0);
    drawArrow(); // x
    glPushMatrix();
      glRotated(90, 0, 0, 1);
      glColor3ub(0, 255, 0);
      drawArrow(); // y
    glPopMatrix();
    glPushMatrix();
      glRotated(90, 0, -1, 0);
      glColor3ub(0, 0, 255);
      drawArrow(); // z
    glPopMatrix();
  glPopMatrix();
}

void drawLine()
{
  glBegin(GL_LINES);
    glVertex2d(-(n / 2.0) * cubeSize, 0);
    glVertex2d((n / 2.0) * cubeSize, 0);
  glEnd();
}
void drawLines(int i)
{
  glTranslated(0, (n/2.0 - i - 1) * cubeSize, (n / 2.0) * cubeSize); drawLine();
  glTranslated(0, 0, -n * cubeSize); drawLine();
  glTranslated(0, 0, (n / 2.0) * cubeSize);
}
void drawCube(Cube &c)
{
  for (int j = 0; j < n; j ++)
    for (int k = 0; k < n; k ++)
    {
      glPushMatrix();
        // front
        glTranslated((n/2.0 - k - 0.5) * cubeSize, (n/2.0 - j - 0.5) * cubeSize, (n / 2.0) * cubeSize);
        glColor3dv(colorMap[cube.face[0][j][k]]);
        glRectd(-cubeSize / 2.0, -cubeSize / 2.0, cubeSize / 2.0, cubeSize / 2.0);
        glPushMatrix();
          glColor3ub(0, 0, 0); glTranslated(0, 0, cubeSize/3.0); printText(to_string(j) + ", " + to_string(k), 0, 0);
        glPopMatrix();
        
        // back
        glTranslated(0, 0, -n * cubeSize);
        glColor3dv(colorMap[cube.face[2][j][k]]);
        glRectd(-cubeSize / 2.0, -cubeSize / 2.0, cubeSize / 2.0, cubeSize / 2.0);
        glPushMatrix();
          glColor3ub(0, 0, 0); glTranslated(0, 0, -cubeSize/3.0); printText(to_string(j) + ", " + to_string(k), 0, 0);
        glPopMatrix();
        
      glPopMatrix();
      glPushMatrix();
        // top
        glRotated(90, -1, 0, 0);
        glTranslated((n/2.0 - k - 0.5) * cubeSize, (n/2.0 - j - 0.5) * cubeSize, (n / 2.0) * cubeSize);
        glColor3dv(colorMap[cube.face[1][j][k]]);
        glRectd(-cubeSize / 2.0, -cubeSize / 2.0, cubeSize / 2.0, cubeSize / 2.0);
        glPushMatrix();
          glColor3ub(0, 0, 0); glTranslated(0, 0, cubeSize/3.0); printText(to_string(j) + ", " + to_string(k), 0, 0);
        glPopMatrix();
        
        // down
        glTranslated(0, 0, -n * cubeSize);
        glColor3dv(colorMap[cube.face[3][j][k]]);
        glRectd(-cubeSize / 2.0, -cubeSize / 2.0, cubeSize / 2.0, cubeSize / 2.0);
        glPushMatrix();
          glColor3ub(0, 0, 0); glTranslated(0, 0, -cubeSize/3.0); printText(to_string(j) + ", " + to_string(k), 0, 0);
        glPopMatrix();
        
      glPopMatrix();
      glPushMatrix();
        // right
        glRotated(90, 0, -1, 0);
        glTranslated((n/2.0 - k - 0.5) * cubeSize, (n/2.0 - j - 0.5) * cubeSize, (n / 2.0) * cubeSize);
        glColor3dv(colorMap[cube.face[4][j][k]]);
        glRectd(-cubeSize / 2.0, -cubeSize / 2.0, cubeSize / 2.0, cubeSize / 2.0);
        glPushMatrix();
          glColor3ub(0, 0, 0); glTranslated(0, 0, cubeSize/3.0); printText(to_string(j) + ", " + to_string(k), 0, 0);
        glPopMatrix();
        
        // left
        glTranslated(0, 0, -n * cubeSize);
        glColor3dv(colorMap[cube.face[5][j][k]]);
        glRectd(-cubeSize / 2.0, -cubeSize / 2.0, cubeSize / 2.0, cubeSize / 2.0);
        glPushMatrix();
          glColor3ub(0, 0, 0); glTranslated(0, 0, -cubeSize/3.0); printText(to_string(j) + ", " + to_string(k), 0, 0);
        glPopMatrix();
        
      glPopMatrix();
    }
  if (BORDER)
  {
    glColor3ub(0, 0, 0); glLineWidth(3);
    for (int i = 0; i < n - 1; i ++)
    {
      // horizontal
      glPushMatrix();
        drawLines(i);
      glPopMatrix();
      glPushMatrix();
        glRotated(90, -1, 0, 0);
        drawLines(i);
      glPopMatrix();
      glPushMatrix();
        glRotated(90, 0, -1, 0);
        drawLines(i);
      glPopMatrix();

      // vertical
      glPushMatrix();
        glRotated(90, 0, 0, 1);
        glPushMatrix();
          drawLines(i);
        glPopMatrix();
        glPushMatrix();
          glRotated(90, -1, 0, 0);
          drawLines(i);
        glPopMatrix();
        glPushMatrix();
          glRotated(90, 0, -1, 0);
          drawLines(i);
        glPopMatrix();
      glPopMatrix();
    }
  }
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
    glTranslated(-3.5 + xOffset, 3.5 + yOffset, 0 + zOffset);
    glColor3ub(255 * (axis == 1), 255 * (axis == 2), 255 * (axis == 3));
    if (rotating) printText("Rotating: " + (string)(axis == 1 ? "x" : axis == 2 ? "y" : "z") + "-axis", 0, 0.5);
    glColor3ub(255, 255, 255);
    // printText("(" + to_string(xAngle) + ", " + to_string(yAngle) + ", " + to_string(zAngle) + ")", 0, -cubeSize / 2.0);
    printText("(" + to_string(orientation.u) + ", " + to_string(orientation.x) + ", " + to_string(orientation.y) + "," + to_string(orientation.z) + ")", 0, 0);
    glColor3ub(255, 255, 0); printText("number: " + to_string(number), -4.5, 0.5);
  glPopMatrix();

  drawSpaceVectors();

  glPushMatrix();
    orientation.fillMat4(rotationMatrix);
    glMultMatrixd(&rotationMatrix[0][0]);
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
  cube.initCube();
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
