#include <GL/freeglut.h>
#include <vector>

const int width = 600, height = 600;
// {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}, {4, 4, 4}}

void display()
{

}

void init()
{
  gluOrtho2D(0, width, height, 0);
}

int main(int argc, char **argv)
{
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