#include "input.hpp"

#include "utils/data.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_mouse.h>
#include <vector>

void Input::poll(Bind bind, bool isDown)
{
    if (Utils::Data::doesVectorContain(m_binds, bind))
    {
        m_down = isDown;
    }
}

void Input::update()
{
    m_pressed   = m_down && !m_wasDown;
    m_unpressed = m_wasDown && !m_down;

    m_wasDown = m_down;
}

void Input::assignBind(const Bind &bind) { m_binds.push_back(bind); }
void Input::removeBind(const Bind &bind) { Utils::Data::removeItemFromVector(m_binds, bind); }
void Input::removeBindsOfType(ButtonType type)
{
    for (auto it = m_binds.begin(); it != m_binds.end(); ++it)
    {
        if (it->type == type)
        {
            it = m_binds.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
