#include "scg/linear/Vector2.hpp"
#include "gtest/gtest.h"

TEST(Vector2Test, DefaultConstructor)
{
    SCG::Vector2 v;
    EXPECT_EQ(0.0f, v[0]);
    EXPECT_EQ(0.0f, v[1]);
}

TEST(Vector2Test, CoordinateConstructor)
{
    SCG::Vector2 v(1.0f, 2.0f);
    EXPECT_EQ(1.0f, v[0]);
    EXPECT_EQ(2.0f, v[1]);
}

TEST(Vector2Test, InitializerListAndIndexOperator)
{
    SCG::Vector2 v({1.0f, 2.0f});
    EXPECT_EQ(1.0f, v[0]);
    EXPECT_EQ(2.0f, v[1]);
}

TEST(Vector2Test, XAccessor)
{
    SCG::Vector2 v({1.0f, 2.0f});
    EXPECT_EQ(1.0f, v.X());
}

TEST(Vector2Test, YAccessor)
{
    SCG::Vector2 v({1.0f, 2.0f});
    EXPECT_EQ(2.0f, v.Y());
}

TEST(Vector2Test, Rotate)
{
    constexpr float pi = 3.1415926535897932;

    SCG::Vector2 v({1.0f, 0.0f});
    SCG::Vector2 u = v.Rotate(pi / 2.0);
    EXPECT_NEAR(0.0f, u.X(), 1e-6f);
    EXPECT_NEAR(1.0f, u.Y(), 1e-6f);
}