#ifndef __BYCICLE__
#define __BYCICLE__

#include <iostream>

#include "vehicle.h"
class CBicycle : public CVehicle
{
public:
	CBicycle(std::string name) :CVehicle(name){}
	~CBicycle() {}
	void InstallChassis()
	{
		std::cout << "Installed Carbon Fiber Frame...\n";
	}
	void InstallTyres()
	{
		std::cout << "Installed 2 tyres...\n";
	}

	// No engine and electronics

	void InstallSeats()
	{
		std::cout << "Installed rider seat...\n";
	}
	void Paint()
	{
		std::cout << "Painted ...\n";
	}
};
#endif
