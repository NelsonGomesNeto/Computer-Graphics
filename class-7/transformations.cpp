#include <GL/freeglut.h>

const int width = 800, height = 800;
int year = 0, day = 0;

void keyboardHandler(unsigned char key, int x, int y)
{
  switch (key)
  {
    case 'd':
      day = (day + 10) % 360;
      glutPostRedisplay();
      break;
    case 'D':
      day = (day - 10) % 360;
      glutPostRedisplay();
      break;
    case 'y':
      year = (year + 5) % 360;
      glutPostRedisplay();
      break;
    case 'Y':
      year = (year - 5) % 360;
      glutPostRedisplay();
      break;
    case 27:
      exit(0);
      break;
    default:
      break;
  }
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1, 1, 1);

  glPushMatrix();
    glRotatef(year, 1, 0, 0);
    glRotatef(day, 0, 0, 1);
    glutWireSphere(1, 20, 16);
  glPopMatrix();

  glPushMatrix();
    glRotatef(year, 0, 1, 0);
    glTranslatef(2, 0, 0);
    glRotatef(day, 0, 1, 0);
    glutWireSphere(0.2, 10, 8);
  glPopMatrix();

  glutSwapBuffers();
}

void init()
{
  glClearColor(0, 0, 0, 0);
  // glViewport(0, 0, width, height);
}

void reshape(int w, int h)
{
  glViewport(0, 0, w, h);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluPerspective(60, (double) w / h, 1, 20);
  gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(width, height);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Rotação de Planetas");

  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboardHandler);
  glutMainLoop();
  return(0);
}
