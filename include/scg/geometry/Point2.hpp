#pragma once

#include "scg/linear/Vector2.hpp"

#include <cmath>

namespace SCG
{
    class Point2
    {
    private:
        float m_x;
        float m_y;

    public:
        Point2(float x, float y) : m_x(x), m_y(y) {}

        float X() const noexcept
        {
            return m_x;
        }

        float Y() const noexcept
        {
            return m_y;
        }

        float DistanceTo(const Point2 &other) const noexcept
        {
            float dx = abs(m_x - other.X());
            float dy = abs(m_y - other.Y());
            return sqrt(dx * dx + dy * dy);
        }

        Point2 operator+(const Vector2 &v) const noexcept
        {
            return Point2(m_x + v.X(), m_y + v.Y());
        }

        Vector2 operator-(const Point2 &p) const noexcept
        {
            return Vector2(m_x - p.X(), m_y - p.Y());
        }

        bool operator==(const Point2 &p) const noexcept
        {
            return this->DistanceTo(p) <= 1e-6f;
        }
    };
}
