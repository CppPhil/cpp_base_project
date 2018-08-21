#include <iostream>

int main()
{
#ifdef NDEBUG
    std::cout << "Release mode\n";
#else
    std::cout << "Debug mode\n";
#endif
}
