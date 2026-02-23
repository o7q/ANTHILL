#pragma once

#include <cmath>

template <typename T> struct Vec2
{
    Vec2() = default;
    Vec2(T x, T y) : x(x), y(y) {}

    T x, y;

    Vec2 operator+(const Vec2 &v) const { return Vec2<T>(x + v.x, y + v.y); }
    Vec2 &operator+=(const Vec2 &v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }
    Vec2 operator+(T s) const { return Vec2<T>(x + s, y + s); }
    Vec2 operator+=(T s) const { return Vec2<T>(x + s, y + s); }

    Vec2 operator-(const Vec2 &v) const { return Vec2<T>(x - v.x, y - v.y); }
    Vec2 &operator-=(const Vec2 &v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    Vec2 operator-(T s) const { return Vec2<T>(x - s, y - s); }

    Vec2 operator*(const Vec2 &v) const { return Vec2<T>(x * v.x, y * v.y); }
    Vec2 &operator*=(const Vec2 &v)
    {
        x *= v.x;
        y *= v.y;
        return *this;
    }
    Vec2 operator*(T s) const { return Vec2<T>(x * s, y * s); }

    Vec2 operator/(const Vec2 &v) const { return Vec2<T>(x / v.x, y / v.y); }
    Vec2 &operator/=(const Vec2 &v)
    {
        x /= v.x;
        y /= v.y;
        return *this;
    }
    Vec2 operator/(T s) const { return Vec2<T>(x / s, y / s); }

    float length() const { return std::sqrt(x * x + y * y); }
    Vec2 normalize() const
    {
        float l = length();
        return Vec2<float>(x / l, y / l);
    }
    float dot(const Vec2<float> &other) const
    {
        return x * other.x + y * other.y;
    }
    Vec2 negate() { return Vec2<T>(-x, -y); }
};
