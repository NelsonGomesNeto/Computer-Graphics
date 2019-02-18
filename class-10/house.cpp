#if _WIN32
  #ifndef _WIN32
    #include <windows.h>
  #endif
#endif
#include <stdio.h>
#include <GL/freeglut.h>
#include <algorithm>
using namespace std;
const int width = 800, height = 800;
int xAngle, yAngle;
struct Point { double x, y, z; };
vector<Point> vertices;
static GLubyte frenteIndices[]    = {0,4,3,2,1};
static GLubyte trasIndices[]      = {5,6,7,8};
static GLubyte esquerdaIndices[]  = {0,5,8,4};
static GLubyte direitaIndices[]   = {2,3,7,10};
static GLubyte topoIndices[]      = {0,1,9,6,5};
static GLubyte fundoIndices[]     = {3,4,8,7};
static GLubyte trianguloIndices[] = {12,13,14};
#define AZUL     0.0, 0.0, 1.0
#define VERMELHO 1.0, 0.0, 0.0
#define AMARELO  1.0, 1.0, 0.0
#define VERDE    0.0, 1.0, 0.0
#define CYAN     1.0, 0.0, 1.0
#define LARANJA  0.8, 0.6, 0.1
#define ROSEO    0.7, 0.1, 0.6
#define CINZA    0.6, 0.6, 0.6

void loadVertices()
{
  FILE *file = fopen("class-10/in", "r");
  double x, y, z;
  vertices.clear();
  while (fscanf(file, "%lf %lf %lf", &x, &y, &z) != EOF)
    vertices.push_back({x, y, z});
  fclose(file);
}

void keyboardHandler(unsigned char key, int x, int y)
{
  switch (key)
  {
    case 'q':
      xAngle = (xAngle + 5) % 360;
      break;
    case 'w':
      yAngle = (yAngle + 5) % 360;
      break;
    case 'Q':
      xAngle = (xAngle - 5) % 360;
      break;
    case 'W':
      yAngle = (yAngle - 5) % 360;
      break;
    default:
      break;
  }
  glutPostRedisplay();
}


void scheduleUpdate(int value)
{
  glutTimerFunc(10, scheduleUpdate, 1);
  loadVertices();
  glutPostRedisplay();
}

void drawPolygon(GLubyte indexes[], int size)
{
  if (size > vertices.size()) return;
  glBegin(GL_POLYGON);
  for (int i = 0; i < size; i ++)
    glVertex3d(vertices[indexes[i]].x, vertices[indexes[i]].y, vertices[indexes[i]].z);
  glEnd();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
    glRotated(yAngle, 0, 1, 0);
    glRotated(xAngle, 1, 0, 0);
    glColor3f (AZUL); /* frente */
    drawPolygon(frenteIndices, 5);

    glColor3f (AMARELO); /* esquerda */
    drawPolygon(esquerdaIndices, 4);

    glColor3f (VERMELHO); /* tras */
    drawPolygon(trasIndices, 4);

    glColor3f (VERDE); /* direita */
    drawPolygon(direitaIndices, 4);

    glColor3f (CYAN); /* topo */
    drawPolygon(topoIndices, 5);

    glColor3f (LARANJA); /* fundo */
    drawPolygon(fundoIndices, 4);

    glColor3f (CINZA); /* triangulo */
    drawPolygon(trianguloIndices, 3);
    glPushMatrix();
      glTranslated(vertices[11].x, vertices[11].y, vertices[11].z);
      for (int i = 0; i < 3; i ++)
      {
        glRotated(90, 0, 1, 0);
        drawPolygon(trianguloIndices, 3);
      }
    glPopMatrix();
  glPopMatrix();

  glutSwapBuffers();
}

void init()
{
  loadVertices();
  glClearColor(0, 0, 0, 0);
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluPerspective(65.0, (GLfloat) width/(GLfloat) height, 20.0, 120.0);
    gluLookAt(0, 0, -90, 0, 0, 0, 0, 1, 0);
  // gluPerspective(60, (double) width / height, 1, 20);
  // gluLookAt(5, 5, 6, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(400, 100);
    glutCreateWindow("House");
    init();
  glutDisplayFunc(display);
  glutTimerFunc(10, scheduleUpdate, 1);
  glutKeyboardFunc(keyboardHandler);
  glutMainLoop();
}
