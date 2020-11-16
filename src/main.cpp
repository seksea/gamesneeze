#include <iostream>

void __attribute__((constructor)) DllEntryPoint()
{
    std::cout << "Injected!\n";
}