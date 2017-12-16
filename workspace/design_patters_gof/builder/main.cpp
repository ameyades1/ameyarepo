
#include "vehicle.h"
#include "vehicle_builder.h"


int main(int argc, char* argv[])
{
	CVehicle* v1;
	CVehicle* v2;
	CVehicle* v3;

	std::cout << "Builder Design Pattern...\n";

	v1 = CVehicleBuilder::BuildVehicle(CVehicleBuilder::eVehicleType::eCar);
	v2 = CVehicleBuilder::BuildVehicle(CVehicleBuilder::eVehicleType::eBicycle);
	v3 = CVehicleBuilder::BuildVehicle(CVehicleBuilder::eVehicleType::eMotorcycle);

	delete v1;
	delete v2;
	delete v3;

	return 0;
}
