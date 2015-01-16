
#include "vector_math.hxx"

vector3 add(const vector3 &a, const vector3 &b){
  vector3 c;
  c.x = a.x + b.x;
  c.y = a.y + b.y;
  c.z = a.z + b.z;
  return c;
}

vector3 sub(const vector3 &a, const vector3 &b){
  vector3 c;
  c.x = a.x - b.x;
  c.y = a.y - b.y;
  c.z = a.z - b.z;
  return c;
}

ftype dot(const vector3 &a, const vector3 &b){
  ftype c = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
  return c;
}





