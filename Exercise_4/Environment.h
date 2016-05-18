#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_


#include "Particle.h"
#include "Point.h"
#include <vector>


class Environment
{
public:
	virtual ~Environment() {}

	// Compute the force for the particle particle[index].
	virtual Point ComputeForce(const std::vector<Particle>& particle, size_t index) = 0;
};


#endif /*ENVIRONMENT_H_*/