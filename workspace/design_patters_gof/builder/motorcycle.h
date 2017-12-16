#ifndef __MOTORCYCLE__
#define __MOTORCYCLE__

#include <iostream>

#include "vehicle.h"
class CMotorcycle : public CVehicle
{
public:
	CMotorcycle(std::string name) :CVehicle(name){}
	~CMotorcycle() {}
	void InstallChassis()
	{
		std::cout << "Installed Steel Alloy Frame...\n";
	}
	void InstallTyres()
	{
		std::cout << "Installed 2 tyres...\n";
	}
	void InstallEngine()
	{
		std::cout << "Installed 150cc Fuel Injection Engine...\n";
	}
	void InstallElectronics()
	{
		std::cout << "Installed Digital Display...\n";
	}
	void InstallSeats()
	{
		std::cout << "Installed rider and pillion seat...\n";
	}
	void Paint()
	{
		std::cout << "Painted ...\n";
	}
};
#endif
