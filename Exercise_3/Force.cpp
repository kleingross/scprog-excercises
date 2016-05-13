#include "Force.h"
#include "Point.h"
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
		Point rij = (pi - pj) / Lij;
		//force
		Point force_ij = (ks * (Lij - L0) + kd * (((vi.x - vj.x) * rij.x) + ((vi.y - vj.y) * rij.y)) )* rij;
		
		//second force component only if not last particle
		if (index < last_index)
		{
			int k = index + 1; 
			Point pk = particle[k].position;
			Point vk = particle[k].velocity;
			double Lik = pi.distance_to(pk);
			Point rik = (pi - pk) / Lik;
			Point force_ik = (ks * (Lik - L0) + kd * (((vi.x - vk.x) * rik.x) + ((vi.y - vk.y) * rik.y)))* rik;
			force = (force_ij - force_ik);
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
