#include "FourthOrderRungeKuttaIntegrator.h"
#include "DerivativeArray.h"


std::vector<Particle>
FourthOrderRungeKuttaIntegrator::update_particles( const std::vector<Particle>& particle, double time_step, Environment* environment)
{
	std::vector<Particle> new_particle = particle;
	
	DerivativeArray k1(particle, environment);
	DerivativeArray k2(particle + ((time_step / 2) * k1), environment);
	DerivativeArray k3(particle + ((time_step / 2) * k2), environment);
	DerivativeArray k4(particle + (time_step * k3), environment);

	new_particle = particle + ((time_step / 6) * (k1 + (2 * k2) + (2 * k3) + k4));

	return new_particle;
}
