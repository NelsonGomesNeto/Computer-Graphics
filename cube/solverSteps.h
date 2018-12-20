int edgeDistanceMemo[12][2][12][2];
int edgeColor[12][2] = {{0, 1}, {0, 5}, {0, 4}, {0, 3}, {2, 1}, {2, 5}, {2, 4}, {2, 3}, {1, 5}, {1, 4}, {3, 5}, {3, 4}};
int mapEdgeColor[6][6] = {{-1, 0, -1, 3, 2, 1}, {0, -1, 4, -1, 9, 8}, {-1, 4, -1, 7, 6, 5}, {3, -1, 7, -1, 11, 10}, {2, 9, 6, 11, -1, -1}, {1, 8, 5, 10, -1, -1}};

struct edgePosition { int color1, face1, i1, j1, color2, face2, i2, j2; };
edgePosition findEdgePosition(Cube &c, int c1, int c2)
{
  for (int i = 1; i < n - 1; i ++)
  {
    // face - top
    if (c.face[0][0][i] == c1 && c.face[1][n-1][i] == c2)
      return(edgePosition({c1, 0, 0, i, c2, 1, n - 1, i}));
    if (c.face[0][0][i] == c2 && c.face[1][n-1][i] == c1)
      return(edgePosition({c2, 0, 0, i, c1, 1, n - 1, i}));

    // face - right
    if (c.face[0][i][0] == c1 && c.face[5][i][0] == c2)
      return(edgePosition({c1, 0, i, 0, c2, 5, i, 0}));
    if (c.face[0][i][0] == c2 && c.face[5][i][0] == c1)
      return(edgePosition({c2, 0, i, 0, c1, 5, i, 0}));

    // face - down
    if (c.face[0][n-1][i] == c1 && c.face[3][n-1][i] == c2)
      return(edgePosition({c1, 0, n - 1, i, c2, 3, n - 1, i}));
    if (c.face[0][n-1][i] == c2 && c.face[3][n-1][i] == c1)
      return(edgePosition({c2, 0, n - 1, i, c1, 3, n - 1, i}));
    
    // face - left
    if (c.face[0][i][n-1] == c1 && c.face[4][i][0] == c2)
      return(edgePosition({c1, 0, i, n - 1, c2, 4, i, 0}));
    if (c.face[0][i][n-1] == c2 && c.face[4][i][0] == c1)
      return(edgePosition({c2, 0, i, n - 1, c1, 4, i, 0}));

    // right - top
    if (c.face[5][0][i] == c1 && c.face[1][n - 1 - i][0] == c2)
      return(edgePosition({c1, 5, 0, i, c2, 1, n - 1 - i, 0}));
    if (c.face[5][0][i] == c2 && c.face[1][n - 1 - i][0] == c1)
      return(edgePosition({c2, 5, 0, i, c1, 1, n - 1 - i, 0}));

    // right - back
    if (c.face[5][i][n-1] == c1 && c.face[2][i][0] == c2)
      return(edgePosition({c1, 5, i, n - 1, c2, 2, i, 0}));
    if (c.face[5][i][n-1] == c2 && c.face[2][i][0] == c1)
      return(edgePosition({c2, 5, i, n - 1, c1, 2, i, 0}));

    // right - down
    if (c.face[5][n-1][i] == c1 && c.face[3][n - 1 - i][0] == c2)
      return(edgePosition({c1, 5, n - 1, i, c2, 3, n - 1 - i, 0}));
    if (c.face[5][n-1][i] == c2 && c.face[3][n - 1 - i][0] == c1)
      return(edgePosition({c2, 5, n - 1, i, c1, 3, n - 1 - i, 0}));

    // top - back
    if (c.face[1][0][i] == c1 && c.face[2][0][i] == c2)
      return(edgePosition({c1, 1, 0, i, c2, 2, 0, i}));
    if (c.face[1][0][i] == c2 && c.face[2][0][i] == c1)
      return(edgePosition({c2, 1, 0, i, c1, 2, 0, i}));

    // top - left
    if (c.face[1][i][n-1] == c1 && c.face[4][0][n - 1 - i] == c2)
      return(edgePosition({c1, 1, i, n - 1, c2, 4, 0, n - 1 - i}));
    if (c.face[1][i][n-1] == c2 && c.face[4][0][n - 1 - i] == c1)
      return(edgePosition({c2, 1, i, n - 1, c1, 4, 0, n - 1 - i}));

    // left - back
    if (c.face[4][i][n-1] == c1 && c.face[2][i][n-1] == c2)
      return(edgePosition({c1, 4, i, n - 1, c2, 2, i, n - 1}));
    if (c.face[4][i][n-1] == c2 && c.face[2][i][n-1] == c1)
      return(edgePosition({c2, 4, i, n - 1, c1, 2, i, n - 1}));

    // left - down
    if (c.face[4][n-1][i] == c1 && c.face[3][n - 1 - i][n-1] == c2)
      return(edgePosition({c1, 4, n - 1, i, c2, 3, n - 1 - i, n - 1}));
    if (c.face[4][n-1][i] == c2 && c.face[3][n - 1 - i][n-1] == c1)
      return(edgePosition({c2, 4, n - 1, i, c1, 3, n - 1 - i, n - 1}));

    // down - back
    if (c.face[3][0][i] == c1 && c.face[2][n-1][i] == c2)
      return(edgePosition({c1, 3, 0, i, c2, 2, n - 1, i}));
    if (c.face[3][0][i] == c2 && c.face[2][n-1][i] == c1)
      return(edgePosition({c2, 3, 0, i, c1, 2, n - 1, i}));
  }
  return(edgePosition({}));
}

double cross(Cube &c)
{
  double value = c.face[3][0][1] == 3;
  value += c.face[3][1][2] == 3; value += c.face[3][1][1] == 3;
  value += c.face[3][2][1] == 3; value += c.face[3][1][0] == 3;
  return(5 - value);
}
double crossSides(Cube &c)
{
  double value = 5 - cross(c);
  value += 1*(c.face[0][2][1] == 0 && c.face[3][2][1] == 3); value += 1*(c.face[5][2][1] == 5 && c.face[3][1][0] == 3);
  value += 1*(c.face[2][2][1] == 2 && c.face[3][0][1] == 3); value += 1*(c.face[4][2][1] == 4 && c.face[3][1][2] == 3);
  return(5 + 1*4 - value);
}
double edgeDistance(Cube &c)
{
  edgePosition ep = findEdgePosition(c, 0, 3);
  return(1);
  // return(1 - (c.face[0][2][1] == 0 && c.face[3][2][1] == 3));
}
