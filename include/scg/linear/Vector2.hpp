#pragma once

#include "scg/linear/VectorN.hpp"
#include <cmath>
#include <stdexcept>
#include <initializer_list>

namespace SCG
{
    class Vector2 : public VectorN<2>
    {
    public:
        Vector2() : VectorN<2>() {}

        Vector2(float x, float y)
            : VectorN<2>({x, y}) {}

        Vector2(std::initializer_list<float> init)
            : VectorN<2>(init) {}

        float X() const noexcept
        {
            return m_values[0];
        }

        float Y() const noexcept
        {
            return m_values[1];
        }

        float Cross(const Vector2 &other) const noexcept
        {
            return this->X() * other.Y() - this->Y() * other.X();
        }

        Vector2 Rotate(float radian) const noexcept
        {
            return Vector2({
                X() * std::cos(radian) - Y() * std::sin(radian),
                X() * std::sin(radian) + Y() * std::cos(radian),
            });
        }
    };
}