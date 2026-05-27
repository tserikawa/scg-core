#pragma once

#include "scg/linear/MatrixNN.hpp"

#include <cmath>
#include <stdexcept>
#include <initializer_list>

namespace SCG
{
    const float FloatZeroValue = 1e-6f;

    // NOTE:CRTPパターン（Curiously Recurring Template Pattern）
    template <typename T, int N>
    class VectorBase
    {
    protected:
        float m_values[N];

    public:
        VectorBase()
        {
            for (size_t i = 0; i < N; i++)
            {
                m_values[i] = 0.0f;
            }
        }

        VectorBase(std::initializer_list<float> init)
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

    public:
        float Length() const noexcept
        {
            float totalSquareLength = 0.0f;
            for (size_t i = 0; i < N; i++)
            {
                totalSquareLength += powf(m_values[i], 2.0f);
            }
            return sqrt(totalSquareLength);
        }

        T Normalize() const
        {
            float length = this->Length();

            if (length <= FloatZeroValue)
            {
                throw std::domain_error("Zero Vector");
            }

            T v;
            for (size_t i = 0; i < N; i++)
            {
                v[i] = m_values[i] / length;
            }

            return v;
        }

        float Dot(const VectorBase<T, N> &other) const noexcept
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

        T operator+(const VectorBase<T, N> &other) const
        {
            T result;
            for (size_t i = 0; i < N; i++)
            {
                result[i] = m_values[i] + other[i];
            }
            return result;
        }

        T operator-(const VectorBase<T, N> &other) const
        {
            T result;
            for (size_t i = 0; i < N; i++)
            {
                result[i] = m_values[i] - other[i];
            }
            return result;
        }

        T operator*(const VectorBase<T, N> &other) const
        {
            T result;
            for (size_t i = 0; i < N; i++)
            {
                result.m_values[i] = m_values[i] * other[i];
            }
            return result;
        }

        T operator*(const MatrixNN<N> &m) const
        {
            T vm;
            for (size_t i = 0; i < N; i++)
            {
                for (size_t k = 0; k < N; k++)
                {
                    vm[i] += (m_values[k] * m(k, i));
                }
            }
            return vm;
        }

        T operator/(float value) const
        {
            if (abs(value) <= 1e-6f)
            {
                throw std::domain_error("VectorBase::operator/: ゼロ除算は数学的に定義されていません。ゼロ以外のスカラー値を指定してください。");
            }

            T result;
            for (size_t i = 0; i < N; i++)
            {
                result[i] = m_values[i] / value;
            }
            return result;
        }

        VectorBase<T, N> &operator+=(float value)
        {
            for (size_t i = 0; i < N; i++)
            {
                m_values[i] += value;
            }
            return *this;
        }

        VectorBase<T, N> &operator-=(float value)
        {
            for (size_t i = 0; i < N; i++)
            {
                m_values[i] -= value;
            }
            return *this;
        }

        VectorBase<T, N> &operator*=(float value)
        {
            for (size_t i = 0; i < N; i++)
            {
                m_values[i] *= value;
            }
            return *this;
        }

        VectorBase<T, N> &operator/=(float value)
        {
            if (abs(value) <= 1e-6f)
            {
                throw std::domain_error("VectorBase::operator/: ゼロ除算は数学的に定義されていません。ゼロ以外のスカラー値を指定してください。");
            }

            for (size_t i = 0; i < N; i++)
            {
                m_values[i] /= value;
            }
            return *this;
        }

        bool operator==(const VectorBase<T, N> &other) const noexcept
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