#ifndef __CIRCLE__
#define __CIRCLE__
class CCircle
{
	float radius;
public:
	CCircle() {}
	virtual ~CCircle() {}

	// R, theta
	CCircle(float _radius) { radius = _radius; }

	virtual float CircleArea()
	{
		return 3.14 * radius * radius;
	}

	virtual float Circumference()
	{
		return 2 * 3.14 * radius;
	}

};
#endif
