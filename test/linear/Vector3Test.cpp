#include "scg/linear/Vector3.hpp"
#include "gtest/gtest.h"

TEST(Vector3Test, DefaultConstructor)
{
    SCG::VectorBase<SCG::Vector3, 3> v;
    EXPECT_EQ(0.0f, v[0]);
    EXPECT_EQ(0.0f, v[1]);
    EXPECT_EQ(0.0f, v[2]);
}

TEST(Vector3Test, InitializerListAndIndexOperator)
{
    SCG::VectorBase<SCG::Vector3, 3> v({1.0f, 2.0f, 3.0f});
    EXPECT_EQ(1.0f, v[0]);
    EXPECT_EQ(2.0f, v[1]);
    EXPECT_EQ(3.0f, v[2]);
}

TEST(Vector3Test, InitializerListSizeMismatch)
{
    EXPECT_THROW(
        []
        { SCG::Vector3 v({1.0f, 2.0f}); }(),
        std::invalid_argument);
}

TEST(Vector3Test, IndexOperatorOutOfRange)
{
    EXPECT_THROW(
        []
        {
            SCG::Vector3 v({1.0f, 2.0f, 3.0f});
            float v3 = v[3];
        }(),
        std::out_of_range);
}

TEST(Vector3Test, AddOperator)
{
    SCG::VectorBase<SCG::Vector3, 3> a({1.0f, 2.0f, 3.0f});
    SCG::Vector3 b({0.25f, 0.5f, 0.75f});
    SCG::Vector3 c = a + b;
    EXPECT_EQ(1.25f, c[0]);
    EXPECT_EQ(2.5f, c[1]);
    EXPECT_EQ(3.75f, c[2]);
}

TEST(Vector3Test, SubstractOperator)
{
    SCG::Vector3 a({1.0f, 2.0f, 3.0f});
    SCG::Vector3 b({0.25f, 0.5f, 0.75f});
    SCG::Vector3 c = a - b;
    EXPECT_EQ(0.75f, c[0]);
    EXPECT_EQ(1.5f, c[1]);
    EXPECT_EQ(2.25f, c[2]);
}

TEST(Vector3Test, MultiplyOperator)
{
    SCG::Vector3 a({1.0f, 2.0f, 3.0f});
    SCG::Vector3 b({0.25f, 0.5f, 0.75f});
    SCG::Vector3 c = a * b;
    EXPECT_EQ(0.25f, c[0]);
    EXPECT_EQ(1.0f, c[1]);
    EXPECT_EQ(2.25f, c[2]);
}

TEST(Vector3Test, DivideFloatOperator)
{
    SCG::Vector3 a({1.0f, 2.0f, 3.0f});
    SCG::Vector3 b = a / 2.0f;
    EXPECT_NEAR(0.5f, b[0], 1e-6f);
    EXPECT_NEAR(1.0f, b[1], 1e-6f);
    EXPECT_NEAR(1.5f, b[2], 1e-6f);
}

TEST(Vector3Test, DivideFloatOperatorZeroDivision)
{
    EXPECT_THROW(
        []
        {
            SCG::Vector3 a({1.0f, 2.0f, 3.0f});
            SCG::Vector3 b = a / 0.0f;
        }(),
        std::domain_error);
}

TEST(Vector3Test, AddAssignOperator)
{
    SCG::Vector3 a({1.0f, 2.0f, 3.0f});
    a += 0.5f;
    EXPECT_EQ(1.5f, a[0]);
    EXPECT_EQ(2.5f, a[1]);
    EXPECT_EQ(3.5f, a[2]);
}

TEST(Vector3Test, SubstractAssignOperator)
{
    SCG::Vector3 a({1.0f, 2.0f, 3.0f});
    a -= 0.5f;
    EXPECT_EQ(0.5f, a[0]);
    EXPECT_EQ(1.5f, a[1]);
    EXPECT_EQ(2.5f, a[2]);
}

TEST(Vector3Test, MultiplyAssignOperator)
{
    SCG::Vector3 a({1.0f, 2.0f, 3.0f});
    a *= 0.5f;
    EXPECT_EQ(0.5f, a[0]);
    EXPECT_EQ(1.0f, a[1]);
    EXPECT_EQ(1.5f, a[2]);
}

TEST(Vector3Test, DivideAssignFloatOperatorZeroDivision)
{
    EXPECT_THROW(
        []
        {
            SCG::Vector3 a({1.0f, 2.0f, 3.0f});
            a /= 0.0f;
        }(),
        std::domain_error);
}
TEST(Vector3Test, EqualOperator)
{
    SCG::Vector3 a({1.0f, 2.0f, 3.0f});
    SCG::Vector3 b({1.0f, 2.0f, 3.0f});
    EXPECT_TRUE(a == b);
}

TEST(Vector3Test, EqualOperatorFalse)
{
    SCG::Vector3 a({1.0f, 2.0f, 3.0f});
    SCG::Vector3 b({1.25f, 2.0f, 3.0f});
    EXPECT_FALSE(a == b);
}

TEST(Vector3Test, DotProduct)
{
    SCG::Vector3 a({1.0f, 2.0f, 3.0f});
    SCG::Vector3 b({1.0f, 0.5f, 1.5f});
    EXPECT_EQ(6.5f, a.Dot(b));
}

TEST(Vector3Test, Length)
{
    SCG::Vector3 a({2.0f, 3.0f, 6.0f});
    EXPECT_EQ(7.0f, a.Length());
}

TEST(Vector3Test, Normalize)
{
    SCG::Vector3 a({2.0f, 3.0f, 6.0f});
    EXPECT_EQ(1.0f, a.Normalize().Length());
}

TEST(Vector3Test, NormalizeZeroVector)
{
    SCG::Vector3 a({0.0f, 0.0f, 0.0f});
    EXPECT_THROW(a.Normalize(), std::domain_error);
}

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