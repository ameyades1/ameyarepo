#ifndef __CAR__
#define __CAR__

#include <iostream>

#include "vehicle.h"
class CCar : public CVehicle
{
private:
	std::string engine_type;
public:

	CCar(std::string name, std::string eng_type) :CVehicle(name){engine_type = eng_type;}
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
		std::cout << "Installed " << engine_type << " Engine...\n";
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
