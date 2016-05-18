#include "Environment.h"
#include "GravityEnvironment.h"
#include "Point.h"
#include <iostream>
#include <math.h>


Point GravityEnvironment::ComputeForce( const std::vector<Particle>& particle, size_t index )
{
	static const double G = 6.674e-11;
    
	Point result;
	result.x = 0.0;
	result.y = 0.0;
	
	for (int j = 0; j < particle.size(); j++)
	{
		if (j != index)
		{
			Point ri = particle[index].position;
			Point rj = particle[j].position;
			double mj = particle[j].mass;

			//distance
			double rij = ri.distance_to(rj);

			//direction
			Point e_rij = (ri - rj) / rij;

			//gravity
			Point gravity_ij = (- G * mj / pow(rij, 2)) * e_rij;

			result = result + gravity_ij;
			
		}
	}

	return result;
		
}