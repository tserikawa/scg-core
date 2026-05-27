#include "scg/linear/VectorN.hpp"
#include "scg/linear/MatrixNN.hpp"
#include <gtest/gtest.h>

TEST(VectorNTest, DefaultConstructor)
{
    SCG::VectorN<3> v;
    EXPECT_EQ(0.0f, v[0]);
    EXPECT_EQ(0.0f, v[1]);
    EXPECT_EQ(0.0f, v[2]);
}

TEST(VectorNTest, InitializerListAndIndexOperator)
{
    SCG::VectorN<3> v({1.0f, 2.0f, 3.0f});
    EXPECT_EQ(1.0f, v[0]);
    EXPECT_EQ(2.0f, v[1]);
    EXPECT_EQ(3.0f, v[2]);
}

TEST(VectorNTest, InitializerListSizeMismatch)
{
    EXPECT_THROW(
        []
        { SCG::VectorN<3> v({1.0f, 2.0f}); }(),
        std::invalid_argument);
}

TEST(VectorNTest, IndexOperatorOutOfRange)
{
    EXPECT_THROW(
        []
        {
            SCG::VectorN<3> v({1.0f, 2.0f, 3.0f});
            float v3 = v[3];
        }(),
        std::out_of_range);
}

TEST(VectorNTest, AddOperator)
{
    SCG::VectorN<3> a({1.0f, 2.0f, 3.0f});
    SCG::VectorN<3> b({0.25f, 0.5f, 0.75f});
    SCG::VectorN<3> c = a + b;
    EXPECT_EQ(1.25f, c[0]);
    EXPECT_EQ(2.5f, c[1]);
    EXPECT_EQ(3.75f, c[2]);
}

TEST(VectorNTest, SubstractOperator)
{
    SCG::VectorN<3> a({1.0f, 2.0f, 3.0f});
    SCG::VectorN<3> b({0.25f, 0.5f, 0.75f});
    SCG::VectorN<3> c = a - b;
    EXPECT_EQ(0.75f, c[0]);
    EXPECT_EQ(1.5f, c[1]);
    EXPECT_EQ(2.25f, c[2]);
}

TEST(VectorNTest, MultiplyOperator)
{
    SCG::VectorN<3> a({1.0f, 2.0f, 3.0f});
    SCG::VectorN<3> b({0.25f, 0.5f, 0.75f});
    SCG::VectorN<3> c = a * b;
    EXPECT_EQ(0.25f, c[0]);
    EXPECT_EQ(1.0f, c[1]);
    EXPECT_EQ(2.25f, c[2]);
}

TEST(VectorNTest, MultiplyMatrixOperator)
{
    SCG::VectorN<2> a({1.0f, 2.0f});
    SCG::MatrixNN<2> m({{2.0f, 1.0f},
                        {3.0f, -1.0f}});
    SCG::VectorN<2> am = a * m;
    EXPECT_NEAR(8.0f, am[0], 1e-6f);
    EXPECT_NEAR(-1.0f, am[1], 1e-6f);
}

TEST(VectorNTest, DivideFloatOperator)
{
    SCG::VectorN<2> a({1.0f, 2.0f});
    SCG::VectorN<2> b = a / 2.0f;
    EXPECT_NEAR(0.5f, b[0], 1e-6f);
    EXPECT_NEAR(1.0f, b[1], 1e-6f);
}

TEST(VectorNTest, DivideFloatOperatorZeroDivision)
{
    EXPECT_THROW(
        []
        {
            SCG::VectorN<3> a({1.0f, 2.0f, 3.0f});
            SCG::VectorN<3> b = a / 0.0f;
        }(),
        std::domain_error);
}

TEST(VectorNTest, AddAssignOperator)
{
    SCG::VectorN<3> a({1.0f, 2.0f, 3.0f});
    a += 0.5f;
    EXPECT_EQ(1.5f, a[0]);
    EXPECT_EQ(2.5f, a[1]);
    EXPECT_EQ(3.5f, a[2]);
}

TEST(VectorNTest, SubstractAssignOperator)
{
    SCG::VectorN<3> a({1.0f, 2.0f, 3.0f});
    a -= 0.5f;
    EXPECT_EQ(0.5f, a[0]);
    EXPECT_EQ(1.5f, a[1]);
    EXPECT_EQ(2.5f, a[2]);
}

TEST(VectorNTest, MultiplyAssignOperator)
{
    SCG::VectorN<3> a({1.0f, 2.0f, 3.0f});
    a *= 0.5f;
    EXPECT_EQ(0.5f, a[0]);
    EXPECT_EQ(1.0f, a[1]);
    EXPECT_EQ(1.5f, a[2]);
}

TEST(VectorNTest, DivideAssignFloatOperator)
{
    SCG::VectorN<2> a({1.0f, 2.0f});
    a /= 2.0f;
    EXPECT_NEAR(0.5f, a[0], 1e-6f);
    EXPECT_NEAR(1.0f, a[1], 1e-6f);
}

TEST(VectorNTest, DivideAssignFloatOperatorZeroDivision)
{
    EXPECT_THROW(
        []
        {
            SCG::VectorN<3> a({1.0f, 2.0f, 3.0f});
            a /= 0.0f;
        }(),
        std::domain_error);
}
TEST(VectorNTest, EqualOperator)
{
    SCG::VectorN<3> a({1.0f, 2.0f, 3.0f});
    SCG::VectorN<3> b({1.0f, 2.0f, 3.0f});
    EXPECT_TRUE(a == b);
}

TEST(VectorNTest, EqualOperatorFalse)
{
    SCG::VectorN<3> a({1.0f, 2.0f, 3.0f});
    SCG::VectorN<3> b({1.25f, 2.0f, 3.0f});
    EXPECT_FALSE(a == b);
}

TEST(VectorNTest, DotProduct)
{
    SCG::VectorN<3> a({1.0f, 2.0f, 3.0f});
    SCG::VectorN<3> b({1.0f, 0.5f, 1.5f});
    EXPECT_EQ(6.5f, a.Dot(b));
}

TEST(VectorNTest, Length)
{
    SCG::VectorN<3> a({2.0f, 3.0f, 6.0f});
    EXPECT_EQ(7.0f, a.Length());
}

TEST(VectorNTest, Normalize)
{
    SCG::VectorN<3> a({2.0f, 3.0f, 6.0f});
    EXPECT_EQ(1.0f, a.Normalize().Length());
}

TEST(VectorNTest, NormalizeZeroVector)
{
    SCG::VectorN<3> a({0.0f, 0.0f, 0.0f});
    EXPECT_THROW(a.Normalize(), std::domain_error);
}
