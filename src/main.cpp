#include <iostream>
#include "../include/calculator.hpp"

int main()
{
   Calculator calc;
   std::cout<<"add(2,3): "<<calc.add(2,3)<<std::endl;
   std::cout<<"multiply(2,3): "<<calc.multiply(2,3)<<std::endl;
   return 0;
}
