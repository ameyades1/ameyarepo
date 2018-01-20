#ifndef __POLYGON__
#define __POLYGON__

#include <list>

class Point
{
public:
	float x;
	float y;

	Point () {};
	Point (float _x, float _y)
	{
		x = _x;
		y = _y;
	}
};

class CPolygon
{
protected:
	std::list <Point> lPoints;

public:
	CPolygon() {}
	virtual ~CPolygon() {};

	virtual float Perimeter() { return 0; }
	virtual float Area() { return 0; }

};
#endif
