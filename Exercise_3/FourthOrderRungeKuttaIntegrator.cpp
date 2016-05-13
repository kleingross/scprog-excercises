#include "FourthOrderRungeKuttaIntegrator.h"
#include "DerivativeArray.h"


std::vector<Particle>
FourthOrderRungeKuttaIntegrator::update_particles( const std::vector<Particle>& particle, double time_step )
{
	std::vector<Particle> new_particle = particle;
	
	DerivativeArray k1(particle);
	DerivativeArray k2(particle + ((time_step / 2) * k1));
	DerivativeArray k3(particle + ((time_step / 2) * k2));
	DerivativeArray k4(particle + (time_step * k3));

	new_particle = particle + ((time_step / 6) * (k1 + (2 * k2) + (2 * k3) + k4));

	return new_particle;
}
