#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/client.hpp"

// mock class
class MockClient: public Client
{
   public:
      MOCK_METHOD(int, fact, (int n), (override));
};


