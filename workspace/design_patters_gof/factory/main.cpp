
#include <iostream>
#include <string>

#include "shape.h"
#include "shapefactory.h"
#include "circle.h"
#include "rectangle.h"
#include "square.h"

int main(int argc, char* argv[])
{
	/* We deal in shapes only. Not what type of shape.
	 * Only create (pointers) objects of shape.
	 * Not child classes. The type of shape must have all
	 * characteristics of shape to be useful.
	 * Higher level of abstraction.
	 */

	CShape* shape1;
	CShape* shape2;
	CShape* shape3;

	shape1 = CShapeFactory::GetShape("Circle");
	std::cout << "Class = " << shape1->GetName() << " -- " << "Area = " << shape1->GetArea() << "\n";

	shape2 = CShapeFactory::GetShape("Rectangle");
	std::cout << "Class = " << shape2->GetName() << " -- " << "Area = " << shape2->GetArea() << "\n";

	shape3 = CShapeFactory::GetShape("Square");
	std::cout << "Class = " << shape3->GetName() << " -- " << "Area = " << shape3->GetArea() << "\n";
	
	delete shape1;
	delete shape2;
	delete shape3;

	return 0;
}

