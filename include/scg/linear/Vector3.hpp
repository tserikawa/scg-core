#pragma once

#include "scg/linear/VectorBase.hpp"
#include <cmath>
#include <stdexcept>
#include <initializer_list>

namespace SCG
{
    class Vector3 : public VectorBase<Vector3, 3>
    {
    public:
        Vector3() : VectorBase<Vector3, 3>() {}

        Vector3(std::initializer_list<float> init)
            : VectorBase<Vector3, 3>(init) {}

        float X() const noexcept
        {
            return m_values[0];
        }

        float Y() const noexcept
        {
            return m_values[1];
        }

        float Z() const noexcept
        {
            return m_values[2];
        }

        Vector3 Cross(const Vector3 &other) const noexcept
        {
            return Vector3({Y() * other.Z() - Z() * other.Y(),
                            Z() * other.X() - X() * other.Z(),
                            X() * other.Y() - Y() * other.X()});
        }
    };
}