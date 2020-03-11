#include <gtest/gtest.h>
#include "Example.h"

TEST(ExampleTest, isInitialized)
{
    auto example = Example();
    EXPECT_TRUE(example.isInitialized());
}