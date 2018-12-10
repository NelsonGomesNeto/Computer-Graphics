#if _WIN32
  #ifndef _WIN32
    #include <windows.h>
  #endif
#endif
#include <vector>
#include <string>
using namespace std;
#include <math.h>
#include <GL/freeglut.h>
const int width = 800, height = 800;
const double pi = acos(-1), tau = 2 * acos(-1), gravitationConstant = 1;
double degToRad(double a) { return(a*pi/180.0); }
struct Point
{
  double x, y;
  Point operator+(const Point &a) { return(Point({x + a.x, y + a.y})); }
  Point operator-(const Point &a) { return(Point({x - a.x, y - a.y})); }
  Point operator-() { return(Point({-x, -y})); }
  Point operator*(const double a) { return(Point({x * a, y * a})); }
  Point operator/(const double a) { return(Point({x / a, y / a})); }
  void operator+=(const Point &a) { x += a.x, y += a.y; }
};
double distance(Point a, Point b) { return(sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2))); }
struct Object { Point position, speed, acceleration; double mass; };
Point mouse;
Object sun = {{400, 400}, {0, 0}, {0, 0}, 1000};
vector<Object> planets;
bool addingPlanet = false; Point startingPoint;

void printText(string s, double x, double y)
{
  glRasterPos2d(x, y);
  for (int i = 0; i < s.size(); i++) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
  glRasterPos2d(-x, -y);
}

void passiveMotionHandler(int x, int y)
{
  mouse.x = x, mouse.y = y;
}

void keyboardHandler(unsigned char key, int x, int y)
{
  switch (key)
  {
    case '1': sun.mass += 10;
      break;
    case '2': sun.mass -= 10;
      break;
    case 'a':
      if (!addingPlanet) startingPoint = {(double) x, (double) y};
      else planets.push_back({startingPoint, -(Point({(double) x, (double) y}) - startingPoint) / 10, {0, 0}, 1});
      addingPlanet = !addingPlanet;
      break;
    case 's':
      planets.pop_back();
      break;
    default:
      break;
  }
}

void scheduleUpdate(int v)
{
  glutTimerFunc(10, scheduleUpdate, 1);
  // ||d|| = d / sqrt(d.x^2 + d.y^2)
  // Gravitational Force = G * m1 * m2 / d^2 * ||d|| = G * m1 * m2 / d^1.5 * unitary(d.x, d.y)
  // Force = mass * acceleration
  // acceleration = Force / mass

  sun.acceleration = {0, 0};
  for (int i = 0; i < planets.size(); i ++)
  {
    double d = distance(planets[i].position, sun.position);
    double force = gravitationConstant * planets[i].mass * sun.mass / pow(d, 1.5);
    planets[i].acceleration = ((sun.position - planets[i].position) / d) * force / planets[i].mass;
    sun.acceleration += ((planets[i].position - sun.position) / d) * force / sun.mass;
    for (int j = 0; j < planets.size(); j ++)
    {
      if (i == j) continue;
      d = distance(planets[i].position, planets[j].position);
      force = gravitationConstant * planets[i].mass * planets[j].mass / pow(d, 1.5);
      planets[i].acceleration += ((planets[j].position - planets[i].position) / d) * force / planets[i].mass;
    }
    planets[i].speed += planets[i].acceleration;
    planets[i].position += planets[i].speed;
  }
  sun.speed += sun.acceleration;
  sun.position += sun.speed;

  glutPostRedisplay();
}

void drawCircle(Point position, int radious, int triangles)
{
  glBegin(GL_TRIANGLE_FAN);
    glVertex2d(position.x, position.y);
    for (int i = 0; i <= triangles; i ++)
      glVertex2d(position.x + radious * cos((double) i / triangles * tau), position.y + radious * sin((double) i / triangles * tau));
  glEnd();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  // printText("sun.mass: " + to_string(sunAux.mass) + " earth.position.x: " + to_string(earthAux.position.x) + " earth.speed.y: " + to_string(earthAux.speed.y), 0, height - 100);
  printText("planets: " + to_string(planets.size()), 0, 50);

  drawCircle(sun.position, 50, 10);
  for (Object planet: planets) drawCircle(planet.position, 10, 10);

  if (addingPlanet)
  {
    drawCircle(startingPoint, 10, 10);
    glColor3ub(0, 0, 255);
    glLineWidth(5);
    glBegin(GL_LINES);
      glVertex2d(startingPoint.x, startingPoint.y);
      glVertex2d(mouse.x, mouse.y);
    glEnd();
    printText("(" + to_string((mouse.x - startingPoint.x) / 10) + ", " + to_string((mouse.y - startingPoint.y) / 10) + ")", (mouse.x + startingPoint.x) / 2.0, (mouse.y + startingPoint.y) / 2.0);
    glColor3ub(255, 255, 255);
  }

  glFlush();
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
    glutInitWindowPosition(400, 100);
    glutCreateWindow("Gravity");
    init();
  glutDisplayFunc(display);
  glutTimerFunc(10, scheduleUpdate, 1);
  glutKeyboardFunc(keyboardHandler);
  glutPassiveMotionFunc(passiveMotionHandler);
  glutMainLoop();
}
