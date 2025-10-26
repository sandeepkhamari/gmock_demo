#include <iostream>
#include "calculator.hpp"

class Client
{
  public:
      // use pointer so that we can inject a mock.
      Calculator *calc;

      Client(Calculator* c): calc(c) {}

      //1.virtual int testFunc(int val) no effect
      //2.virtual int testFunc(int& val)  mock test fails, as it modifies res value.
      virtual int testFunc(int val)
      {
          val++;
	  return val;
      }
   
      virtual int calculateSpecialValue(int a, int b)
      {
         int res= calc->add(a,b);
	 // it doesnt break the mock as it doesnt change any value
	 // that is used after this step.
	 //1.testFunc(res);
	 testFunc(res);
	 return calc->multiply(res, 10);
      }

      virtual int calculateSumUntil(int n)
      {
         return calc->multiply(n, n+1)/2;
      }

      virtual int doSomeCalculation(int n)
      {
         int res  = calc->multiply(n, n+1) + calc->multiply(n+2, n+3);
         calc->add(res, n+3);
         int res1 = calc->multiply(n+2, n+3) + calc->add(n+1, n+2);
         int res2 = calc->calculateSumUntil(res1); 
         return res2;
      }
};
