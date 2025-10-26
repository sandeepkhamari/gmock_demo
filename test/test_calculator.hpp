#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/calculator.hpp"

//mock class
class MockCalculator: public Calculator
{
   public:
       MOCK_METHOD(int, add, (int a, int b), (override));
       MOCK_METHOD(int, multiply, (int a, int b), (override));
       MOCK_METHOD(int, calculateSumUntil, (int n), (override));
};
