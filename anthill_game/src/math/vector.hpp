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

    Vec2<int> toInt() const { return Vec2<int>(static_cast<int>(x), static_cast<int>(y)); }
    Vec2<float> toFloat() const { return Vec2<float>(static_cast<float>(x), static_cast<float>(y)); }

    T x = 0, y = 0;
};