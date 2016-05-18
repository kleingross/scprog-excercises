#ifndef GRAVITYENVIRONMENT_H_
#define GRAVITYENVIRONMENT_H_


#include "Particle.h"
#include "Point.h"
#include "Environment.h"
#include <vector>


class GravityEnvironment:
	public Environment
{
public:
	// compute force for particle particle[index]
	Point ComputeForce(const std::vector<Particle>& particle, size_t index);
};


#endif /*GRAVITYENVIRONMENT_H_*/