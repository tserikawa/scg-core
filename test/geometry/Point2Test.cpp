#include "scg/linear/Vector2.hpp"
#include "scg/geometry/Point2.hpp"
#include <gtest/gtest.h>

TEST(Point2Test, CoordinateConstructorAndXYAccesser)
{
    SCG::Point2 p(1.0f, 2.0f);
    EXPECT_NEAR(1.0f, p.X(), 1e-6f);
    EXPECT_NEAR(2.0f, p.Y(), 1e-6f);
}

TEST(Point2Test, DistanceTo)
{
    SCG::Point2 p1(1.0f, 1.0f);
    SCG::Point2 p2(4.0f, 5.0f);
    EXPECT_NEAR(5.0f, p1.DistanceTo(p2), 1e-6f);
}

TEST(Point2Test, AddVector2Operator)
{
    SCG::Point2 p(1.0f, 1.0f);
    SCG::Vector2 v({1.0f, 2.0f});
    SCG::Point2 pv = p + v;
    EXPECT_NEAR(2.0f, pv.X(), 1e-6f);
    EXPECT_NEAR(3.0f, pv.Y(), 1e-6f);
}

TEST(Point2Test, SubstractVector2Operator)
{
    SCG::Point2 p1(1.0f, 1.0f);
    SCG::Point2 p2(4.0f, 5.0f);
    SCG::Vector2 v = p2 - p1;
    EXPECT_NEAR(3.0f, v.X(), 1e-6f);
    EXPECT_NEAR(4.0f, v.Y(), 1e-6f);
}

TEST(Point2Test, EqualOperator)
{
    SCG::Point2 p1(1.0f, 1.0f);
    SCG::Point2 p2(1.0f, 1.0f);
    SCG::Point2 p3(4.0f, 5.0f);
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}
