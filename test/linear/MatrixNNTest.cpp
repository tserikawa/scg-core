#include "scg/linear/MatrixNN.hpp"
#include <gtest/gtest.h>

TEST(MatrixNNTest, DefaultConstructor)
{
    SCG::MatrixNN<2> m;
    EXPECT_EQ(0.0f, m(0, 0));
    EXPECT_EQ(0.0f, m(0, 1));
    EXPECT_EQ(0.0f, m(1, 0));
    EXPECT_EQ(0.0f, m(1, 1));
}

TEST(MatrixNNTest, Initializer)
{
    SCG::MatrixNN<2> m({{-3.0f, 0.0f},
                        {5.0f, 0.5f}});
    EXPECT_EQ(-3.0f, m(0, 0));
    EXPECT_EQ(0.0f, m(0, 1));
    EXPECT_EQ(5.0f, m(1, 0));
    EXPECT_EQ(0.5f, m(1, 1));
}

TEST(MatrixNNTest, Indexer)
{
    SCG::MatrixNN<2> m;
    m(0, 0) = -3.0f;
    m(0, 1) = 0.0f;
    m(1, 0) = 5.0f;
    m(1, 1) = 0.5f;
    EXPECT_EQ(-3.0f, m(0, 0));
    EXPECT_EQ(0.0f, m(0, 1));
    EXPECT_EQ(5.0f, m(1, 0));
    EXPECT_EQ(0.5f, m(1, 1));
}

TEST(MatrixNNTest, Transpose)
{
    SCG::MatrixNN<2> m;
    m(0, 0) = -3.0f;
    m(0, 1) = 0.0f;
    m(1, 0) = 5.0f;
    m(1, 1) = 0.5f;
    SCG::MatrixNN<2> tM = m.Transpose();
    EXPECT_EQ(-3.0f, tM(0, 0));
    EXPECT_EQ(5.0f, tM(0, 1));
    EXPECT_EQ(0.0f, tM(1, 0));
    EXPECT_EQ(0.5f, tM(1, 1));
}

TEST(MatrixNNTest, MultiplyScalarOperator)
{
    SCG::MatrixNN<2> m({{-3.0f, 0.0f},
                        {5.0f, 0.5f}});
    SCG::MatrixNN<2> m2 = m * 2.0;
    EXPECT_EQ(-6.0f, m2(0, 0));
    EXPECT_EQ(0.0f, m2(0, 1));
    EXPECT_EQ(10.0f, m2(1, 0));
    EXPECT_EQ(1.0f, m2(1, 1));
}

TEST(MatrixNNTest, MultiplyMatrixOperator)
{
    SCG::MatrixNN<2> a({{-3.0f, 0.0f},
                        {5.0f, 0.5f}});
    SCG::MatrixNN<2> b({{-7.0f, 2.0f},
                        {4.0f, 6.0f}});
    SCG::MatrixNN<2> ab = a * b;
    EXPECT_EQ(21.0f, ab(0, 0));
    EXPECT_EQ(-6.0f, ab(0, 1));
    EXPECT_EQ(-33.0f, ab(1, 0));
    EXPECT_EQ(13.0f, ab(1, 1));
}