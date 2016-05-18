#ifndef PENDULUMENVIRONMENT_H_
#define PENDULUMENVIRONMENT_H_


#include "Particle.h"
#include "Point.h"
#include "Environment.h"
#include <vector>


class PendulumEnvironment :
	public Environment
{
public:
	// compute force for particle particle[index]
	Point ComputeForce(const std::vector<Particle>& particle, size_t index);
};


#endif /*PENDULUMENVIRONMENT_H_*/