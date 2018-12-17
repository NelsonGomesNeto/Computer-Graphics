struct Quaternions
{
  double u, x, y, z;

  Quaternions operator+(const Quaternions& q)
  {
    return(Quaternions({u + q.u, x + q.x, y + q.y, z + q.z}));
  }
  Quaternions operator-(const Quaternions& q)
  {
    return(Quaternions({u - q.u, x - q.x, y - q.y, z - q.z}));
  }
  Quaternions operator*(const Quaternions& q)
  {
    return(Quaternions({u*q.u - x*q.x - y*q.y - z*q.z,
            u*q.x + x*q.u + y*q.z - z*q.y,
            u*q.y - x*q.z + y*q.u + z*q.x,
            u*q.z + x*q.y - y*q.x + z*q.u}));
  }
  void fillMat4(double mat[4][4])
  {
    mat[0][0] = 1 - 2*(y*y + z*z), mat[0][1] = 2*(x*y - u*z), mat[0][2] = 2*(u*y + x*z), mat[0][3] = 0;
    mat[1][0] = 2*(x*y + u*z), mat[1][1] = 1 - 2*(x*x + z*z), mat[1][2] = 2*(y*z - u*x), mat[1][3] = 0;
    mat[2][0] = 2*(x*z - u*y), mat[2][1] = 2*(u*x + y*z), mat[2][2] = 1 - 2*(x*x + y*y), mat[2][3] = 0;
    // mat[3][0] = mat[3][1] = mat[3][2] =
    mat[3][0] = mat[3][1] = mat[3][2] = 0, mat[3][3] = 1;
  }
};
