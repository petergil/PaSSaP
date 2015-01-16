#ifndef PASSAP_VECTOR_MATH_HXX
#define PASSAP_VECTOR_MATH_HXX

#include "datatypes.hxx"


/**
  * Add two vectors according to linear algebra.
  *
  * @param a First vector
  * @param b Second vector
  * @return {a.x + b.x, a.y + b.y, a.z + b.z}
  */
vector3 add(const vector3 &a, const vector3 &b);

/**
  * Subtract one vector from another according to linear algebra.
  *
  * @param a First vector
  * @param b Second vector
  * @return {a.x - b.x, a.y - b.y, a.z - b.z}
  */
vector3 sub(const vector3 &a, const vector3 &b);

/**
  * Dot product between two vectors.
  *
  * Ex:
  *
  * return = {a.x * b.x + a.y * b.y + a.z * b.z}
  *
  * @param a First vector
  * @param b Second vector
  * @return the resulting vector
  */
ftype dot(const vector3 &a, const vector3 &b);

/**
  * Multiply a constant number to a vector
  * @param n constant number
  * @param a vetor
  * @return {a.x * n, a.y*n, a.z * n}
  * */
vector3 multiply(const ftype n, vector3 a);

#endif // PASSAP_VECTOR_MATH_HXX
