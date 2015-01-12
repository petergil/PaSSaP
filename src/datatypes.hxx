#ifndef PASSAP_DATATYPES_HXX
#define PASSAP_DATATYPES_HXX


/* Define a standard type for floating point values.
 * Precision of floating point data type.
 */
typedef double ftype;

/** A standard 3d vector
  *
  */
struct vector3{
  ftype x = 0;
  ftype y = 0;
  ftype z = 0;
};

/** Represents one particle in the system.
  *
  */
struct particle{
  vector3 pos; // position
  vector3 vel; // velocity
  // ftype mass = 0; // mass
  // ftype radius = 1; // radius
};

#endif // PASSAP_DATATYPES_HXX
