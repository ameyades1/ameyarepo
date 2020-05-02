
#include <cstdlib>
#include "my_malloc.hpp"


int main(int argc, char* argv[])
{
    char* ptr = (char*)my_malloc(100);
    return 0;
}
