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
  value += 5*(c.face[0][2][1] == 0 && c.face[3][0][1] == 3); value += 5*(c.face[2][2][1] == 2 && c.face[3][1][2] == 3);
  value += 5*(c.face[4][2][1] == 4 && c.face[3][1][0] == 3); value += 5*(c.face[5][2][1] == 5 && c.face[3][2][1] == 3);
  return(5 + 5*4 - value);
}
