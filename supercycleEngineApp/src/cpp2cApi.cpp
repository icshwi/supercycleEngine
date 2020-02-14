#include "cpp2cApi.hpp"

#include <iostream>
extern "C" int print(int i, double d)
{
    std::cout << "i = " << i << ", d = " << d << std::endl;
}
