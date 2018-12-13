// 0 - face, 1 - top, 2 - back, 3 - down, 4 - left, 5 - right
struct Piece { int color[6] = {0, 1, 2, 3, 4, 5}; };
const double colorMap[6][3] = {{1, 1, 1}, {0, 0, 1}, {1, 241 / 255.0, 25 / 255.0}, {0, 1, 0}, {253 / 255.0, 126 / 255.0, 0}, {1, 0, 0}};
const int n = 3; const int cicleSize = 2*n + 2*(n - 2);
struct Cube { Piece pieces[n][n][n]; };
Piece cicle[cicleSize];

int dr[3][4] = {{3, 2, 1, 0}, {5, 2, 4, 0}, {4, 3, 5, 1}};
void rotatePiece(Piece &piece, unsigned char key)
{
  int d = 0;
  switch (key)
  {
    case 'R': d = 0; break;
    case 'U': d = 1; break;
    case 'F': d = 2; break;
    default: break;
  }
  int aux = piece.color[dr[d][0]];
  for (int k = 0; k < 3; k ++)
    piece.color[dr[d][k]] = piece.color[dr[d][k + 1]];
  piece.color[dr[d][3]] = aux;
}

void moveR(Cube &c)
{
  int i = 0, j = 0, k = n - 1, l = 0;
  while (i < n) cicle[l ++] = c.pieces[i ++][j][k]; i --, j ++;
  while (j < n) cicle[l ++] = c.pieces[i][j ++][k]; j --, i --;
  while (i >= 0) cicle[l ++] = c.pieces[i --][j][k]; i ++, j --;
  while (j >= 1) cicle[l ++] = c.pieces[i][j --][k];

  for (int m = 0; m < cicleSize; m ++) rotatePiece(cicle[m], 'R');

  i = n - 1, j = 0, k = n - 1, l = 0;
  while (j < n) c.pieces[i][j ++][k] = cicle[l ++]; j --, i --;
  while (i >= 0) c.pieces[i --][j][k] = cicle[l ++]; i ++, j --;
  while (j >= 0) c.pieces[i][j --][k] = cicle[l ++]; j ++, i ++;
  while (i < n - 1) c.pieces[i ++][j][k] = cicle[l ++];
}

void moveU(Cube &c)
{
  int i = 0, j = 0, k = n - 1, l = 0;
  while (k >= 0) cicle[l ++] = c.pieces[i][j][k --]; k ++, i ++;
  while (i < n) cicle[l ++] = c.pieces[i ++][j][k]; i --, k ++;
  while (k < n) cicle[l ++] = c.pieces[i][j][k ++]; k --, i --;
  while (i >= 1) cicle[l ++] = c.pieces[i --][j][k];

  for (int m = 0; m < cicleSize; m ++) rotatePiece(cicle[m], 'U');

  i = 0, j = 0, k = 0, l = 0;
  while (i < n) c.pieces[i ++][j][k] = cicle[l ++]; i --, k ++;
  while (k < n) c.pieces[i][j][k ++] = cicle[l ++]; k --, i --;
  while (i >= 0) c.pieces[i --][j][k] = cicle[l ++]; i ++, k --;
  while (k >= 1) c.pieces[i][j][k --] = cicle[l ++];
}

void moveF(Cube &c)
{
  int i = 0, j = 0, k = 0, l = 0;
  while (k < n) cicle[l ++] = c.pieces[i][j][k ++]; k --, j ++;
  while (j < n) cicle[l ++] = c.pieces[i][j ++][k]; j --, k --;
  while (k >= 0) cicle[l ++] = c.pieces[i][j][k --]; k ++, j --;
  while (j >= 1) cicle[l ++] = c.pieces[i][j --][k];

  for (int m = 0; m < cicleSize; m ++) rotatePiece(cicle[m], 'F');

  i = 0, j = 0, k = n - 1, l = 0;
  while (j < n) c.pieces[i][j ++][k] = cicle[l ++]; j --, k --;
  while (k >= 0) c.pieces[i][j][k --] = cicle[l ++]; k ++, j --;
  while (j >= 0) c.pieces[i][j --][k] = cicle[l ++]; j ++, k ++;
  while (k < n - 1) c.pieces[i][j][k ++] = cicle[l ++];
}

void moveCube(Cube &c, unsigned char key)
{
  switch (key)
  {
    case 'R': moveR(c); break;
    case 'r': for (int i = 0; i < 3; i ++) moveR(c); break;
    case 'U': moveU(c); break;
    case 'u': for (int i = 0; i < 3; i ++) moveU(c); break;
    case 'F': moveF(c); break;
    case 'f': for (int i = 0; i < 3; i ++) moveF(c); break;
    default: break;
  }
}
