#include "particle_operations.hxx"
#include "datatypes.hxx"
#include "vector_math.hxx"
#include <math.h>
#include <iostream>

const ftype SIGMA = 0.01; 

ftype calculate_collision_time(const particle &a, const particle &b){
  
  // T_ab is time of collision 
  ftype T_ab;

  // r(a,b) = r(a) - r(b)
  // r is the position
  vector3 R_ab;
  R_ab = sub(a.pos, b.pos);
  
  // v(a,b) = v(a) - v(b)
  // v is the velocity 
  vector3 V_ab;
  V_ab = sub(a.vel, b.vel);

  // b(a,b) = r(a,b) * v(a,b)
  // b is the Dot Product
  ftype B_ab;
  B_ab = dot(R_ab, V_ab);
  
  if (B_ab < 0){
    // delta = b(a,b)^2 - v(a,b)^2 * (r(a,b)^2 - sigma^2)
    // t(a,b) = (-b(a,b) - sqrt(delta)) / v(a,b)^2
    //
    // V_ab_pow2 is V_ab power 2
    // B_ab_pow2 is B_ab power 2
    // R_ab_pow2 is R_ab power 2
    //
    ftype V_ab_pow2;
    ftype B_ab_pow2;
    ftype R_ab_pow2;
  
    V_ab_pow2 = dot(V_ab, V_ab);
    B_ab_pow2 = B_ab * B_ab;
    R_ab_pow2 = dot(R_ab, R_ab);
  
    ftype delta = B_ab_pow2 - V_ab_pow2 * (R_ab_pow2 - pow(SIGMA, 2));
    T_ab = (-B_ab - (B_ab_pow2 - sqrt(delta))) / V_ab_pow2;
  }
  else{
    T_ab = 0;
  }
  std::cout << "\nzzzzzzz" << T_ab << "\n";
  return T_ab;
}

particle update_position(particle par, ftype dt){}

void perform_collision(particle *a, particle *b){}
