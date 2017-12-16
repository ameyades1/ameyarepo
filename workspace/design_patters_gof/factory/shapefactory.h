#ifndef __FACTORY_H__
#define __FACTORY_H__

#include "shape.h"
#include "circle.h"
#include "rectangle.h"
#include "square.h"

class CShapeFactory 
{
	private:
	CShapeFactory() {};
	~CShapeFactory() {};

	public:
	static CShape* GetShape(std::string shape_name)
	{
		if(shape_name == "Circle")
		{
			CCircle* circle = new CCircle();
			return dynamic_cast<CShape*>(circle);
		}
		else if(shape_name == "Rectangle")
		{
			CRectangle* rect = new CRectangle();
			return dynamic_cast<CShape*>(rect);
		}
		else if (shape_name == "Square")
		{
			CSquare* square = new CSquare();
			return dynamic_cast<CShape*>(square);
		}
		else
			return NULL;
	}
};

#endif
