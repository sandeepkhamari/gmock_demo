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
