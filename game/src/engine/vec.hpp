#pragma once

#include <algorithm>
template <typename T> struct Vec2
{
    Vec2() = default;
    Vec2(T x, T y) : x(x), y(y) {}

    T x, y;

    Vec2 operator+(const Vec2 &v) { return Vec2<T>(x + v.x, y + v.y); }
    Vec2 operator+(T s) { return Vec2<T>(x + s, y + s); }

    Vec2 operator-(const Vec2 &v) { return Vec2<T>(x - v.x, y - v.y); }
    Vec2 operator-(T s) { return Vec2<T>(x - s, y - s); }

    Vec2 operator*(const Vec2 &v) { return Vec2<T>(x * v.x, y * v.y); }
    Vec2 operator*(T s) { return Vec2<T>(x * s, y * s); }

    Vec2 operator/(const Vec2 &v) { return Vec2<T>(x / v.x, y / v.y); }
    Vec2 operator/(T s) { return Vec2<T>(x / s, y / s); }

    Vec2 negate() { return Vec2<T>(-x, -y); }
};
