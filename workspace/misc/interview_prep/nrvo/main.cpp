#include <iostream>
#include <vector>

// Named Return Value Optimization

std::vector<int> func ()
{
	std::vector<int> a;
	a.push_back(10);
	a.push_back(20);

	std::cout << "Address of a = " << std::hex << &a << "\n";
	return a;
}

int main (int argc, char* argv[])
{
	std::cout << "Named Return Value Optimization \n";
	std::vector<int> b = func();
	std::cout << "Address of b = " << std::hex << &b << "\n";
  std::cout << "b = " << std::dec << b[0] << "--" << b[1] <<"\n";	
	
	return 0;
}


