#include "Point.h"
#include "Particle.h"
#include "DerivativeArray.h"
#include "Integrator.h"
#include "EulerIntegrator.h"
#include "SecondOrderRungeKuttaIntegrator.h"
#include "FourthOrderRungeKuttaIntegrator.h"
#include "Environment.h"
#include "GravityEnvironment.h"
#include "PendulumEnvironment.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>


// namespace for parmeters, default to pendulum
namespace parameters
{
	int steps_per_frame = 10;
	double time_step = 0.01;
	std::string input_file = "pendulum.txt";
}

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
			std::cout << "integrator type: " << integrator_type << std::endl;
			return &euler_integrator;
		}
		else if (integrator_type == "Runge-Kutta-2")
		{
			static SecondOrderRungeKuttaIntegrator rk2_integrator;
			std::cout << "integrator type: " << integrator_type << std::endl;
			return &rk2_integrator;
		}
		else if (integrator_type == "Runge-Kutta-4")
		{
			static FourthOrderRungeKuttaIntegrator rk4_integrator;
			std::cout << "integrator type: " << integrator_type << std::endl;
			return &rk4_integrator;
		}
		else {
			std::cout << "incorrect integrator, default Euler" << std::endl;
			static EulerIntegrator fallback_integrator;
			return &fallback_integrator;
		}
	}
	else
	{
		std::cout << "no integrator chosen, default Euler" << std::endl;
		static EulerIntegrator fallback_integrator;
		return &fallback_integrator;
	}
}

// Create Gravity environment, or Pendulum Environment
static Environment*
CreateEnvironment(int argc, char** argv)
{
	if ( argc > 2)
	{
		std::string environment_type;
		environment_type = argv[2];

		//Fallunterscheidung nach Environment
		if (environment_type == "pendulum")
		{
			static PendulumEnvironment pendulum_environment;
			std::cout << "environment: " << environment_type << std::endl;
			return &pendulum_environment;
		}

		else if (environment_type == "gravity") 
		{
			static GravityEnvironment gravity_environment;
			std::cout << "environment: " << environment_type << std::endl;
			return &gravity_environment;
		}

		else 
		{
			std::cout << "incorrect environment chosen, default pendulum" << std::endl;
			static PendulumEnvironment fallback_environment;
			return &fallback_environment;
		}

	}
	else 
	{
		std::cout << "no environment chosen, default pendulum" << std::endl;
		static PendulumEnvironment fallback_environment;
		return &fallback_environment;
	}
}

// Read start particles from input_file
static std::vector<Particle>
ReadParticles()
{
	static std::vector<Particle> start_particles;

	std::fstream input_file;
	input_file.open( parameters::input_file, std::ios::in );

	//append properties to start_particles
	if (input_file.is_open())
	{
		while( !input_file.eof() )
		{
			Particle particle;

			//read in properties of particle
			input_file >> particle.position.x;
			input_file >> particle.position.y;
			input_file >> particle.velocity.x;
			input_file >> particle.velocity.y;
			input_file >> particle.mass;
			
			//if eof dont append to start particles
			if (input_file.eof()) break;

			//append read start_particle
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
RunSimulation( std::vector<Particle>& particle, Integrator* integrator, Environment* environment )
{
    static const int    FrameCount  = 500;
    static const int    StepCount   = parameters::steps_per_frame;
    static const double TimeStep    = parameters::time_step;
    
    for( int frame = 0; frame < FrameCount; ++frame )
    {
		for (int step = 0; step < StepCount; ++step) 
			particle = integrator->update_particles(particle, TimeStep, environment);
        
        PrintParticles( particle, frame );
    }
}

int
main( int argc, char** argv )
{
	// set global variables
	Integrator* integrator = CreateIntegrator( argc, argv );
	Environment* environment = CreateEnvironment(argc, argv); 

	if (argc > 3) parameters::steps_per_frame = atoi(argv[3]);
	std::cout << "steps per frame: " << argv[3] << std::endl;
	if (argc > 4) parameters::time_step = atof(argv[4]);
	std::cout << "time step: " << argv[4] << std::endl;
	if (argc > 5) parameters::input_file = argv[5];
	std::cout << "input file: " << parameters::input_file << std::endl;
		
    if( integrator != 0 && environment != 0 )
    {
        std::vector<Particle> particle = ReadParticles();
        RunSimulation( particle, integrator, environment );

		std::cout << "success" << std::endl;
	}
    
    return 0;
}
