#pragma once

class Calculator
{
  public:
     virtual ~Calculator() = default;

     virtual int add(int a, int b)
     {
	return a+b;
     }

     virtual int multiply(int a, int b)
     {
        return a*b;
     }

     virtual int calculateSumUntil(int n)
     {
        return multiply(n, n+1)/2;
     }
};
