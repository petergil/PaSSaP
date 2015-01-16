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



#endif // PASSAP_VECTOR_MATH_HXX
