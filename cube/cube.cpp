#include <GL/freeglut.h>
#include <vector>
using namespace std;

const int width = 600, height = 600;
struct Piece { int color[6]; }; // 0 - face, 1 - top, 2 - back, 3 - down, 4 - left, 5 - right
struct Cube { vector<vector<vector<Piece>>> pieces; };
Cube cube;
Cube newCube(const int n)
{
  Cube temp;
  for (int i = 0; i < n; i ++)
  {
    temp.pieces.push_back(vector<vector<Piece>>());
    for (int j = 0; j < n; j ++)
    {
      temp.pieces[i].push_back(vector<Piece>());
      for (int k = 0; k < n; k ++) temp.pieces[i][j].push_back({0, 1, 2, 3, 4, 5});
    }
  }
}

void display()
{
  pushMatrix();
    glTranslated();
    glutSolidCube(50);
  popMatrix();
}

void init()
{
  gluOrtho2D(0, width, height, 0);
  glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near_val, GLdouble far_val);
}

int main(int argc, char **argv)
{
  cube = newCube(3);

  glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 0);
    glutCreateWindow("Gravity");
    init();
  glutDisplayFunc(display);
  // glutTimerFunc(10, scheduleUpdate, 1);
  // glutKeyboardFunc(keyboardHandler);
  // glutPassiveMotionFunc(passiveMotionHandler);
  glutMainLoop();
}
