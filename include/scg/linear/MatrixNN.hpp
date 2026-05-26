#pragma once

#include <stdexcept>
#include <initializer_list>

namespace SCG
{
    template <int N>
    class MatrixNN
    {
    protected:
        float m_matrix[N][N];

    public:
        MatrixNN()
        {
            for (size_t i = 0; i < N; i++)
            {
                for (size_t j = 0; j < N; j++)
                {
                    m_matrix[i][j] = 0.0f;
                }
            }
        }

        MatrixNN(std::initializer_list<std::initializer_list<float>> list)
        {
            if (list.size() > N)
            {
                throw std::out_of_range("要素数が行列のサイズを超えています。");
            }

            for (size_t i = 0; i < list.size(); i++)
            {
                auto row = *(list.begin() + i);
                if (row.size() > N)
                {
                    throw std::out_of_range("要素数が行列のサイズを超えています。");
                }

                for (size_t j = 0; j < row.size(); j++)
                {
                    m_matrix[i][j] = *(row.begin() + j);
                }
            }
        }

        MatrixNN<N> Transpose() const noexcept
        {
            MatrixNN<N> tM;
            for (size_t i = 0; i < N; i++)
            {
                for (size_t j = 0; j < N; j++)
                {
                    tM(i, j) = m_matrix[j][i];
                }
            }
            return tM;
        }

        MatrixNN<N> operator*(float a) const noexcept
        {
            MatrixNN<N> m;
            for (size_t i = 0; i < N; i++)
            {
                for (size_t j = 0; j < N; j++)
                {
                    m(i, j) = m_matrix[i][j] * a;
                }
            }
            return m;
        }

        MatrixNN<N> operator*(const MatrixNN<N> &m) const noexcept
        {
            MatrixNN<N> result;
            for (size_t i = 0; i < N; i++)
            {
                for (size_t j = 0; j < N; j++)
                {
                    float total = 0.0f;
                    for (size_t k = 0; k < N; k++)
                    {
                        total += m_matrix[i][k] * m(k, j);
                    }
                    result(i, j) = total;
                }
            }
            return result;
        }

        float &operator()(size_t row, size_t col)
        {
            if (!IsInsideOfRange(row, col))
            {
                throw std::out_of_range("インデックスが行列のサイズを超えています。");
            }

            return m_matrix[row][col];
        }

        const float &operator()(size_t row, size_t col) const
        {
            if (!IsInsideOfRange(row, col))
            {
                throw std::out_of_range("インデックスが行列のサイズを超えています。");
            }

            return m_matrix[row][col];
        }

    private:
        bool IsInsideOfRange(size_t row, size_t col) const noexcept
        {
            return 0 <= row && row < N && 0 <= col && col < N;
        }
    };
}