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

TEST(Vector2Test, InitializerListSizeMismatch)
{
    EXPECT_THROW(
        []
        { SCG::Vector2 v({1.0f, 2.0f, 3.0f}); }(),
        std::invalid_argument);
}

TEST(Vector2Test, IndexOperatorOutOfRange)
{
    EXPECT_THROW(
        []
        {
            SCG::Vector2 v({1.0f, 2.0f});
            float v2 = v[2];
        }(),
        std::out_of_range);
}

TEST(Vector2Test, AddOperator)
{
    SCG::Vector2 a({1.0f, 2.0f});
    SCG::Vector2 b({0.25f, 0.5f});
    SCG::Vector2 c = a + b;
    EXPECT_EQ(1.25f, c[0]);
    EXPECT_EQ(2.5f, c[1]);
}

TEST(Vector2Test, SubstractOperator)
{
    SCG::Vector2 a({1.0f, 2.0f});
    SCG::Vector2 b({0.25f, 0.5f});
    SCG::Vector2 c = a - b;
    EXPECT_EQ(0.75f, c[0]);
    EXPECT_EQ(1.5f, c[1]);
}

TEST(Vector2Test, MultiplyOperator)
{
    SCG::Vector2 a({1.0f, 2.0f});
    SCG::Vector2 b({0.25f, 0.5f});
    SCG::Vector2 c = a * b;
    EXPECT_EQ(0.25f, c[0]);
    EXPECT_EQ(1.0f, c[1]);
}

TEST(Vector2Test, MultiplyMatrixOperator)
{
    SCG::Vector2 a({1.0f, 2.0f});
    SCG::MatrixNN<2> m({{2.0f, 1.0f},
                        {3.0f, -1.0f}});
    SCG::Vector2 am = a * m;
    EXPECT_NEAR(8.0f, am[0], 1e-6f);
    EXPECT_NEAR(-1.0f, am[1], 1e-6f);
}

TEST(Vector2Test, DivideFloatOperator)
{
    SCG::Vector2 a({1.0f, 2.0f});
    SCG::Vector2 b = a / 2.0f;
    EXPECT_NEAR(0.5f, b[0], 1e-6f);
    EXPECT_NEAR(1.0f, b[1], 1e-6f);
}

TEST(Vector2Test, DivideFloatOperatorZeroDivision)
{
    EXPECT_THROW(
        []
        {
            SCG::Vector2 a({1.0f, 2.0f});
            SCG::Vector2 b = a / 0.0f;
        }(),
        std::domain_error);
}

TEST(Vector2Test, AddAssignOperator)
{
    SCG::Vector2 a({1.0f, 2.0f});
    a += 0.5f;
    EXPECT_EQ(1.5f, a[0]);
    EXPECT_EQ(2.5f, a[1]);
}

TEST(Vector2Test, SubstractAssignOperator)
{
    SCG::Vector2 a({1.0f, 2.0f});
    a -= 0.5f;
    EXPECT_EQ(0.5f, a[0]);
    EXPECT_EQ(1.5f, a[1]);
}

TEST(Vector2Test, MultiplyAssignOperator)
{
    SCG::Vector2 a({1.0f, 2.0f});
    a *= 0.5f;
    EXPECT_EQ(0.5f, a[0]);
    EXPECT_EQ(1.0f, a[1]);
}

TEST(Vector2Test, DivideAssignFloatOperator)
{
    SCG::Vector2 a({1.0f, 2.0f});
    a /= 2.0f;
    EXPECT_NEAR(0.5f, a[0], 1e-6f);
    EXPECT_NEAR(1.0f, a[1], 1e-6f);
}

TEST(Vector2Test, DivideAssignFloatOperatorZeroDivision)
{
    EXPECT_THROW(
        []
        {
            SCG::Vector2 a({1.0f, 2.0f});
            a /= 0.0f;
        }(),
        std::domain_error);
}
TEST(Vector2Test, EqualOperator)
{
    SCG::Vector2 a({1.0f, 2.0f});
    SCG::Vector2 b({1.0f, 2.0f});
    EXPECT_TRUE(a == b);
}

TEST(Vector2Test, EqualOperatorFalse)
{
    SCG::Vector2 a({1.0f, 2.0f});
    SCG::Vector2 b({1.25f, 2.0f});
    EXPECT_FALSE(a == b);
}

TEST(Vector2Test, DotProduct)
{
    SCG::Vector2 a({1.0f, 2.0f});
    SCG::Vector2 b({1.0f, 0.5f});
    EXPECT_EQ(2.0f, a.Dot(b));
}

TEST(Vector2Test, Length)
{
    SCG::Vector2 a({3.0f, 4.0f});
    EXPECT_EQ(5.0f, a.Length());
}

TEST(Vector2Test, Normalize)
{
    SCG::Vector2 a({3.0f, 4.0f});
    EXPECT_EQ(1.0f, a.Normalize().Length());
}

TEST(Vector2Test, NormalizeZeroVector)
{
    SCG::Vector2 a({0.0f, 0.0f});
    EXPECT_THROW(a.Normalize(), std::domain_error);
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