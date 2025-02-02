#pragma once

template <typename T>
struct Vec2
{
    Vec2() = default;
    Vec2(T x, T y) : x(x), y(y) {}

    Vec2<T> operator+(const Vec2<T> &other) const { return Vec2<T>(x + other.x, y + other.y); }
    Vec2<T> operator-(const Vec2<T> &other) const { return Vec2<T>(x - other.x, y - other.y); }
    Vec2<T> operator*(const Vec2<T> &other) const { return Vec2<T>(x * other.x, y * other.y); }
    Vec2<T> operator/(const Vec2<T> &other) const { return Vec2<T>(x / other.x, y / other.y); }

    Vec2<T> operator+(T other) const { return Vec2<T>(x + other, y + other); }
    Vec2<T> operator-(T other) const { return Vec2<T>(x - other, y - other); }
    Vec2<T> operator*(T other) const { return Vec2<T>(x * other, y * other); }
    Vec2<T> operator/(T other) const { return Vec2<T>(x / other, y / other); }

    T x = 0, y = 0;
};