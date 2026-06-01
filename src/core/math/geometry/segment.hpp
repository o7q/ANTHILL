#pragma once

#include "core/math/geometry/vec.hpp"
#include "core/utils/hash.hpp"

template <typename T> struct Segment
{
    Vec2<T> a;
    Vec2<T> b;

    bool operator==(const Segment &other) const
    {
        return (a == other.a && b == other.b) || (a == other.b && b == other.a);
    }
};

template <typename T> struct SegmentHash
{
  public:
    std::size_t operator()(const Segment<T> &s) const
    {
        Vec2Hash<T> h;
        return Utils::Hash::hashCombine(h(s.a), h(s.b));
    }
};

using Segment_i = Segment<int>;
using Segment_u = Segment<unsigned int>;
using Segment_f = Segment<float>;
using Segment_d = Segment<double>;
