#ifndef __SQUARE_H__
#define __SQUARE_H__

#include <string>
#include "shape.h"

class CSquare : public CShape
{
	private:
	float m_side;

	public:
	CSquare()
	{
		m_name = "Square";
		m_side = 7;
	}
	~CSquare(){};

	float GetArea()
	{
		m_area = m_side * m_side;
		return m_area;
	}

};

#endif
