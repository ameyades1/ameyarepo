#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include <string>
#include "shape.h"

static const float PI = 3.141916;

class CCircle : public CShape
{
	private:
	float m_radius;
	
	public:
	CCircle() 
	{ 
		m_name = "Circle";
		m_radius = 7;
	}
	~CCircle(){};

	float GetArea()
	{
		m_area = PI * m_radius * m_radius;
		return m_area;
	}

};

#endif

