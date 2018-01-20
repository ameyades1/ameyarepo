#ifndef __RECTANGLE__
#define  __RECTANGLE__

#include "polygon.h"
#include <cmath>

class CRectangle : public CPolygon
{
public:
	CRectangle() {}
	~CRectangle() {}

	CRectangle (Point p1, Point p2)
	{
		lPoints.push_back(p1);
		lPoints.push_back(p2);
	}

	float Perimeter ()
	{
		// Just two points
		Point p1 = lPoints.front();
		Point p2 = lPoints.back();

		return (2 * fabs(p1.x - p2.x) + fabs(p1.y - p2.y));
	}

	float Area ()
	{
		// Just two points
		Point p1 = lPoints.front();
		Point p2 = lPoints.back();

		return (fabs(p1.x - p2.x) * fabs(p1.y - p2.y));
	}
};
#endif
