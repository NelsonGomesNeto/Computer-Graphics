#ifndef _WIN32
#include <windows.h>
#endif
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
#include <stdio.h>
#include <math.h>
#include "./../rainbow.h"
#include <GL/freeglut.h>
const double pi = acos(-1), gravity = 100, gravityConstant = 160000.0;
const int width = 800, height = 800;
double degToRad(double a) { return (a * pi / 180.0); }
struct Vector
{
  double x, y;
};
double distance(Vector a, Vector b) { return (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2))); }
struct Block
{
  double x, y, width, height;
  Vector speed, acceleration;
};
int cornerDx[4] = {1, 1, -1, -1}, cornerDy[4] = {-1, 1, 1, -1};
vector<Block> blocks;
Vector speed = {10, 0};
vector<Vector> waves; // will be a vector of forces, which can be added by clicking (force will be mouse.y and position will be mouse.x)

void printText(string s, double x, double y)
{
  glRasterPos2d(x, y);
  for (int i = 0; i < s.size(); i++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
  glRasterPos2d(-x, -y);
}

void mouseHandler(int button, int state, int x, int y)
{
  if (state == GLUT_DOWN)
    waves.push_back({(double)x, (double)y / height * 150.0 * (button == GLUT_LEFT_BUTTON ? 1 : -1)});
  printf("Mouse(%s): %d | mouse: (%d, %d)\n", state == GLUT_DOWN ? "down" : "up", button, x, y);
}

void keyboardHandler(unsigned char key, int x, int y)
{
  switch (key)
  {
  case '1':
    blocks.push_back({0});
    for (int i = 0; i < blocks.size(); i++)
      blocks[i] = {width * (double)(i + 1) / (blocks.size() + 1), 100, 50, 50, {2, 0}, {0, -gravity}};
    break;
  case '2':
    if (blocks.size())
      blocks.pop_back();
    for (int i = 0; i < blocks.size(); i++)
      blocks[i] = {width * (double)(i + 1) / (blocks.size() + 1), 100, 50, 50, {2, 0}, {0, -gravity}};
    break;
  default:
    break;
  }
  printf("Keyboard: %c | mouse: (%d, %d)\n", key, x, y);
}
void specialHandler(int key, int x, int y)
{
  printf("Special: %d | mouse: (%d, %d)\n", key, x, y);
}

void scheduleUpdate(int v)
{
  for (int i = 0; i < blocks.size(); i++)
  { // Force = mass * acceleration
    blocks[i].acceleration.y = -gravity - blocks[i].speed.y;
    for (int j = 0; j < waves.size(); j++)
      blocks[i].acceleration.y += gravityConstant * waves[j].y / pow(distance({blocks[i].x, blocks[i].y}, {waves[j].x, -100}), 2);

    blocks[i].speed.y += blocks[i].acceleration.y;

    blocks[i].x = (int)(blocks[i].x + blocks[i].speed.x) % width, blocks[i].y += blocks[i].speed.y;
    if (blocks[i].y < 100)
      blocks[i].y = 100, blocks[i].speed.y = 0;
    if (blocks[i].y > height - blocks[i].height / 2.0)
      blocks[i].y = height - blocks[i].height / 2.0, blocks[i].speed.y = 0;
  }
  glutTimerFunc(10, scheduleUpdate, 1);
  glutPostRedisplay();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3ub(255, 255, 255);
  printText("Blocks: " + to_string(blocks.size()) + " Waves: " + to_string(waves.size()), 100, height - 100);

  if (blocks.size())
    for (int i = 0, ac = 0, sc = rainbowSize / min(blocks.size(), rainbowSize); i < blocks.size(); i++, ac += sc)
    {
      glBegin(GL_QUADS);
      glColor3dv(rainbowArray[ac % rainbowSize]);
      for (int k = 0; k < 4; k++)
        glVertex2d(blocks[i].x + blocks[i].width / 2.0 * cornerDx[k], blocks[i].y + blocks[i].height / 2.0 * cornerDy[k]);
      glEnd();
      glColor3ub(255, 255, 255);
      printText(to_string(blocks[i].acceleration.y), blocks[i].x - 25, blocks[i].y + 10);
      printText(to_string(blocks[i].speed.y), blocks[i].x - 25, blocks[i].y - 20);
    }

  glFlush();
}

void init()
{
  gluOrtho2D(0, width, 0, height);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(width, height);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Input");
  init();
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboardHandler);
  glutSpecialFunc(specialHandler);
  glutMouseFunc(mouseHandler);
  glutTimerFunc(10, scheduleUpdate, 1);
  glutMainLoop();
}