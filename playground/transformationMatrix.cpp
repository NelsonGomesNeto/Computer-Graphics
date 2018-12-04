#ifndef _WIN32
  #if _WIN32
    #include <windows.h>
  #endif
#endif
#include <vector>
#include <string>
using namespace std;
#include <math.h>
#include <GL/freeglut.h>
struct Point
{
  double x, y;
  string to_string() { return("(" + std::to_string(x) + ", " + std::to_string(y) + ")"); }
};
double transformationMatrix[3][3];
Point mouse = {0, 0};
const int width = 800, height = 800, dx[4] = {0, 1, 1, 0}, dy[4] = {0, 0, 1, 1};
int plane = 2, planeScale = 20;
const double pi = acos(-1);
double degToRad(double a) { return(a*pi/180.0); }

string doubleToString(double number, int precision)
{
  double pot = pow(10, precision);
  int l = (int)(round(number * pot) / pot);
  int r = (number - l) * pot;
  return(to_string(l) + "." + to_string(r));
}
void printText(string s, double x, double y)
{
  glRasterPos2d(x, y);
  for (int i = 0; i < s.size(); i++) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
  glRasterPos2d(-x, -y);
}

double pointerVector[3];
double *transform(double t[3][3], vector<double> v)
{
  pointerVector[0] = pointerVector[1] = pointerVector[2] = 0;
  for (int i = 0; i < 1; i ++)
    for (int j = 0; j < 3; j ++)
      for (int k = 0; k < 3; k ++)
        pointerVector[j] += t[j][k] * v[k];
  return(pointerVector);
}

void readFromFile(string path)
{
  FILE *p = fopen(path.c_str(), "r");
  for (int i = 0; i < 3; i ++)
    for (int j = 0; j < 3; j ++)
      fscanf(p, "%lf", &transformationMatrix[i][j]);
  fclose(p);
}

void scheduleUpdate(int v)
{
  glutTimerFunc(10, scheduleUpdate, 1);
  readFromFile("./playground/transformationMatrix");
  glLoadIdentity();
    gluOrtho2D(width * (1 - dx[plane]), width * dx[plane], height * (1 - dy[plane]), height * dy[plane]);
  glutPostRedisplay();
}

void keyboardHandler(unsigned char key, int x, int y)
{
  if (key >= '1' && key <= '4') plane = key - '1';
}

void passiveMotionHandler(int x, int y)
{
  mouse.x = dx[plane] * x +  (1 - dx[plane]) * (width - x), mouse.y = dy[plane] * (height - y) + (1 - dy[plane]) * y;
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT); glClearColor(1, 1, 1, 1);

  glColor3ub(0, 0, 0);
  for (int i = -10*height; i < 10*height; i += planeScale)
  {
    glBegin(GL_LINES);
      glVertex2dv(transform(transformationMatrix, {(double)-10*width, (double)i, 1.0}));
      glVertex2dv(transform(transformationMatrix, {(double)10*width, (double)i, 1.0}));
    glEnd();
  }
  for (int j = -10*width; j < 10*width; j += planeScale)
  {
    glBegin(GL_LINES);
      glVertex2dv(transform(transformationMatrix, {(double)j, (double)-10*height, 1.0}));
      glVertex2dv(transform(transformationMatrix, {(double)j, (double)10*height, 1.0}));
    glEnd();
  }

  printText(mouse.to_string(), mouse.x, mouse.y);

  glColor3ub(255, 0, 0);
  glBegin(GL_TRIANGLE_FAN);
    glVertex2d(-20, -20); glVertex2d(-20, 20); glVertex2d(20, 20); glVertex2d(20, -20);
  glEnd();

  glColor3ub(255, 255, 255);
  glBegin(GL_TRIANGLE_FAN);
    glVertex2d(0, height - 110); glVertex2d(0, height); glVertex2d(width - 160, height); glVertex2d(width - 160, height - 110);
  glEnd();
  glColor3ub(0, 0, 255);
  glLineWidth(5);
  for (int i = 0; i < 3; i ++)
    for (int j = 0; j < 3; j ++)
      printText(doubleToString(transformationMatrix[i][j], 2), 60 * j, height - 30 * (i + 1));
  printText("(x, y) -> (" + doubleToString(transformationMatrix[0][0], 2) + "x + " + doubleToString(transformationMatrix[0][1], 2) + "y + " + doubleToString(transformationMatrix[0][2], 2) + ", " +
                       doubleToString(transformationMatrix[1][0], 2) + "x + " + doubleToString(transformationMatrix[1][1], 2) + "y + " + doubleToString(transformationMatrix[1][2], 2) + ")", 180, height - 60);
  glLineWidth(1);

  glFlush();
}

void init()
{
  gluOrtho2D(width * (1 - dx[plane]), width * dx[plane], height * (1 - dy[plane]), height * dy[plane]);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(800, 100);
    glutCreateWindow("Transformation Matrix Playground");
    init();

  glutDisplayFunc(display);
  glutTimerFunc(10, scheduleUpdate, 1);
  glutKeyboardFunc(keyboardHandler);
  glutPassiveMotionFunc(passiveMotionHandler);

  glutMainLoop();
}