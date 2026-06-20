#include "camera.hpp"

px::Vec2i Camera::viewportToCamera(px::Vec2i pos) const { return pos + m_position.toGrid() - m_viewSize.toInt() / 2; }
px::Vec2i Camera::cameraToRenderer(px::Vec2i pos) const { return pos - m_position.toGrid() + m_viewSize.toInt() / 2; }
