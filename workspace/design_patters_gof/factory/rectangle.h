#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include <string>
#include "shape.h"

class CRectangle : public CShape
{
	private:
	float m_length;
	float m_width;

	public:
	CRectangle()
	{
		m_name = "Rectangle";
		m_length = 7;
		m_width = 10;
	}
	~CRectangle(){};

	float GetArea()
	{
		m_area = m_length * m_width;
		return m_area;
	}

};

#endif
