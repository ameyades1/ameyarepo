#ifndef __CHIPSIM__
#define __CHIPSIM__

#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include "large_simulation.h"

class CChipSimulation : public CLargeSimulation
{

public:
	bool boot_status;

	CChipSimulation()
	{
		SimulateTillLinuxBoot();
	}

	CChipSimulation(float init_conditions)
	{
		SimulateTillLinuxBoot(init_conditions);
	}

	// Copy simulation results without running simulation again
	CLargeSimulation* makeCopy()
	{
		// We are calling parameterized constructor to avoid long simulation :)
		CLargeSimulation* newSim = dynamic_cast<CLargeSimulation*>(new CChipSimulation(*this));
		return newSim;
	}

	void SimulateTillLinuxBoot(bool disable_pcie = false)
	{
		//Consume lot of time
		std::cout <<"Gate level simulation till linux boot...\n";
		boot_status = boot_status |  disable_pcie;
		std::this_thread::sleep_for (std::chrono::seconds(7));
		std::cout <<"Simulation complete after 7 hours...\n";
	}

	void SimulateDrivers(unsigned int d)
	{
		std::cout <<"Simulating drivers... \n" ;
	}

private:
	// Our copy constructors. Make them private to avoid cheating
	CChipSimulation(CChipSimulation& physim)
	{
		boot_status = physim.boot_status;
	}

	CChipSimulation& operator= (CChipSimulation physim)
	{
		return *this;
	}
};

#endif
