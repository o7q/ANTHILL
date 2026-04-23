#include "camera.hpp"
#include "math/angle.hpp"

void Camera::jerk(Angle angle, float amount)
{
    float radians = angle.radians();
    Vec2f vec = Vec2f(std::cosf(radians), std::sinf(radians)) * amount;
    m_position += vec;
}
