#ifndef DERIVATIVEARRAY_H_
#define DERIVATIVEARRAY_H_


#include "Particle.h"

#include <vector>


// Assuming that the particles are moved according to the equation z'(t) = F(z(t)),
// this class stores the value of the right-hand side of this equation for each particle.
class DerivativeArray
{
public:
	DerivativeArray();
	DerivativeArray( const std::vector<Particle>& particle );
	std::vector<Particle> entries;
};

// These operators are used to implement integration schemes such as
// z(t+dt) = z(t) + dt*F(z(t))
// where z(t) and z(t+dt) are represented by std::vector<Particle>,
// and F(z(t)) is represented by DerivativeArray
DerivativeArray         operator + ( const DerivativeArray& d1, const DerivativeArray& d2 );
DerivativeArray         operator * ( double a, const DerivativeArray& d );
std::vector<Particle>   operator + ( const std::vector<Particle>& particle, const DerivativeArray& d );


#endif /*DERIVATIVEARRAY_H_*/
