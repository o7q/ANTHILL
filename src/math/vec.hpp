#pragma once

#include "math/numbers.hpp"
#include <algorithm>
#include <cmath>

template <typename T> struct Vec2
{
    T x = 0, y = 0;

    Vec2() = default;
    Vec2(T x_, T y_) : x(x_), y(y_) {}

    Vec2 operator+(const Vec2 &v) const { return {x + v.x, y + v.y}; }
    Vec2 operator-(const Vec2 &v) const { return {x - v.x, y - v.y}; }
    Vec2 operator*(const Vec2 &v) const { return {x * v.x, y * v.y}; }
    Vec2 operator/(const Vec2 &v) const { return {x / v.x, y / v.y}; }
    Vec2 operator%(const Vec2 &v) const { return {x % v.x, y % v.y}; }

    Vec2 operator+(T s) const { return {x + s, y + s}; }
    Vec2 operator-(T s) const { return {x - s, y - s}; }
    Vec2 operator*(T s) const { return {x * s, y * s}; }
    Vec2 operator/(T s) const { return {x / s, y / s}; }
    Vec2 operator%(T s) const { return {x % s, y % s}; }

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
    Vec2 &operator%=(const Vec2 &v)
    {
        x %= v.x;
        y %= v.y;
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
    Vec2 &operator%=(T s)
    {
        x %= s;
        y %= s;
        return *this;
    }

    Vec2 operator-() const { return {-x, -y}; }

    bool operator==(const Vec2 &other) const { return x == other.x && y == other.y; }
    bool operator!=(const Vec2 &other) const { return x != other.x || y != other.y; }

    T length() const { return std::sqrt(x * x + y * y); }
    Vec2 normalize() const
    {
        T l = length();
        return {x / l, y / l};
    }
    T dot(const Vec2 &other) const { return x * other.x + y * other.y; }
    Vec2 floor() const { return {static_cast<T>(std::floor(x)), static_cast<T>(std::floor(y))}; }
    Vec2 ceil() const { return {static_cast<T>(std::ceil(x)), static_cast<T>(std::ceil(y))}; }
    Vec2 round() const { return {static_cast<T>(std::round(x)), static_cast<T>(std::round(y))}; }
    Vec2 pow(const Vec2 &other) const { return {std::pow(x, other.x), std::pow(y, other.y)}; }
    Vec2 clamp(const Vec2 &min, const Vec2 &max)
    {
        return {std::clamp(x, min.x, max.x), std::clamp(y, min.y, max.y)};
    }
    Vec2<int> direction() { return {Math::Numbers::sign(x), Math::Numbers::sign(y)}; }

    Vec2<int> toGrid() const { return {static_cast<int>(std::floor(x)), static_cast<int>(std::floor(y))}; }
    Vec2<float> toFloat() const { return {static_cast<float>(x), static_cast<float>(y)}; }
    Vec2<double> toDouble() const { return {static_cast<double>(x), static_cast<double>(y)}; }
    Vec2<int> toInt() const { return {static_cast<int>(x), static_cast<int>(y)}; }
    Vec2<unsigned int> toUnsignedInt() const
    {
        return {static_cast<unsigned int>(x), static_cast<unsigned int>(y)};
    }
};

using Vec2i = Vec2<int>;
using Vec2u = Vec2<unsigned int>;
using Vec2f = Vec2<float>;
using Vec2d = Vec2<double>;
