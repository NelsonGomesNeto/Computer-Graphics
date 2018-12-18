// 0 - face, 1 - top, 2 - back, 3 - down, 4 - left, 5 - right
struct Piece { int color[6] = {0, 1, 2, 3, 4, 5}; };
const double colorMap[6][3] = {{1, 1, 1}, {0, 0, 1}, {1, 241 / 255.0, 25 / 255.0}, {0, 1, 0}, {253 / 255.0, 126 / 255.0, 0}, {1, 0, 0}};
const int n = 3; const int cycleSize = 2*n + 2*(n - 2);
struct Cube { Piece pieces[n][n][n]; };
Piece cycle[cycleSize];

int dr[3][4] = {{3, 2, 1, 0}, {5, 2, 4, 0}, {4, 3, 5, 1}};
void rotatePiece(Piece &piece, unsigned char key, bool reverse)
{
  int d = 0;
  switch (key)
  {
    case 'R': d = 0; break;
    case 'U': d = 1; break;
    case 'F': d = 2; break;
    default: break;
  }
  if (reverse)
  {
    int aux = piece.color[dr[d][3]];
    for (int k = 3; k > 0; k --)
      piece.color[dr[d][k]] = piece.color[dr[d][k - 1]];
    piece.color[dr[d][0]] = aux;
  }
  else
  {
    int aux = piece.color[dr[d][0]];
    for (int k = 0; k < 3; k ++)
      piece.color[dr[d][k]] = piece.color[dr[d][k + 1]];
    piece.color[dr[d][3]] = aux;
  }
}

void moveR(Cube &c, int number, bool reverse)
{
  int i = 0, j = 0, k = n - 1 - number, l = 0;
  while (i < n) cycle[l ++] = c.pieces[i ++][j][k]; i --, j ++;
  while (j < n) cycle[l ++] = c.pieces[i][j ++][k]; j --, i --;
  while (i >= 0) cycle[l ++] = c.pieces[i --][j][k]; i ++, j --;
  while (j >= 1) cycle[l ++] = c.pieces[i][j --][k];

  for (int m = 0; m < cycleSize; m ++) rotatePiece(cycle[m], 'R', reverse);

  i = n - 1, j = 0, k = n - 1 - number, l = (reverse ? cycleSize / 2 : 0) - 1;
  while (j < n) c.pieces[i][j ++][k] = cycle[(++ l) % cycleSize]; j --, i --;
  while (i >= 0) c.pieces[i --][j][k] = cycle[(++ l) % cycleSize]; i ++, j --;
  while (j >= 0) c.pieces[i][j --][k] = cycle[(++ l) % cycleSize]; j ++, i ++;
  while (i < n - 1) c.pieces[i ++][j][k] = cycle[(++ l) % cycleSize];
}

void moveU(Cube &c, int number, bool reverse)
{
  int i = 0, j = number, k = n - 1, l = 0;
  while (k >= 0) cycle[l ++] = c.pieces[i][j][k --]; k ++, i ++;
  while (i < n) cycle[l ++] = c.pieces[i ++][j][k]; i --, k ++;
  while (k < n) cycle[l ++] = c.pieces[i][j][k ++]; k --, i --;
  while (i >= 1) cycle[l ++] = c.pieces[i --][j][k];

  for (int m = 0; m < cycleSize; m ++) rotatePiece(cycle[m], 'U', reverse);

  i = 0, j = number, k = 0, l = (reverse ? cycleSize / 2 : 0) - 1;
  while (i < n) c.pieces[i ++][j][k] = cycle[(++ l) % cycleSize]; i --, k ++;
  while (k < n) c.pieces[i][j][k ++] = cycle[(++ l) % cycleSize]; k --, i --;
  while (i >= 0) c.pieces[i --][j][k] = cycle[(++ l) % cycleSize]; i ++, k --;
  while (k >= 1) c.pieces[i][j][k --] = cycle[(++ l) % cycleSize];
}

void moveF(Cube &c, int number, bool reverse)
{
  int i = number, j = 0, k = 0, l = 0;
  while (k < n) cycle[l ++] = c.pieces[i][j][k ++]; k --, j ++;
  while (j < n) cycle[l ++] = c.pieces[i][j ++][k]; j --, k --;
  while (k >= 0) cycle[l ++] = c.pieces[i][j][k --]; k ++, j --;
  while (j >= 1) cycle[l ++] = c.pieces[i][j --][k];

  for (int m = 0; m < cycleSize; m ++) rotatePiece(cycle[m], 'F', reverse);

  i = number, j = 0, k = n - 1, l = (reverse ? cycleSize / 2 : 0) - 1;
  while (j < n) c.pieces[i][j ++][k] = cycle[(++ l) % cycleSize]; j --, k --;
  while (k >= 0) c.pieces[i][j][k --] = cycle[(++ l) % cycleSize]; k ++, j --;
  while (j >= 0) c.pieces[i][j --][k] = cycle[(++ l) % cycleSize]; j ++, k ++;
  while (k < n - 1) c.pieces[i][j][k ++] = cycle[(++ l) % cycleSize];
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
