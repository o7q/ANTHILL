#include "camera.hpp"
#include "px/basic_types/angle.hpp"

void Camera::jerk(px::Angle_f angle, float amount)
{
    float radians = angle.radians();
    px::Vec2f vec = px::Vec2f{std::cosf(radians), std::sinf(radians)} * amount;
    m_position += vec;
}
