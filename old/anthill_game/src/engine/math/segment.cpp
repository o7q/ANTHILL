#include "segment.hpp"

const Segment::IData Segment::segmentIntersect(const Segment &other) const
{
    float x1 = a.x;
    float x2 = b.x;
    float x3 = other.a.x;
    float x4 = other.b.x;

    float y1 = a.y;
    float y2 = b.y;
    float y3 = other.a.y;
    float y4 = other.b.y;

    float d  =  (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
    float ra = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / d;
    float rb = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / d;

    IData i_data;
    if (ra >= 0.0f && ra <= 1.0f && rb >= 0 && rb <= 1.0f)
    {
        i_data.intersecting = true;

        float i_x = x1 + ra * (x2 - x1);
        float i_y = y1 + ra * (y2 - y1);

        i_data.position.x = i_x;
        i_data.position.y = i_y;

        i_data.range_a = ra;
        i_data.range_b = rb;
    }

    return i_data;
}