#include "particle.h"
#include "Integrator.h"
#include "EulerIntegrator.h"
#include "SecondOrderRungeKuttaIntegrator.h"
#include "FourthOrderRungeKuttaIntegrator.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>


// Create the Euler integrator, or the second order Runge-Kutta integrator, or the fourth order Runge-Kutta integrator
static Integrator*
CreateIntegrator( int argc, char** argv )
{
	if (argc > 1)
	{
		std::string integrator_type;
		integrator_type = argv[1];

		//Fallunterscheidung nach modus
		if (integrator_type == "Euler")
		{
			static EulerIntegrator euler_integrator;
			std::cout << integrator_type << std::endl;
			return &euler_integrator;
		}
		else if (integrator_type == "Runge-Kutta-2")
		{
			static SecondOrderRungeKuttaIntegrator rk2_integrator;
			std::cout << integrator_type << std::endl;
			return &rk2_integrator;
		}
		else if (integrator_type == "Runge-Kutta-4")
		{
			static FourthOrderRungeKuttaIntegrator rk4_integrator;
			std::cout << integrator_type << std::endl;
			return &rk4_integrator;
		}
		else {
			std::cout << "wrong integrator, default Euler" << std::endl;
			static EulerIntegrator fallback_integrator;
			return &fallback_integrator;
		}
	}
	else {
		std::cout << "no integrator chosen, default Euler" << std::endl;
		static EulerIntegrator fallback_integrator;
		return &fallback_integrator;
	}
}

// read particles from the file "particle.txt"
static std::vector<Particle>
ReadParticles()
{
	int N = 4; //number of particles to read
	static std::vector<Particle> start_particles;

	std::fstream input_file;
	input_file.open("particle.txt");
	
	//append properties to start_particles
	if (input_file.is_open())
	{
		for (int i = 0; i < N; i++)
		{
			Particle particle;
			input_file >> particle.position.x;
			input_file >> particle.position.y;
			input_file >> particle.mass;
			//std::cout << "x: " << particle.position.x << " y: " << particle.position.y << " mass: " << particle.mass << std::endl;
			start_particles.push_back(particle);
		}
	}
	else { std::cout << "error reading file" << std::endl; }
	input_file.close();

	return start_particles;
}

// print particles to the file frame_NNNN.txt,
// where NNNN is the frame index passed as the second function argument
static void
PrintParticles( const std::vector<Particle>& particle, int frame )
{
	//set up filename from frame, needs optimization
	std::stringstream convert_frame; //conversion int to string
	convert_frame << frame;
	std::string frame_number = convert_frame.str();
	size_t framesize = frame_number.length(); //number of digits
	std::string output_filename = "frame_";	//set up filename
	output_filename.resize(10 - framesize, '0'); //format filename with '0'
	output_filename = output_filename + frame_number + ".txt";

		
	//write to output file
	std::fstream output_file;
	output_file.open(output_filename, std::ios::out);

	for (int i = 0; i < particle.size(); i++)
	{
		std::stringstream convert_x; //double to string
		convert_x << particle[i].position.x;
		std::string current_position_x = convert_x.str();
		std::stringstream convert_y; //double to string
		convert_y << particle[i].position.y;
		std::string current_position_y = convert_y.str();

		output_file << current_position_x << " " << current_position_y << std::endl;
	}
	output_file.close();
		
}

static void
RunSimulation( std::vector<Particle>& particle, Integrator* integrator )
{
    static const int    FrameCount  = 500;
    static const int    StepCount   = 10;
    static const double TimeStep    = 0.01;
    
    for( int frame = 0; frame < FrameCount; ++frame )
    {
		for (int step = 0; step < StepCount; ++step) 
			particle = integrator->update_particles(particle, TimeStep);
        
        PrintParticles( particle, frame );
    }
}

int
main( int argc, char** argv )
{
	Integrator* integrator = CreateIntegrator( argc, argv );
	
    if( integrator != 0 )
    {
        std::vector<Particle> particle = ReadParticles();
        RunSimulation( particle, integrator );
	}
    
    return 0;
}
