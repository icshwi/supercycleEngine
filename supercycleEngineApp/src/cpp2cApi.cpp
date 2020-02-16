#include "cpp2cApi.hpp"

#include <iostream>

extern "C" void prints(char *args)
{
    std::cout << args << std::endl;
}

extern "C" void printn(long int argl)
{
    std::cout << argl << std::endl;
}
