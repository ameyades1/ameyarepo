#ifndef __SHAPE_H__
#define __SHAPE_H__

#include <string>
class CShape
{
protected:
	std::string m_name;
	float m_area;

public:
	CShape() {m_area = 0;};
	virtual ~CShape() {};

	std::string GetName() { return m_name; } ;
	virtual float GetArea() = 0;

};

#endif
