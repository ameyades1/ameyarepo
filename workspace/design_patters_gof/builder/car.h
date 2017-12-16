#ifndef __CAR__
#define __CAR__

#include <iostream>

#include "vehicle.h"
class CCar : public CVehicle
{
public:
	CCar(std::string name) :CVehicle(name){}
	~CCar() {}
	void InstallChassis()
	{
		std::cout << "Installed Chassis...\n";
	}
	void InstallTyres()
	{
		std::cout << "Installed 4 tyres...\n";
	}
	void InstallEngine()
	{
		std::cout << "Installed CRDi Diesel 13HP Engine...\n";
	}
	void InstallElectronics()
	{
		std::cout << "Installed Android auto and Bose sound system...\n";
	}
	void InstallSeats()
	{
		std::cout << "Installed 4 seats...\n";
	}
	void Paint()
	{
		std::cout << "Painted ...\n";
	}
};

#endif
