#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/client.hpp"
#include "test_calculator.hpp"

using ::testing::InSequence;

TEST(ClientTest, SpecialOpsTest)
{
   MockCalculator mockCalc;

   {
     InSequence seq;

     EXPECT_CALL(mockCalc, add(2,3))
      .Times(1)
      .WillOnce(::testing::Return(5));

     EXPECT_CALL(mockCalc, multiply(5, 10))
      .Times(1)
      .WillOnce(::testing::Return(100));
   }

   Client client(&mockCalc);

   int result= client.calculateSpecialValue(2,3);

   EXPECT_EQ(result, 100);
}

TEST(ClientTest, CalculateSumUntilTest)
{
   MockCalculator mockCalc;

   EXPECT_CALL(mockCalc, multiply(10, 11))
      .Times(1)
      .WillOnce(::testing::Return(110));

   Client client(&mockCalc);

   int result= client.calculateSumUntil(10);

   EXPECT_EQ(result, 55); 
}

TEST(ClientTest, doSomeCalculationTest)
{
   MockCalculator mockCalc;

   EXPECT_CALL(mockCalc, multiply(2,3))
      .Times(1)
      .WillOnce(::testing::Return(6));

   //EXPECT_CALL(mockCalc, multiply(4,5))
   //   .Times(1)
   //   .WillOnce(::testing::Return(20));
   
   EXPECT_CALL(mockCalc, multiply(4,5))
      .Times(2)
      .WillRepeatedly(::testing::Return(20));
  
   // Compbine the 2 add calls 
   //EXPECT_CALL(mockCalc, add(26, 5)
   //   .Times(1)
   //   .WillOnce(::testing::Return(31));

   //EXPECT_CALL(mockCalc, add(3,4))
   //   .Times(1)
   //   .WillOnce(::testing::Return(7));

   EXPECT_CALL(mockCalc, add(::testing::_,::testing:: _))
      .Times(2)
      .WillOnce(::testing::Return(31))    // add(res, n+3)
      .WillOnce(::testing::Return(7));    // add(n+1, n+2) 

   EXPECT_CALL(mockCalc, calculateSumUntil(27))
      .Times(1)
      .WillOnce(::testing::Return(378));

   Client client(&mockCalc);

   int result= client.doSomeCalculation(2);

   EXPECT_EQ(result, 378);
}

TEST(ClientTest, notFibTest)
{
  MockCalculator mockCalc;

  // In real, when the code runs, it calculates not_fib(5) as 5
  // which is basically 6th number in the fib series {0, 1, 1, 2, 3, 5}
  // As we dont expect any return, we return 1 always, 
  // which is getting printed always as the real call was intercepted by
  // GoogleMock framework and returns the set values.
  EXPECT_CALL(mockCalc, add(::testing::_,::testing::_))
     .Times(::testing::Exactly(2 * 5))  // since inside while(i<=n)
     .WillRepeatedly(::testing::Return(1)); // dummy return 

  Client client(&mockCalc);
  client.not_fib(5);
  // no result to expect or compare.
}

TEST(ClientTest, fibReturnsTest)
{
  MockCalculator mockCalc;

  // Finding the 4th number in the fibonacci series: 
  // {0, 1, 1, 2, 3, 5, 8, ......} which is 2.
  EXPECT_CALL(mockCalc, add(::testing::_,::testing::_))
     .Times(::testing::Exactly(2))  // (n-2) calls when n=4 
     .WillRepeatedly([](int a, int b){ return a + b; }); // actual return

  Client client(&mockCalc);
  int result= client.fib_returns(4);
  
  //EXPECT_GT(result, 0);
  EXPECT_EQ(result, 2);
}
