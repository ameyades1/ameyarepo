#ifndef __VEHICLE_BUILDER__
#define __VEHICLE_BUILDER__

#include "vehicle.h"
#include "car.h"
#include "bicycle.h"
#include "motorcycle.h"
#include <string>

class CVehicleBuilder
{
	public:
	typedef enum _eVehicleType
	{
		eCar = 0,
		eBicycle,
		eMotorcycle
	}eVehicleType;

	CVehicleBuilder() {}
	~CVehicleBuilder() {}
	static 	CVehicle* BuildVehicle(eVehicleType vtype)
	{
		CVehicle* vehicle;
		switch(vtype)
		{
		case eCar:
				vehicle = new CCar("Maruti Swift");
				std::cout << "\n\nBuilding " << vehicle->name <<"\n";
				vehicle->InstallChassis();
				vehicle->InstallElectronics();
				vehicle->InstallEngine();
				vehicle->InstallSeats();
				vehicle->InstallTyres();
				break;

		case eBicycle:
				vehicle = new CBicycle("Shimano");
				std::cout << "\n\nBuilding " << vehicle->name <<"\n";
				vehicle->InstallChassis();
				vehicle->InstallSeats();
				vehicle->InstallTyres();
				break;

		default:
		case eMotorcycle:
				vehicle = new CMotorcycle("Bajaj Pulsar");
				std::cout << "\n\nBuilding " << vehicle->name <<"\n";
				vehicle->InstallChassis();
				vehicle->InstallElectronics();
				vehicle->InstallEngine();
				vehicle->InstallSeats();
				vehicle->InstallTyres();
				break;
		}

		return vehicle;
	}
};
#endif
