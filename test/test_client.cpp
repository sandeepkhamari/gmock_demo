#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/client.hpp"
#include "test_calculator.hpp"
#include "test_client.hpp"

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

TEST(ClientTest, factorialTest)
{
  MockCalculator mockCalc;

  EXPECT_CALL(mockCalc, multiply(::testing::_, ::testing::_))
     .Times(::testing::Exactly(5))
     .WillRepeatedly([](int a, int b){ return a*b; });

  Client client(&mockCalc);
  int result= client.factorial(5);

  EXPECT_EQ(result, 120); 
}

// Let the mock fallback to real recurssive behaviour.
TEST(ClientTest, factTest)
{
  MockClient mockClient;

  //EXPECT_CALL(mockClient, fact(5))
     //.Times(::testing::Exactly(1))
     //.WillOnce(::testing::Return(120));

  //EXPECT_CALL(mockClient, fact(4))
     //.Times(::testing::Exactly(1))
     //.WillOnce(::testing::Return(24));

  //EXPECT_CALL(mockClient, fact(3))
     //.Times(::testing::Exactly(1))
     //.WillOnce(::testing::Return(6));

  //EXPECT_CALL(mockClient, fact(2))
     //.Times(::testing::Exactly(1))
     //.WillOnce(::testing::Return(2));

  //EXPECT_CALL(mockClient, fact(1))
     //.Times(::testing::Exactly(1))
     //.WillOnce(::testing::Return(1)); 

  // Allow real recurssive behaviour by default.
  ON_CALL(mockClient, fact(::testing::_))
      .WillByDefault(::testing::Invoke([&mockClient](int n) {
          if( n==0 || n==1 )
	    return 1;
	  return n* mockClient.fact(n-1);
      }));

  EXPECT_CALL(mockClient, fact(::testing::_))
     .Times(::testing::AtLeast(1));

  Client client(&mockClient);
  int result= client.fact(5);

  EXPECT_EQ(result, 120);

  //EXPECT_CALL(mockClient, fact(::testing::_))
  //   .Times(::testing::Exactly(5))
  //   .WillRepeatedly(::testing::Return([](int n){ return n; }));

  //Client client;
  //int result= client.fact(5);

  //EXPECT_EQ(result, 120);
}

// test only the top-level call.
TEST(ClientTest, factTopLvlTest)
{
   MockClient mockClient;

   // fact(5) is real call to the fact() in Client class.
   // whereas fact(4) is intercepted by the google mock.
   // But the result will be calculated as per the method logic.
   // fact(3), fact(2) and fact(1) are neither mocked nor called.
   // result= fact(5)->5 * fact(4)->24 = 120
   EXPECT_CALL(mockClient, fact(4))
      .Times(1)
      .WillOnce(::testing::Return(24));

   Client client(&mockClient);

   int result= client.fact(5);

   EXPECT_EQ(result, 120);
}
