#ifndef __CIRCLESHAPE__
#define __CIRCLESHAPE__

#include <iostream>
#include "polygon.h"
#include "circle.h"

class CCircleShapeAdapter : public CPolygon
{

public:
	CCircleShapeAdapter()
	{
		c = NULL;
	}
	~CCircleShapeAdapter()
	{
		if (c)
			delete c;
	}

	CCircle *c;

	CCircleShapeAdapter(float radius)
	{
		c = new CCircle(radius);
		Point p;
		p.x = radius;
		p.y = radius;

		lPoints.push_back(p);
	}

	float Perimeter()
	{
		return c->Circumference();
	}

	float Area()
	{
		return c->CircleArea();
	}
};
#endif
