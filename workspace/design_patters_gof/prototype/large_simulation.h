#ifndef __LARGEOBJ__
#define __LARGEOBJ__

#include <cstdio>

class CLargeSimulation
{

public:
	CLargeSimulation() {}
	virtual ~CLargeSimulation() {}

	virtual CLargeSimulation* makeCopy() = 0;
};

#endif
