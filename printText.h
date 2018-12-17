#include <GL/freeglut.h>
#include <string>
using namespace std;

void printText(string s, double x, double y)
{
  glRasterPos2d(x, y);
  for (int i = 0; i < s.size(); i++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
  glRasterPos2d(-x, -y);
}