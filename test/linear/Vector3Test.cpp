#include "scg/linear/Vector3.hpp"
#include "gtest/gtest.h"

TEST(Vector3Test, XAccessor)
{
    SCG::Vector3 v({1.0f, 2.0f, 3.0f});
    EXPECT_EQ(1.0f, v.X());
}

TEST(Vector3Test, YAccessor)
{
    SCG::Vector3 v({1.0f, 2.0f, 3.0f});
    EXPECT_EQ(2.0f, v.Y());
}

TEST(Vector3Test, ZAccessor)
{
    SCG::Vector3 v({1.0f, 2.0f, 3.0f});
    EXPECT_EQ(3.0f, v.Z());
}

TEST(Vector3Test, CrossProduct)
{
    SCG::Vector3 a({1.0f, 0.0f, 0.0f});
    SCG::Vector3 b({0.0f, 1.0f, 0.0f});
    SCG::Vector3 axb = a.Cross(b);
    EXPECT_NEAR(0.0f, axb.X(), 1e-6f);
    EXPECT_NEAR(0.0f, axb.Y(), 1e-6f);
    EXPECT_NEAR(1.0f, axb.Z(), 1e-6f);
}