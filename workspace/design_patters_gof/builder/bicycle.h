#ifndef __BYCICLE__
#define __BYCICLE__

#include <iostream>

#include "vehicle.h"
class CBicycle : public CVehicle
{
	std::string frame_type;
public:
	CBicycle(std::string name, std::string ftype) :CVehicle(name){frame_type = ftype;}
	~CBicycle() {}
	void InstallChassis()
	{
		std::cout << "Installed " << frame_type << " Frame...\n";
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
