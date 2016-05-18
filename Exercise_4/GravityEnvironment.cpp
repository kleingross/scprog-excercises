#include "Environment.h"
#include "GravityEnvironment.h"
#include <iostream>


Point
ComputeForce( const std::vector<Particle>& particle, size_t index )
{
    static const double ks = 50.0;
    static const double kd = 1.0;
    static const double L0 = 1.0;
    static const double g  = 9.8;
    
	Point force;
	Point gravity;
	gravity.x = 0.0;
	gravity.y = -g;

	if (index > 0)
	{
		//index
		int last_index = particle.size()-1;
		int i = index;
		int j = index - 1;
		//position
		Point pi = particle[i].position;
		Point pj = particle[j].position;
		//velocity
		Point vi = particle[i].velocity;
		Point vj = particle[j].velocity;
		//distance
		double Lij = pi.distance_to(pj);
		//direction
		Point rij = (pj - pi) / Lij;
		//force
		Point force_ij = (ks * (Lij - L0) + kd * (((vj.x - vi.x) * rij.x) + ((vj.y - vi.y) * rij.y) ) )* rij;
		
		//second force component only if not last particle
		if (index < last_index)
		{
			int k = index + 1; 
			Point pk = particle[k].position;
			Point vk = particle[k].velocity;
			double Lik = pi.distance_to(pk);
			Point rik = (pk - pi) / Lik;
			Point force_ik = (ks * (Lik - L0) + kd * (((vk.x - vi.x) * rik.x) + ((vk.y - vi.y) * rik.y)))* rik;
			force = (force_ij + force_ik);
		}
		//if last particle
		else if (index = last_index) { force = force_ij;  }
	}
	//first element does not move
	else if (index == 0)
	{
		return force;
	}
	else
	{
		std::cout << "index out of range" << std::endl;
		return force;
	}

	Point result;
	result = force / particle[index].mass + gravity;
	return result;
}
