#include <GL/freeglut.h>
#include <stdio.h>

const int width = 800, height = 800;
int year = 0, day = 0;
GLfloat lightSpotCutoff = 10, attenuation = 0.25;
double lx = 0, ly = 0, lz = 0, yAngle = 0;

void scheduleUpdate(int value)
{
  glutTimerFunc(10, scheduleUpdate, 1);
  // day += 50;
  // if (day >= 360) year += 1, day %= 360;
  printf("%8.3lf %8.3lf %8.3lf || %8.3lf\n", lx, ly, lz, yAngle);
  day ++, year ++;
  glutPostRedisplay();
}

void keyboardHandler(unsigned char key, int x, int y)
{
  switch (key)
  {
    case 'w': lz -= 0.1; break;
    case 's': lz += 0.1; break;
    case 'a': lx -= 0.1; break;
    case 'd': lx += 0.1; break;
    case 'r': ly += 0.1; break;
    case 'f': ly -= 0.1; break;
    case '1':
      attenuation += 0.01;
      break;
    case '2':
      attenuation -= 0.01;
      break;
    case '3':
      yAngle += 1;
      break;
    case '4':
      yAngle -= 1;
      break;
    case 27:
      exit(0);
      break;
    default:
      break;
  }
}

void lightsSetup()
{
  GLfloat materialAmbientAndDiffuse[] = {1, 1, 1, 1};
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialAmbientAndDiffuse); // Defines objects reflection to ambient and diffuse light
  GLfloat materialSpecular[] = {1, 1, 1, 1};
  glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular); // Defines objects reflection to specular light
  glMaterialf(GL_FRONT, GL_SHININESS, 50); // Defines objects level of reflection (0 to 128)
  GLfloat lightAmbient[] = {0.2, 0.2, 0.2, 1}; glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
  GLfloat lightDiffuse[] = {1.0, 1.0, 1.0, 1}; glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
  GLfloat lightSpecular[] = {1.0, 1.0, 1.0, 1}; glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
  // glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, lightSpotCutoff);
  glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, attenuation);
  GLfloat lightPosition[] = {0, 0, 0, 1};
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void drawSolarSystem()
{
  // Sun
  glPushMatrix();
    glColor3ub(255, 127, 80);
    glRotatef(year, 1, 0, 0);
    glRotatef(day, 0, 0, 1);
    glutSolidSphere(0.5, 100, 100);
  glPopMatrix();

  // Planet 1
  glPushMatrix();
    glColor3ub(255, 255, 0);
    glRotatef(year, 0, 1, 0);
    glTranslatef(2, 0, 0);
    glPushMatrix();
      glRotatef(day, 0, 1, 0);
      glutSolidSphere(0.1, 100, 100); // Planet 1
    glPopMatrix();

    glPushMatrix();
      glColor3ub(255, 0, 0);
      glRotatef(1.25*day, 0, 0, 1);
      glTranslatef(0.2, 0, 0);
      glutSolidSphere(0.05, 100, 100); // Moon 1
    glPopMatrix();

    glPushMatrix();
      glColor3ub(0, 255, 0);
      glRotatef(1.5*day, 0, 1, 0);
      glTranslatef(0.4, 0, 0);
      glutSolidSphere(0.025, 100, 100); // Moon 2
    glPopMatrix();

    glPushMatrix();
      glColor3ub(0, 0, 255);
      glRotatef(1.75*day, 0, 1, 1);
      glTranslatef(0.3, 0, 0);
      glutSolidSphere(0.025, 100, 100); // Moon 3
    glPopMatrix();
  glPopMatrix();

  // Planet 2
  glPushMatrix();
    glColor3ub(0, 255, 255);
    glRotatef(2*year, 0, -1, 0);
    glTranslatef(1, 0, 0);
    glRotatef(2*day, 0, 1, 0);
    glutSolidSphere(0.1, 10, 8); // Planet 2
  glPopMatrix();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // glLoadIdentity();
  // gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

  glPushMatrix();
    // Light source
    glPushMatrix();
      glRotated(yAngle, 0, 1, 0);
      glColor3ub(255, 255, 255);
      glTranslated(lx, ly, lz);
      lightsSetup();
      glutSolidSphere(0.05, 100, 100);
    glPopMatrix();

    drawSolarSystem();
  glPopMatrix();


  glutSwapBuffers();
}

void init()
{
  glEnable(GL_DEPTH_TEST);
  glClearColor(0, 0, 0, 0);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
  glShadeModel(GL_SMOOTH);
}

void reshape(int w, int h)
{
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  gluPerspective(60, (double) w / h, 1, 20);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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
