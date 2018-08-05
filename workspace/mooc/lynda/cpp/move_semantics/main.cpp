#include <iostream>
#include <vector>

void display(std::vector<std::string>& v)
{
  std::cout << v;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> v1 = {"one", "two", "three", "four", "five"};
  std::vector<std::string> v2 = {"six", "seven", "eight", "nine", "ten"};
  
  display(v1);	
  display(v2);
  
  return 0;
}
