#include "DerivativeArray.h"


DerivativeArray::DerivativeArray( const std::vector<Particle>& particle )
{
}

DerivativeArray
operator + ( const DerivativeArray& d1, const DerivativeArray& d2 )
{
	DerivativeArray array = d1;
	return array;
}

DerivativeArray
operator * ( double a, const DerivativeArray& d )
{
	DerivativeArray array = d;
	return array;
}

std::vector<Particle>
operator + ( const std::vector<Particle>& particle, const DerivativeArray& d )
{
	std::vector<Particle> result = particle;
	return result;
}
