#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/calculator.hpp"
#include "test_calculator.hpp"

TEST(CalculatorTest, AddTest)
{
   MockCalculator calc;

   //EXPECT_CALL(calc, add(2,3))
   EXPECT_CALL(calc, add(2,3))
       .Times(1)
       .WillOnce(::testing::Return(11));

   int result= calc.add(2,3);
   EXPECT_EQ(result, 11);
}

TEST(CalculatorTest, MultiplyTest)
{
   MockCalculator calc;

   EXPECT_CALL(calc, multiply(::testing::_, 5))
       .Times(1)
       .WillOnce(::testing::Return(50));

   int result= calc.multiply(7,5);
   EXPECT_EQ(result, 50);
}
