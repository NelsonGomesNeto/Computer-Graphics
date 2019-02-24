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
bool specialKeyPressed[256], keyPressed[256];
const int width = 800, height = 800;
double distanceX = 0, distanceZ = 90, distanceBase = 90, maxSpeed = 0.5;
struct Point
{
  double x, y, z;
  Point operator+(const Point &a) { return(Point({x + a.x, y + a.y, z + a.z})); }
  void operator+=(const Point &a) { x += a.x, y += a.y, z += a.z; }
  void operator*=(const double a) { x *= a, y *= a, z *= a; }
  void limit(double l)
  {
    double mag = sqrt(x*x + y*y + z*z);
    if (mag > 1e-5)
      x *= l / mag, y *= l / mag, z *= l / mag;
  }
  void print()
  {
    printf("%.3lf %.3lf %.3lf\n", x, y, z);
  }
};
struct Camera
{
  Point position, speed, acceleration;
  double angle = 0, cosAngle = 1, sinAngle = 0, angularSpeed = 0, angularAcceleration = 0;
  void getMovement()
  {
    if (specialKeyPressed[GLUT_KEY_UP] || specialKeyPressed[GLUT_KEY_DOWN] || specialKeyPressed[GLUT_KEY_RIGHT] || specialKeyPressed[GLUT_KEY_LEFT])
    {
      if (specialKeyPressed[GLUT_KEY_UP])
        acceleration.z += +0.05 * cosAngle, acceleration.x += +0.05 * sinAngle;
      if (specialKeyPressed[GLUT_KEY_DOWN])
        acceleration.z += -0.05 * cosAngle, acceleration.x += -0.05 * sinAngle;
      if (specialKeyPressed[GLUT_KEY_RIGHT])
        acceleration.x += -0.05 * cosAngle, acceleration.z += +0.05 * sinAngle;
      if (specialKeyPressed[GLUT_KEY_LEFT])
        acceleration.x += +0.05 * cosAngle, acceleration.z += -0.05 * sinAngle;
      acceleration.limit(0.05);
    }
    else acceleration *= 0.0, speed *= 0.0;

    if (keyPressed['q'] || keyPressed['w'])
    {
      if (keyPressed['q'])
        angularAcceleration = +0.001;
      if (keyPressed['w'])
        angularAcceleration = -0.001;
    }
    else angularAcceleration = angularSpeed = 0;

    if (keyPressed['y'])
      position.y -= 0.50;
    if (keyPressed['Y'])
      position.y += 0.50;
    if (keyPressed['c'])
      angle = 0;
  }
  void update()
  {
    speed += acceleration;
    speed.limit(maxSpeed);
    position += speed;
    angularSpeed += angularAcceleration;
    angularSpeed = angularSpeed < -0.04 ? -0.04 : angularSpeed > 0.04 ? 0.04 : angularSpeed;
    angle += angularSpeed;
    if (angularSpeed != 0)
    {
      cosAngle = cos(angle), sinAngle = sin(angle);
      distanceX = sinAngle * distanceBase, distanceZ = cosAngle * distanceBase;
    }
    // printf("speed: "); speed.print();
    // printf("position: "); position.print();
  }
};
Camera camera = {{0, 0, -90}, {0, 0, 0}, {0, 0, 0}};
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

void specialFuncHandler(int key, int x, int y) { specialKeyPressed[key] = true; }
void specialFuncUpHandler(int key, int x, int y) { specialKeyPressed[key] = false; }
void keyboardHandler(unsigned char key, int x, int y) { keyPressed[key] = true; }
void keyboardUpHandler(unsigned char key, int x, int y) { keyPressed[key] = false; }

void scheduleUpdate(int value)
{
  glutTimerFunc(10, scheduleUpdate, 1);
  loadVertices();
  camera.getMovement();
  camera.update();
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
  gluLookAt(camera.position.x, camera.position.y, camera.position.z,
            camera.position.x + distanceX, camera.position.y, camera.position.z + distanceZ,
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
  glutKeyboardUpFunc(keyboardUpHandler);
  glutSpecialFunc(specialFuncHandler);
  glutSpecialUpFunc(specialFuncUpHandler);
  glutMainLoop();
}
