
/*
 *  S Y S T E M   I N C L U D E S
 */
#include <iostream>


/*
 *  C O M P O N E N T   I N C L U D E S
 */
#include "complex.h"

typedef struct _stComplexNos {
	CComplex* pComplex;
	char* cName;
}stComplexNos;


CComplex cNum1(1,2, "cNum1");
CComplex cNum2(cNum1);
CComplex cNum3;
CComplex cNum4;

const char* cNames[] = {"Num1",
				        "Num2",
                        "Num3"
};

stComplexNos stComplexNumbers[] =
{
	{&cNum1, "Num1"},
	{&cNum2, "Num2"},
	{&cNum3, "Num3"},
	{&cNum4, "Num4"},
};

static const unsigned int nNumbers = sizeof (stComplexNumbers) / sizeof (stComplexNumbers[0]);

int main(int argc, char* argv[])
{
	for(unsigned int i = 0; i < nNumbers; i++)
		stComplexNumbers[i].pComplex->setName(stComplexNumbers[i].cName);

	cNum2.setStr("cNum2");
	cNum3.setStr("cNum3");

	cNum1.print();
	cNum2.print(); std::cout <<"\n";

	cNum3 = cNum1 + cNum2;
	std::cout << "cNum3 = cNum1 + cNum2" << "\n";
	cNum3.print(); std::cout <<"\n";

	cNum3 = cNum3 + cNum2;
	std::cout << "cNum3 = cNum3 + cNum2" << "\n";
	cNum3.print(); std::cout <<"\n";

	cNum3 = cNum3 + cNum3;
	std::cout << "cNum3 = cNum3 + cNum3" << "\n";
	cNum3.print(); std::cout <<"\n";

	cNum3 = cNum3 + 4;
	std::cout << "cNum3 = cNum3 + 4" << "\n";
	cNum3.print(); std::cout <<"\n";

	cNum3 = cNum2 * cNum1;
	std::cout << "cNum3 = cNum2 * cNum1" << "\n";
	cNum3.print(); std::cout <<"\n";

	cNum3 = cNum3 * 2;
	std::cout << "cNum3 = cNum3 * 2" << "\n";
	cNum3.print(); std::cout <<"\n";

	cNum3++;
	std::cout << "cNum3++" << "\n";
	cNum3.print(); std::cout << "\n";

	cNum4 = cNum3++;
	std::cout << "cNum4 = cNum3++" << "\n";
	cNum4.print(); std::cout << "\n";
	cNum3.print(); std::cout << "\n";

	cNum4 = ++cNum4;
	std::cout << "cNum4 = ++cNum4" << "\n";
	cNum4.print(); std::cout << "\n";
	return 0;
}


