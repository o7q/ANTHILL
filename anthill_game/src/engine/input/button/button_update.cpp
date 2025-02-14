#include "button.hpp"

void IButton::update()
{
    m_pressed = m_down && !m_wasDown;
    m_unpressed = m_wasDown && !m_down;

    m_wasDown = m_down;
}