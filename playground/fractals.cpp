#if _WIN32
  #ifndef _WIN32
    #include <windows.h>
  #endif
#endif
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>
#include <vector>
using namespace std;
const int width = 1000, height = 1000;
double transformationMatrix[3][3];

struct Point
{
  double x, y;
  void applyTransformation()
  {
    double xx = x, yy = y;
    x = transformationMatrix[0][0] * xx + transformationMatrix[0][1] * yy + transformationMatrix[0][2] * 1;
    y = transformationMatrix[1][0] * xx + transformationMatrix[1][1] * yy + transformationMatrix[1][2] * 1;
  }
  Point operator-(const Point &a) { return(Point({x - a.x, y - a.y})); }
};
double pixelSized2 = 0.5;

const double pi = acos(-1);
double degToRad(double angle) { return(angle * pi / 180.0); }
/* rotation formula
cos | -sin | x1 * (1 - cos) + y1 * sin
sin |  cos | y1 * (1 - cos) + x1 * sin
  0 |    0 |                         1
*/
void fillTransformationMatrix(double angle, Point p)
{
  double c = cos(angle), s = sin(angle);
  transformationMatrix[0][0] = c, transformationMatrix[0][1] = -s, transformationMatrix[0][2] = p.x * (1 - c) + p.y * s;
  transformationMatrix[1][0] = s, transformationMatrix[1][1] = c, transformationMatrix[1][2] = p.y * (1 - c) - p.x * s;
  transformationMatrix[2][0] = 0, transformationMatrix[2][1] = 0, transformationMatrix[2][2] = 1;
}
struct Fractal
{
  vector<Point> points;

  void translate(Point p) { for (Point &pi: points) pi.x += p.x, pi.y += p.y; }
  void rotate(double angle, Point p)
  {
    fillTransformationMatrix(angle, p);
    for (Point &pi: points) pi.applyTransformation();
  }
  void add(Fractal &piece) { for (Point &pi: piece.points) points.push_back(pi); }
};
Fractal fractal = {{{0, 0}, {1, 0}, {2, 0}}}, nextPiece;

void keyboardHandler(unsigned char key, int x, int y)
{
  switch (key)
  {
    case '+':
      nextPiece = fractal; nextPiece.translate(nextPiece.points[nextPiece.points.size() - 1] - nextPiece.points[0]);
      nextPiece.rotate(degToRad(90), nextPiece.points[0]);
      fractal.add(nextPiece);
      break;
    case 'c': nextPiece = fractal; nextPiece.translate(nextPiece.points[nextPiece.points.size() - 1] - nextPiece.points[0]); break;
    case 'r': nextPiece.rotate(degToRad(90), nextPiece.points[0]); break;
    case 'p': fractal.add(nextPiece); break;
    default: break;
  }
  glutPostRedisplay();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();
    glColor3ub(255, 255, 255);
    glTranslated(width / 2.0, height / 2.0, 0);
    for (Point &pi: fractal.points)
    {
      glRectd(pi.x - pixelSized2, pi.y - pixelSized2, pi.x + pixelSized2, pi.y + pixelSized2);
      // printf("(%3.3lf, %3.3lf)\n", pi.x, pi.y);
    }
  glPopMatrix();

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
    glutInitWindowPosition(400, 0);
    glutCreateWindow("Fractals");
    init();
  glutKeyboardFunc(keyboardHandler);
  glutDisplayFunc(display);
  glutMainLoop();
}