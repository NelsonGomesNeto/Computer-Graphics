#include <time.h>
// 0 - face, 1 - top, 2 - back, 3 - down, 4 - left, 5 - right
struct Piece { int color[6] = {0, 1, 2, 3, 4, 5}; };
const double colorMap[6][3] = {{1, 1, 1}, {0, 0, 1}, {1, 241 / 255.0, 25 / 255.0}, {0, 1, 0}, {253 / 255.0, 126 / 255.0, 0}, {1, 0, 0}};
const int n = 3; const int cycleSize = 2*n + 2*(n - 2);
struct Cube { int face[6][n][n]; void initCube() { for (int i = 0; i < 6; i ++) for (int j = 0; j < n; j ++) for (int k = 0; k < n; k ++) face[i][j][k] = i; } };

void rotateFace(int face[n][n], bool reverse)
{
  for (int k = 0; k < n / 2; k ++)
  {
    if (reverse)
      for (int i = 0; i < n - 1 - 2 * k; i ++)
      {
        int aux = face[0 + k][i + k];
        face[0 + k][i + k] = face[i + k][n - 1 - k];
        face[i + k][n - 1 - k] = face[n - 1 - k][n - 1 - i - k];
        face[n - 1 - k][n - 1 - i - k] = face[n - 1 - i - k][0 + k];
        face[n - 1 - i - k][0 + k] = aux;
      }
    else
      for (int i = 0; i < n - 1 - 2 * k; i ++)
      {
        int aux = face[0 + k][i + k];
        face[0 + k][i + k] = face[n - 1 - i - k][0 + k];
        face[n - 1 - i - k][0 + k] = face[n - 1 - k][n - 1 - i - k];
        face[n - 1 - k][n - 1 - i - k] = face[i + k][n - 1 - k];
        face[i + k][n - 1 - k] = aux;
      }
  }
}

void moveR(Cube &c, int number, bool reverse)
{
  if (reverse)
    for (int i = 0; i < n; i ++)
    {
      int aux = c.face[0][n - 1 - i][number];
      c.face[0][n - 1 - i][number] = c.face[1][n - 1 - i][number];
      c.face[1][n - 1 - i][number] = c.face[2][i][number];
      c.face[2][i][number] = c.face[3][i][number];
      c.face[3][i][number] = aux;
    }
  else
    for (int i = 0; i < n; i ++)
    {
      int aux = c.face[3][i][number];
      c.face[3][i][number] = c.face[2][i][number];
      c.face[2][i][number] = c.face[1][n - 1 - i][number];
      c.face[1][n - 1 - i][number] = c.face[0][n - 1 - i][number];
      c.face[0][n - 1 - i][number] = aux;
    }
  if (number == 0) rotateFace(c.face[5], reverse);
  if (number == n - 1) rotateFace(c.face[4], reverse);
}

void moveU(Cube &c, int number, bool reverse)
{
  if (reverse)
    for (int i = 0; i < n; i ++)
    {
      int aux = c.face[0][number][i];
      c.face[0][number][i] = c.face[4][number][i];
      c.face[4][number][i] = c.face[2][number][n - 1 - i];
      c.face[2][number][n - 1 - i] = c.face[5][number][n - 1 - i];
      c.face[5][number][n - 1 - i] = aux;
    }
  else
    for (int i = 0; i < n; i ++)
    {
      int aux = c.face[5][number][n - 1 - i];
      c.face[5][number][n - 1 - i] = c.face[2][number][n - 1 - i];
      c.face[2][number][n - 1 - i] = c.face[4][number][i];
      c.face[4][number][i] = c.face[0][number][i];
      c.face[0][number][i] = aux;
    }
  if (number == 0) rotateFace(c.face[1], !reverse);
  if (number == n - 1) rotateFace(c.face[3], !reverse);
}

void moveF(Cube &c, int number, bool reverse)
{
  if (reverse)
    for (int i = 0; i < n; i ++)
    {
      int aux = c.face[1][n - 1 - number][i];
      c.face[1][n - 1 - number][i] = c.face[5][n - 1 - i][number];
      c.face[5][n - 1 - i][number] = c.face[3][n - 1 - number][n - 1 - i];
      c.face[3][n - 1 - number][n - 1 - i] = c.face[4][i][number];
      c.face[4][i][number] = aux;
    }
  else
    for (int i = 0; i < n; i ++)
    {
      int aux = c.face[5][n - 1 - i][number];
      c.face[5][n - 1 - i][number] = c.face[1][n - 1 - number][i];
      c.face[1][n - 1 - number][i] = c.face[4][i][number];
      c.face[4][i][number] = c.face[3][n - 1 - number][n - 1 - i];
      c.face[3][n - 1 - number][n - 1 - i] = aux;
    }
  if (number == 0) rotateFace(c.face[0], !reverse);
  if (number == n - 1) rotateFace(c.face[2], !reverse);
}

void moveCube(Cube &c, unsigned char key, int number)
{
  switch (key)
  {
    case 'R': moveR(c, number, (number > n / 2) - false); break;
    case 'r': moveR(c, number, (number > n / 2) - true); break;

    case 'U': moveU(c, number, (number > n / 2) - false); break;
    case 'u': moveU(c, number, (number > n / 2) - true); break;

    case 'F': moveF(c, number, (number > n / 2) - false); break;
    case 'f': moveF(c, number, (number > n / 2) - true); break;
    default: break;
  }
}

void randomScramble(Cube &c)
{
  srand(time(NULL)); char op[7] = "RUFruf";
  for (int i = 0; i < 100; i ++)
  {
    int number = rand() % n;
    moveCube(c, op[rand() % 6], number);
  }
}
void readScramble(Cube &c)
{
  randomScramble(c); return;
  int number; char op;
  FILE *scrambleFile = fopen("cube/scramble", "r"); if (scrambleFile == NULL) return;
  while (fscanf(scrambleFile, "%d%c", &number, &op) != EOF) moveCube(c, op, number - 1);
  fclose(scrambleFile);
}
