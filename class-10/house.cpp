#if _WIN32
  #ifndef _WIN32
    #include <windows.h>
  #endif
#endif
#include <stdio.h>
#include <GL/freeglut.h>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;
const int width = 800, height = 800;
double angle = 0, distanceX = 0, distanceZ = 90, distanceBase = 90;
struct Point { double x, y, z; };
Point camera = {0, 0, -90};
vector<Point> vertices;
static GLubyte frenteIndices[]    = {0,4,3,2};
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

void specialFuncHandler(int key, int x, int y)
{
  switch (key)
  {
    case GLUT_KEY_UP:
      camera.z += 2 * cos(angle);
      camera.x += 2 * sin(angle);
      break;
    case GLUT_KEY_DOWN:
      camera.z -= 2 * cos(angle);
      camera.x -= 2 * sin(angle);
      break;
    case GLUT_KEY_RIGHT:
      camera.x -= 2 * cos(angle);
      camera.z += 2 * sin(angle);
      break;
    case GLUT_KEY_LEFT:
      camera.x += 2 * cos(angle);
      camera.z -= 2 * sin(angle);
      break;
    default:
      break;
  }
}

void keyboardHandler(unsigned char key, int x, int y)
{
  switch (key)
  {
    case 'q':
      angle += 0.05;
      break;
    case 'w':
      angle -= 0.05;
      break;
    case 'y':
      camera.y -= 0.50;
      break;
    case 'Y':
      camera.y += 0.50;
      break;
    case 'c':
      angle = 0;
      break;
    default:
      break;
  }
  distanceX = sin(angle) * distanceBase;
  distanceZ = cos(angle) * distanceBase;
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

  glColor3ub(0, 0, 0);
  // glLineWidth(10);
  glBegin(GL_LINES);
    for (int i = 0; i < size; i ++)
    {
      glVertex3d(vertices[indexes[i]].x, vertices[indexes[i]].y, vertices[indexes[i]].z);
      glVertex3d(vertices[indexes[(i+1)%size]].x, vertices[indexes[(i+1)%size]].y, vertices[indexes[(i+1)%size]].z);
    }
  glEnd();
}

void drawHouse()
{
  glPushMatrix();
    // glRotated(yAngle, 0, 1, 0);
    // glRotated(angle, 1, 0, 0);
    glTranslated(-vertices[11].x, -vertices[11].y / 2.0, -vertices[11].z);
    glColor3f (AZUL); /* frente */
    drawPolygon(frenteIndices, 4);

    glColor3f (AMARELO); /* esquerda */
    drawPolygon(esquerdaIndices, 4);

    glColor3f (VERMELHO); /* tras */
    drawPolygon(trasIndices, 4);

    glColor3f (VERDE); /* direita */
    drawPolygon(direitaIndices, 4);

    glColor3f (LARANJA); /* fundo */
    drawPolygon(fundoIndices, 4);

    glPushMatrix();
      glTranslated(vertices[11].x, vertices[11].y, vertices[11].z);
      for (int i = 0; i < 4; i ++)
      {
        glColor3f (CINZA); /* triangulo */
        drawPolygon(trianguloIndices, 3);
        glRotated(90, 0, 1, 0);
      }
    glPopMatrix();
  glPopMatrix();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  gluPerspective(65.0, (GLfloat) width/(GLfloat) height, 20.0, 180.0);
  gluLookAt(camera.x, camera.y, camera.z,
            camera.x + distanceX, camera.y, camera.z + distanceZ,
            0, 1, 0);

  drawHouse();

  glFlush();
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
  glutSpecialFunc(specialFuncHandler);
  glutMainLoop();
}
