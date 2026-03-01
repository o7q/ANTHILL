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

    operator Vec2<float>() const
    {
        return Vec2<float>(static_cast<float>(x), static_cast<float>(y));
    }
    operator Vec2<int>() const
    {
        return Vec2<int>(static_cast<int>(x), static_cast<int>(y));
    }
    operator Vec2<unsigned int>() const
    {
        return Vec2<unsigned int>(static_cast<unsigned int>(x),
                                  static_cast<unsigned int>(y));
    }
    operator Vec2<double>() const
    {
        return Vec2<double>(static_cast<double>(x), static_cast<double>(y));
    }

    T length() const { return std::sqrt(x * x + y * y); }
    Vec2 normalize() const
    {
        T l = length();
        return {x / l, y / l};
    }
    T dot(const Vec2 &other) const { return x * other.x + y * other.y; }
    Vec2 floor() const
    {
        return {static_cast<T>(std::floor(x)), static_cast<T>(std::floor(y))};
    }
    Vec2 ceil() const
    {
        return {static_cast<T>(std::ceil(x)), static_cast<T>(std::ceil(y))};
    }
    Vec2 pow(const Vec2 &other)
    {
        return {std::pow(x, other.x), std::pow(y, other.y)};
    }

    Vec2<int> toGrid()
    {
        return {static_cast<int>(std::floor(x)),
                static_cast<int>(std::floor(y))};
    }
};
