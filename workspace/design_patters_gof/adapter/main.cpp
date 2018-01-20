#include <iostream>
#include <list>
#include "polygon.h"
#include "rectangle.h"
#include "circle.h"
#include "circle_shape_adapter.h"

int main(int argc, char* argv[])
{
	CPolygon* p1 = dynamic_cast<CPolygon*> (new CRectangle(Point(2,6), Point(6,2)));
	CPolygon* p2 = dynamic_cast<CPolygon*> (new CCircleShapeAdapter(7));

	std::cout << "Perimeter of polygon p1 = " << p1->Perimeter() << "\n";
	std::cout << "Perimeter of polygon p2 = " << p2->Perimeter() << "\n"; // Perimeter = Circumference

	std::cout << "Area of polygon p1 = " << p1->Area() << "\n";
	std::cout << "Area of polygon p2 = " << p2->Area() << "\n";
	
	delete p1;
	delete p2;

	return 0;
}
