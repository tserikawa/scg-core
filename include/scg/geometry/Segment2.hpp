#pragma once

#include "scg/geometry/Point2.hpp"

namespace SCG

{
    class Segment2
    {
    private:
        Point2 m_start;
        Point2 m_end;

    public:
        Segment2(Point2 start, Point2 end) : m_start(start), m_end(end) {}

        Point2 Start() const noexcept
        {
            return m_start;
        }

        Point2 MidPoint() const noexcept
        {
            return m_start + Direction(false) / 2.0;
        }

        Point2 End() const noexcept
        {
            return m_end;
        }

        float Length() const noexcept
        {
            return m_start.DistanceTo(m_end);
        }

        Vector2 Direction(bool isNormalized) const noexcept
        {
            Vector2 direction = m_end - m_start;
            return isNormalized ? direction.Normalize() : direction;
        }
    };
}