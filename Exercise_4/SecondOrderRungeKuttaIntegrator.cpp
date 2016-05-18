#include "SecondOrderRungeKuttaIntegrator.h"
#include "DerivativeArray.h"
#include "Environment.h"


std::vector<Particle>
SecondOrderRungeKuttaIntegrator::update_particles( const std::vector<Particle>& particle, double time_step, Environment* environment)
{
	std::vector<Particle> new_particle = particle;
	DerivativeArray k1(particle, environment);
	DerivativeArray k2(particle + ((time_step / 2) * k1), environment);
	new_particle = particle + (time_step * k2);
	
	return new_particle;
}
