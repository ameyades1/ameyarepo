#include "large_simulation.h"
#include "physics_simulation.h"
#include "chip_simulation.h"

int main(int argc, char* argv[])
{
	/*
	 * Prototype design pattern
	 * We avoid creation costs of one object to create other objects.
	 * Make copies created of objects to save time in creating them.
	 */

	// The dynamic casts are due to strict implementation of makeCopy interface.
	// Could have avoided, but then cant guarantee uniform implementation of makeCopy()
	// across all implementors

	std::cout << "---Prototype Design Pattern---\n";
	std::cout << "Create copies for reuse by avoiding creation costs of one object.\n\n";

	CPhysicsSimulation phy1(6.28);
	std::cout <<"Large simulation phy1 complete. FunkyEinsteinValue = " << phy1.fEinsteinParameter << "\n\n";

	CPhysicsSimulation* phy2 = dynamic_cast<CPhysicsSimulation*>(phy1.makeCopy());
	std::cout <<"Reusing large simulation phy1 results in phy2. FunkyEinsteinValue = " << phy2->fEinsteinParameter << "\n";
	phy2->SimulateAhead(10);

	std::cout << "\n";
	CChipSimulation csim1;
	std::cout << "Gate level simulation of csim1 finished.\n\n";

	CChipSimulation* csim2 = dynamic_cast<CChipSimulation*> (csim1.makeCopy());
	std::cout << "Reusing booted linux simulation csim1 in csim 2...\n";
	csim2->SimulateDrivers(false);

	delete phy2;
	delete csim2;

	return 0;
}
