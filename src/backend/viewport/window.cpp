#include "viewport.hpp"

#include <algorithm>

void Viewport::recalculatePresentRect(Vec2u windowSize, float windowAspect)
{
    if (windowAspect > m_aspectRatio)
    {
        m_presentRect.w = windowSize.x / windowAspect * m_aspectRatio;
        m_presentRect.h = windowSize.y;
    }
    else
    {
        m_presentRect.w = windowSize.x;
        m_presentRect.h = windowSize.y * windowAspect / m_aspectRatio;
    }
    m_presentRect.x = windowSize.x / 2.0f - m_presentRect.w / 2.0f;
    m_presentRect.y = windowSize.y / 2.0f - m_presentRect.h / 2.0f;
}

Vec2i Viewport::windowToViewportPosition(Vec2f windowPosition)
{
    windowPosition.x -= m_presentRect.x;
    windowPosition.y -= m_presentRect.y;

    float pixelSize = m_presentRect.w / m_size.x;
    windowPosition.x /= pixelSize;
    windowPosition.y /= pixelSize;

    windowPosition.x =
        std::clamp(windowPosition.x, 0.0f, static_cast<float>(m_size.x) - 1);
    windowPosition.y =
        std::clamp(windowPosition.y, 0.0f, static_cast<float>(m_size.y) - 1);

    return windowPosition.toGrid();
}
