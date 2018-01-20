#ifndef __PHYSICSSIM__
#define __PHYSICSSIM__

#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include "large_simulation.h"

class CPhysicsSimulation : public CLargeSimulation
{

public:
	float fEinsteinParameter;

	CPhysicsSimulation()
	{
		DoLargeSimulation();
	}

	CPhysicsSimulation(float init_conditions)
	{
		DoLargeSimulation(init_conditions);
	}

	// Copy simulation results without running simulation again
	CLargeSimulation* makeCopy()
	{
		// We are calling parameterized constructor to avoid long simulation :)
		CLargeSimulation* newSim = dynamic_cast<CLargeSimulation*>(new CPhysicsSimulation(*this));
		return newSim;
	}


	void DoLargeSimulation(float init_conditions = 3.14)
	{
		//Consume lot of time
		std::cout <<"Simulating the universe till today...\n";
		fEinsteinParameter = init_conditions *  init_conditions;
		std::this_thread::sleep_for (std::chrono::seconds(5));
		std::cout <<"Simulation complete after 5 seconds...\n";
	}

	void SimulateAhead(unsigned int d)
	{
		fEinsteinParameter += d;
		std::cout <<"Simulating tomorrow ... " << "FunkyEinsteinValue = " << fEinsteinParameter << "\n";
	}

private:
	// Our copy constructors. Make them private to avoid cheating
	CPhysicsSimulation(CPhysicsSimulation& physim)
	{
		fEinsteinParameter = physim.fEinsteinParameter;
	}

	CPhysicsSimulation& operator= (CPhysicsSimulation physim)
	{
		return *this;
	}
};

#endif
