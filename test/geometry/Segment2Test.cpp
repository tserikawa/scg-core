#include "scg/linear/Vector2.hpp"
#include "scg/geometry/Point2.hpp"
#include "scg/geometry/Segment2.hpp"
#include <gtest/gtest.h>

TEST(Segment2Test, ConstructorAndEndsAccesser)
{
    SCG::Point2 start(0.0f, 0.0f);
    SCG::Point2 end(3.0f, 4.0f);
    SCG::Segment2 s(start, end);
    EXPECT_TRUE(s.Start() == start);
    EXPECT_TRUE(s.End() == end);
}

TEST(Segment2Test, MidPoint)
{
    SCG::Point2 start(1.0f, 1.0f);
    SCG::Point2 end(4.0f, 5.0f);
    SCG::Segment2 s(start, end);
    EXPECT_TRUE(s.MidPoint() == SCG::Point2(2.5f, 3.0f));
}

TEST(Segment2Test, Length)
{
    SCG::Point2 start(1.0f, 1.0f);
    SCG::Point2 end(4.0f, 5.0f);
    SCG::Segment2 s(start, end);
    EXPECT_TRUE(s.Length() == 5.0f);
}

TEST(Segment2Test, Direction)
{
    SCG::Point2 start(1.0f, 1.0f);
    SCG::Point2 end(3.0f, 4.0f);
    SCG::Segment2 s(start, end);
    EXPECT_TRUE(s.Direction(false) == SCG::Vector2(2.0f, 3.0f));
}

TEST(Segment2Test, DirectionNormalized)
{
    SCG::Point2 start(1.0f, 1.0f);
    SCG::Point2 end(4.0f, 5.0f);
    SCG::Segment2 s(start, end);
    EXPECT_TRUE(s.Direction(true) == SCG::Vector2(0.6f, 0.8f));
}
