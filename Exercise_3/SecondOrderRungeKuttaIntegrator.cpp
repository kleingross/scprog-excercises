#include "SecondOrderRungeKuttaIntegrator.h"
#include "DerivativeArray.h"


std::vector<Particle>
SecondOrderRungeKuttaIntegrator::update_particles( const std::vector<Particle>& particle, double time_step )
{
	std::vector<Particle> new_particle = particle;
	DerivativeArray k1(particle);
	DerivativeArray k2(particle + ((time_step / 2) * k1));
	new_particle = particle + (time_step * k2);
	
	return new_particle;
}
