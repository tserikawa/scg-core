#pragma once

#include "scg/linear/MatrixNN.hpp"

#include <cmath>
#include <stdexcept>
#include <initializer_list>

namespace SCG
{
    const float FloatZeroValue = 1e-6f;

    template <int N>
    class VectorN
    {
    protected:
        float m_values[N];

    public:
        VectorN()
        {
            for (size_t i = 0; i < N; i++)
            {
                m_values[i] = 0.0f;
            }
        }

        VectorN(std::initializer_list<float> init)
        {
            if (init.size() != N)
            {
                throw std::invalid_argument("引数の要素数が一致しません。");
            }

            for (size_t i = 0; i < N; i++)
            {
                m_values[i] = *(init.begin() + i);
            }
        }

        float Length() const noexcept
        {
            float totalSquareLength = 0.0f;
            for (size_t i = 0; i < N; i++)
            {
                totalSquareLength += powf(m_values[i], 2.0f);
            }
            return sqrt(totalSquareLength);
        }

        VectorN<N> Normalize() const
        {
            float length = this->Length();

            if (length <= FloatZeroValue)
            {
                throw std::domain_error("Zero Vector");
            }

            VectorN<N> v;
            for (size_t i = 0; i < N; i++)
            {
                v[i] = m_values[i] / length;
            }

            return v;
        }

        float Dot(const VectorN<N> &other) const noexcept
        {
            float dot = 0.0f;
            for (size_t i = 0; i < N; i++)
            {
                dot += m_values[i] * other[i];
            }
            return dot;
        }

        const float &operator[](size_t index) const
        {
            if (index >= N)
            {
                throw std::out_of_range("インデックスが要素数を超えています。");
            }

            return m_values[index];
        }

        float &operator[](size_t index)
        {
            if (index >= N)
            {
                throw std::out_of_range("インデックスが要素数を超えています。");
            }

            return m_values[index];
        }

        VectorN<N> operator+(const VectorN<N> &other) const
        {
            VectorN<N> result;
            for (size_t i = 0; i < N; i++)
            {
                result[i] = m_values[i] + other[i];
            }
            return result;
        }

        VectorN<N> operator-(const VectorN<N> &other) const
        {
            VectorN<N> result;
            for (size_t i = 0; i < N; i++)
            {
                result[i] = m_values[i] - other[i];
            }
            return result;
        }

        VectorN<N> operator*(const VectorN<N> &other) const
        {
            VectorN<N> result;
            for (size_t i = 0; i < N; i++)
            {
                result[i] = m_values[i] * other[i];
            }
            return result;
        }

        VectorN<N> operator*(const MatrixNN<N> &m) const
        {
            VectorN<N> vm;
            for (size_t i = 0; i < N; i++)
            {
                for (size_t k = 0; k < N; k++)
                {
                    vm[i] += (m_values[k] * m(k, i));
                }
            }
            return vm;
        }

        VectorN<N> &operator+=(float value)
        {
            for (size_t i = 0; i < N; i++)
            {
                m_values[i] += value;
            }
            return *this;
        }

        VectorN<N> &operator-=(float value)
        {
            for (size_t i = 0; i < N; i++)
            {
                m_values[i] -= value;
            }
            return *this;
        }

        VectorN<N> &operator*=(float value)
        {
            for (size_t i = 0; i < N; i++)
            {
                m_values[i] *= value;
            }
            return *this;
        }

        bool operator==(const VectorN<N> &other) const noexcept
        {
            for (size_t i = 0; i < N; i++)
            {
                if (abs(m_values[i] - other[i]) > FloatZeroValue)
                {
                    return false;
                }
            }
            return true;
        }
    };
}