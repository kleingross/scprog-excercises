#ifndef FORCE_H_
#define FORCE_H_


#include "Particle.h"
#include "Point.h"
#include <vector>


// Compute the force for the particle particle[index].
Point ComputeForce( const std::vector<Particle>& particle, size_t index );


#endif /*FORCE_H_*/
