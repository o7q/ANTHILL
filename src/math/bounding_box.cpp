#include "bounding_box.hpp"

BoundingBox::BoundingBox(int x, int y, int width, int height)
{
    m_pos.x = x;
    m_pos.y = y;

    m_size.x = width;
    m_size.y = height;

    update_points();
}

void BoundingBox::setPosition(int x, int y)
{
    m_pos.x = x;
    m_pos.y = y;

    update_points();
}

void BoundingBox::setSize(int width, int height)
{
    m_size.x = width;
    m_size.y = height;

    update_points();
}

void BoundingBox::update_points()
{
    m_points[0].x = m_pos.x - m_size.x / 2.0f;
    m_points[0].y = m_pos.y - m_size.y / 2.0f;

    m_points[1].x = m_pos.x + m_size.x / 2.0f;
    m_points[1].y = m_pos.y - m_size.y / 2.0f;

    m_points[2].x = m_pos.x + m_size.x / 2.0f;
    m_points[2].y = m_pos.y + m_size.y / 2.0f;

    m_points[3].x = m_pos.x - m_size.x / 2.0f;
    m_points[3].y = m_pos.y + m_size.y / 2.0f;
}