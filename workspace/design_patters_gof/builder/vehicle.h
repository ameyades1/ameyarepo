#ifndef __VEHICLE__
#define __VEHICLE__

#include <string>

class CVehicle
{
public:

	std::string name;
	CVehicle(){};
	virtual ~CVehicle(){}
	CVehicle(std::string _name) {name = _name;}

	virtual void InstallChassis() {};
	virtual void InstallTyres() {};
	virtual void InstallEngine() {};
	virtual void InstallElectronics() {};
	virtual void InstallSeats() {};
	virtual void Paint() {};

	CVehicle& operator=(const CVehicle& v)
	{
		name = v.name;
		return *this;
	}
};

#endif
