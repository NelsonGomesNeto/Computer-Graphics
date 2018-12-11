#include <GL/freeglut.h>

const int width = 800, height = 800;
int year = 0, day = 0;

void scheduleUpdate(int value)
{
  glutTimerFunc(10, scheduleUpdate, 1);
  // day += 50;
  // if (day >= 360) year += 1, day %= 360;
  day ++, year ++;
  glutPostRedisplay();
}

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

  // Sun
  glPushMatrix();
    glRotatef(year, 1, 0, 0);
    glRotatef(day, 0, 0, 1);
    glutWireSphere(0.5, 20, 16);
  glPopMatrix();

  // Planet 1
  glPushMatrix();
    glRotatef(year, 0, 1, 0);
    glTranslatef(2, 0, 0);
    glPushMatrix();
      glRotatef(day, 0, 1, 0);
      glutWireSphere(0.1, 10, 8);
    glPopMatrix();

    glPushMatrix();
      glColor3ub(255, 0, 0);
      glRotatef(1.25*day, 0, 0, 1); // Moon 1
      glTranslatef(0.2, 0, 0);
      glutWireSphere(0.05, 10, 8);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(0, 255, 0);
      glRotatef(1.5*day, 0, 1, 0); // Moon 2
      glTranslatef(0.4, 0, 0);
      glutWireSphere(0.025, 10, 8);
    glPopMatrix();

    glPushMatrix();
      glColor3ub(0, 0, 255);
      glRotatef(1.75*day, 0, 1, 1); // Moon 3
      glTranslatef(0.3, 0, 0);
      glutWireSphere(0.025, 10, 8);
    glPopMatrix();
  glPopMatrix();

  // Planet 2
  glPushMatrix();
    glColor3ub(255, 255, 255);
    glRotatef(2*year, 0, -1, 0);
    glTranslatef(1, 0, 0);
    glRotatef(2*day, 0, 1, 0);
    glutWireSphere(0.1, 10, 8);
  glPopMatrix();

  glutSwapBuffers();
}

void init()
{
  glClearColor(0, 0, 0, 0);
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
  glutTimerFunc(10, scheduleUpdate, 1);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboardHandler);
  glutMainLoop();
  return(0);
}
