#pragma once

#include <cmath>

template <typename T> struct Vec2
{
    T x = 0, y = 0;

    Vec2() = default;
    Vec2(T x, T y) : x(x), y(y) {}

    Vec2 operator+(const Vec2 &v) const { return {x + v.x, y + v.y}; }
    Vec2 operator-(const Vec2 &v) const { return {x - v.x, y - v.y}; }
    Vec2 operator*(const Vec2 &v) const { return {x * v.x, y * v.y}; }
    Vec2 operator/(const Vec2 &v) const { return {x / v.x, y / v.y}; }

    Vec2 operator+(T s) const { return {x + s, y + s}; }
    Vec2 operator-(T s) const { return {x - s, y - s}; }
    Vec2 operator*(T s) const { return {x * s, y * s}; }
    Vec2 operator/(T s) const { return {x / s, y / s}; }

    Vec2 &operator+=(const Vec2 &v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }
    Vec2 &operator-=(const Vec2 &v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    Vec2 &operator*=(const Vec2 &v)
    {
        x *= v.x;
        y *= v.y;
        return *this;
    }
    Vec2 &operator/=(const Vec2 &v)
    {
        x /= v.x;
        y /= v.y;
        return *this;
    }

    Vec2 &operator+=(T s)
    {
        x += s;
        y += s;
        return *this;
    }
    Vec2 &operator-=(T s)
    {
        x -= s;
        y -= s;
        return *this;
    }
    Vec2 &operator*=(T s)
    {
        x *= s;
        y *= s;
        return *this;
    }
    Vec2 &operator/=(T s)
    {
        x /= s;
        y /= s;
        return *this;
    }

    Vec2 operator-() const { return {-x, -y}; }

    T length() const { return std::sqrt(x * x + y * y); }
    Vec2 normalize() const
    {
        T l = length();
        return {x / l, y / l};
    }
    T dot(const Vec2 &other) const { return x * other.x + y * other.y; }
};
